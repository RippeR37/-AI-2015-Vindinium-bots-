#include "Path.h"
#include "Graph/AStar.hpp"

#include <cmath>

/*** Typedefs ***/
typedef Graph::GraphAdapter<State, Position, int> BaseGraphAdapter;


/*** Simple A* graph adapter for getPath(state, start, end) method ***/
class SimpleMapAdapter : public BaseGraphAdapter {
    public:
        SimpleMapAdapter(const State& state, const Position& goal) : BaseGraphAdapter(state), _goal(goal) {

        }

        bool isAvailable(const Position& position) const {
            bool isAvailable = false;

            if(position == _goal)
                isAvailable = true;
            else if(_graph.get_tile_from_background_border_check(position) == Tile::EMPTY)
                isAvailable = true;

            return isAvailable;
        }

        std::vector<NodeAdapterType> getNeighboursOf(const NodeAdapterType& node) const {
            std::vector<NodeAdapterType> neighbours;

            std::vector<std::pair<int, int>> posDiffs = {
                {  0, -1 }, {  0,  1 }, { -1,  0 }, {  1,  0 }
            };

            for(const std::pair<int, int>& posDiff : posDiffs) {
                neighbours.push_back(
                    NodeAdapterType(
                        Position(
                            node.position.x + posDiff.first,
                            node.position.y + posDiff.second
                        )
                    )
                );
            }

            return neighbours;
        }

        virtual int getHeuristicCostLeft(const NodeAdapterType& currentNode, const NodeAdapterType& goal) const {
            int dx, dy;

            dx = std::abs(currentNode.position.x - goal.position.x);
            dy = std::abs(currentNode.position.y - goal.position.y);

            return dx + dy;
        }

    private:
        const Position& _goal;

};

/*** Simple A* graph adapter for getPath(state, start, end) method ***/
class AdvancedMapAdapter : public BaseGraphAdapter {
    public:
        AdvancedMapAdapter(const State& state) : BaseGraphAdapter(state) {

        }

        bool isAvailable(const Position& position) const {
            bool isAvailable = false;

            if(_graph.get_tile_from_background_border_check(position) == Tile::EMPTY)
                isAvailable = true;

            // TODO: fix this - it should return true if above function returns tile from any of accepted type!

            return isAvailable;
        }

        std::vector<NodeAdapterType> getNeighboursOf(const NodeAdapterType& node) const {
            std::vector<NodeAdapterType> neighbours;

            std::vector<std::pair<int, int>> posDiffs = {
                {  0, -1 }, {  0,  1 }, { -1,  0 }, {  1,  0 }
            };

            for(const std::pair<int, int>& posDiff : posDiffs) {
                neighbours.push_back(
                    NodeAdapterType(
                        Position(
                            node.position.x + posDiff.first,
                            node.position.y + posDiff.second
                        )
                    )
                );
            }

            return neighbours;
        }

        int getHeuristicCostLeft(const NodeAdapterType& currentNode, const NodeAdapterType& goal) const {
            // TODO: implement this

            return 0;
        }
};


Path::PathType Path::getPath(const State& state, const Position& start, const Position& end) {
    PathType result;
    Graph::AStar<State, Position, int> myAStar;
    SimpleMapAdapter myMapAdapter(state, end);
    SimpleMapAdapter::NodeAdapterType nodeStart(start);
    SimpleMapAdapter::NodeAdapterType nodeGoal(end);

    result = myAStar.getPath(myMapAdapter, nodeStart, nodeGoal);

    return result;
}


Path::PathType Path::getPath(const State& state, const Position& start, Tile tileType) {
    PathType result;

    result = getPath(state, start, { tileType });

    return result;
}


Path::PathType Path::getPath(const State& state, const Position& start, const std::vector<Tile>& tileTypes) {
    PathType result;
    Graph::AStar<State, Position, int> myAStar;
    AdvancedMapAdapter myMapAdapter(state);
    AdvancedMapAdapter::NodeAdapterType nodeStart(start);
    //SimpleMapAdapter::NodeAdapterType nodeGoal(end); // TODO: fix this

    //result = myAStar.getPath(myMapAdapter, nodeStart, nodeGoal);

    return result;
}


Direction Path::getDirection(const Position& pos1, const Position& pos2) {
    Direction result = Direction::STAY;

    if(pos2.x > pos1.x) {
        result = Direction::EAST;
    } else if(pos2.x < pos1.x) {
        result = Direction::WEST;
    } else {
        if(pos2.y > pos1.y) {
            result = Direction::NORTH;
        } else if(pos2.y < pos1.y) {
            result = Direction::SOUTH;
        }
    }

    return result;
}
#include "Path.h"
#include "Graph/AStar.hpp"

#include <cmath>

/*** Typedefs ***/
typedef Graph::GraphAdapter<State, Position, int> BaseGraphAdapter;


/*** Simple A* graph adapter for getPath(state, start, end) method ***/
class SimpleMapAdapter : public BaseGraphAdapter {
    public:
        SimpleMapAdapter(const State& state) : BaseGraphAdapter(state) {

        }

        bool isAvailable(const Position& position) const {
            bool isAvailable = false;

            // TODO: implement this

            return isAvailable;
        }

        std::vector<NodeAdapterType> getNeighboursOf(const NodeAdapterType& node) const {
            std::vector<NodeAdapterType> neighbours;

            // TODO: implement this;

            return neighbours;
        }

        virtual int getHeuristicCostLeft(const NodeAdapterType& currentNode, const NodeAdapterType& goal) const {
            int dx, dy;

            dx = std::abs(currentNode.position.x - goal.position.x);
            dy = std::abs(currentNode.position.y - goal.position.y);

            return dx + dy;
        }

};


Path::PathType Path::getPath(const State& state, const Position& start, const Position& end) {
    PathType result;
    Graph::AStar<State, Position, int> myAStar;
    SimpleMapAdapter myMapAdapter(state);
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

    // TODO: implement this

    return result;
}


Direction Path::getDirection(const Position& pos1, const Position& pos2) {
    Direction result;

    result = Direction::STAY; // TODO: implement this

    return result;
}
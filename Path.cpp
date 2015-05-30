#include "Path.h"
#include "Graph/AStar.hpp"

#include <cmath>
#include <climits>

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

/*** Advanced A* graph adapter for getPath(state, start, tileTypes) method ***/
class AdvancedMapAdapter : public BaseGraphAdapter {
    public:
        AdvancedMapAdapter(const State& state, const std::vector<Tile>& tileTypes) : BaseGraphAdapter(state), _tileTypes(tileTypes) {

        }

        bool isAvailable(const Position& position) const {
            bool isAvailable = false;
            Tile tileOnPosition;

            tileOnPosition = _graph.get_tile_from_background_border_check(position);
            if(tileOnPosition == Tile::EMPTY)
                isAvailable = true;

            for(unsigned int i = 0; i < _tileTypes.size(); ++i) {
                if(tileOnPosition == _tileTypes[i]) {
                    isAvailable = true;
                    break;
                }
            }

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

        int getHeuristicCostLeft(const NodeAdapterType& currentNode, const NodeAdapterType& currentNodeCpy) const {
            static std::vector<PositionType> tavernPositions = _getTavernPositions();
            static std::vector<PositionType> minesPositions = _getMinesPositions();

            int result = INT_MAX;
            PositionType position;
            PositionType currentPosition = currentNode.position;
            int distance, diffx, diffy;

            for(Tile t: _tileTypes) {
                switch(t) {
                    case HERO1:
                        position = _graph.heroes[0].position;
                        diffx = currentPosition.x - position.x;
                        diffy = currentPosition.y - position.y;
                        distance = diffx * diffx + diffy * diffy;
                        result = std::min(result, distance);
                        break;
                    case HERO2:
                        position = _graph.heroes[1].position;
                        diffx = currentPosition.x - position.x;
                        diffy = currentPosition.y - position.y;
                        distance = diffx * diffx + diffy * diffy;
                        result = std::min(result, distance);
                        break;
                    case HERO3:
                        position = _graph.heroes[2].position;
                        diffx = currentPosition.x - position.x;
                        diffy = currentPosition.y - position.y;
                        distance = diffx * diffx + diffy * diffy;
                        result = std::min(result, distance);
                        break;
                    case HERO4:
                        position = _graph.heroes[3].position;
                        diffx = currentPosition.x - position.x;
                        diffy = currentPosition.y - position.y;
                        distance = diffx * diffx + diffy * diffy;
                        result = std::min(result, distance);
                        break;
                    case TAVERN:
                        for(PositionType pos: tavernPositions) {
                            diffx = currentPosition.x - pos.x;
                            diffy = currentPosition.y - pos.y;
                            distance = diffx * diffx + diffy * diffy;
                            result = std::min(result, distance);
                        }
                        break;
                    case MINE:
                        for(PositionType pos: minesPositions) {
                            bool owned = false;
                            for(int i = 0; i < 4; ++i) {
                                owned = (owned || (_graph.heroes[i].mine_positions.find(pos) != _graph.heroes[i].mine_positions.end()));
                            }
                            if(!owned) {
                                diffx = currentPosition.x - pos.x;
                                diffy = currentPosition.y - pos.y;
                                distance = diffx * diffx + diffy * diffy;
                                result = std::min(result, distance);
                            }
                        }
                        break;
                    case MINE1:
                        for(PositionType pos: _graph.heroes[0].mine_positions) {
                            diffx = currentPosition.x - pos.x;
                            diffy = currentPosition.y - pos.y;
                            distance = diffx * diffx + diffy * diffy;
                            result = std::min(result, distance);
                        }
                        break;
                    case MINE2:
                        for(PositionType pos: _graph.heroes[1].mine_positions) {
                            diffx = currentPosition.x - pos.x;
                            diffy = currentPosition.y - pos.y;
                            distance = diffx * diffx + diffy * diffy;
                            result = std::min(result, distance);
                        }
                        break;
                    case MINE3:
                        for(PositionType pos: _graph.heroes[2].mine_positions) {
                            diffx = currentPosition.x - pos.x;
                            diffy = currentPosition.y - pos.y;
                            distance = diffx * diffx + diffy * diffy;
                            result = std::min(result, distance);
                        }
                        break;
                    case MINE4:
                        for(PositionType pos: _graph.heroes[3].mine_positions) {
                            diffx = currentPosition.x - pos.x;
                            diffy = currentPosition.y - pos.y;
                            distance = diffx * diffx + diffy * diffy;
                            result = std::min(result, distance);
                        }
                        break;
                    default: break;
                }
            }

            return ( (result == INT_MAX) ? 0 : result );
        }

    private:
        std::vector<PositionType> _getTavernPositions() const {
            int mapSize = _graph.get_tiles_full().shape()[0];
            std::vector<PositionType> positions;
            for(int i = 0; i < mapSize; ++i) {
                for(int j = 0; j < mapSize; ++j) {
                    PositionType position(i, j);
                    if(_graph.get_tile_from_background(position) == TAVERN) {
                        positions.push_back(position);
                    }
                }
            }
            return positions;
        }

        std::vector<PositionType> _getMinesPositions() const {
            int mapSize = _graph.get_tiles_full().shape()[0];
            std::vector<PositionType> positions;
            for(int i = 0; i < mapSize; ++i) {
                for(int j = 0; j < mapSize; ++j) {
                    PositionType position(i, j);
                    Tile t = _graph.get_tile_from_background(position);
                    if(t == MINE || t == MINE1 || t == MINE2 || t == MINE3 || t == MINE4) {
                        positions.push_back(position);
                    }
                }
            }
            return positions;
        }

        const std::vector<Tile>& _tileTypes;
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
    AdvancedMapAdapter myMapAdapter(state, tileTypes);
    AdvancedMapAdapter::NodeAdapterType nodeStart(start);

    std::function<bool(const AdvancedMapAdapter::NodeAdapterType&)> endCondition = [&](const AdvancedMapAdapter::NodeAdapterType& currentNode) -> bool {
        bool isGoal = false;
        Tile tileType;

        tileType = state.get_tile_from_background_border_check(currentNode.position);
        for(unsigned int i = 0; i < tileTypes.size(); ++i) {
            if(tileTypes[i] == tileType) {
                isGoal = true;
                break;
            }
        }

        return isGoal;
    };

    result = myAStar.getPath(myMapAdapter, nodeStart, endCondition);

    return result;
}


Direction Path::getDirection(const Position& pos1, const Position& pos2) {
    Direction result = Direction::STAY;

    // Be advised - game uses bed signatures for x/y and EW/SN, so it may not look logical here
    if(pos2.x > pos1.x) {
        result = Direction::SOUTH;
    } else if(pos2.x < pos1.x) {
        result = Direction::NORTH;
    } else {
        if(pos2.y > pos1.y) {
            result = Direction::EAST;
        } else if(pos2.y < pos1.y) {
            result = Direction::WEST;
        }
    }

    return result;
}

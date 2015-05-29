#include "Path.h"


Path::PathType Path::getPath(const Tiles& tiles, const Position& start, const Position& end) {
    PathType result;

    // TODO: implement this

    return result;
}


Path::PathType Path::getPath(const Tiles& tiles, const Position& start, Tile tileType) {
    PathType result;

    result = getPath(tiles, start, { tileType });

    return result;
}


Path::PathType Path::getPath(const Tiles& tiles, const Position& start, const std::initializer_list<Tile>& tileTypes) {
    PathType result;

    // TODO: implement this

    return result;
}


Direction Path::getDirection(const Position& pos1, const Position& pos2) {
    Direction result;

    result = Direction::STAY; // TODO: implement this

    return result;
}
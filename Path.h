#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include "tiles.h"
#include "utils.h"

#include <list>
#include <initializer_list>

class Path {
    public:
        typedef std::list<Position> PathType;

    public:
        static PathType getPath(const Tiles& tiles, const Position& start, const Position& end);
        static PathType getPath(const Tiles& tiles, const Position& start, Tile tileType);
        static PathType getPath(const Tiles& tiles, const Position& start, const std::initializer_list<Tile>& tileTypes);

        static Direction getDirection(const Position& pos1, const Position& pos2);

    private:

};

#endif
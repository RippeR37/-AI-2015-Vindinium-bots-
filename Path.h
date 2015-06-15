/**
 * Authors:
 * Damian Dyńdo
 * Mikołaj Nowak
*/

#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include "state.h"
#include "utils.h"

#include <list>
#include <vector>

class Path {
    public:
        typedef std::list<Position> PathType;

    public:
        static PathType getPath(const State& tiles, const Position& start, const Position& end);
        static PathType getPath(const State& tiles, const Position& start, Tile tileType);
        static PathType getPath(const State& tiles, const Position& start, const std::vector<Tile>& tileTypes);
        static PathType getPath(const State& tiles, const Position& start, const std::vector<Tile>& goalTypes, const std::vector<Tile>& avoidTypes);

        static Direction getDirection(const Position& pos1, const Position& pos2);

    private:

};

#endif
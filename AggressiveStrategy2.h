/**
 * Authors:
 * Damian Dyńdo
 * Mikołaj Nowak
*/

#pragma once

#include <vector>

#include "Strategy.h"

class AggressiveStrategy2 : public Strategy {
    public:
        AggressiveStrategy2(const Game& game);
        Direction getMove();
    private:
        static Tile getHeroFromIndex(int index);
    private:
        Tile _playerTile;
        std::vector<Tile> _goal;
        std::vector<Tile> _avoid;
        std::vector<Tile> _tavern;
};


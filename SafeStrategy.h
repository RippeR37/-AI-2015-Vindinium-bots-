#pragma once

#include <vector>

#include "Strategy.h"

class SafeStrategy : public Strategy {
    public:
        SafeStrategy(const Game& game);
        Direction getMove();
    private:
        static Tile getHeroFromIndex(int index);
    private:
        Tile _playerTile;
        std::vector<Tile> _goal;
        std::vector<Tile> _avoid;
        std::vector<Tile> _tavern;
};


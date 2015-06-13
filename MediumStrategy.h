#pragma once

#include <vector>

#include "Strategy.h"

class MediumStrategy : public Strategy {
    public:
        MediumStrategy(const Game& game);
        Direction getMove();
    private:
        static Tile getHeroFromIndex(int index);
    private:
        Tile _playerTile;
        std::vector<Tile> _goal;
        std::vector<Tile> _avoid;
        std::vector<Tile> _tavern;
};


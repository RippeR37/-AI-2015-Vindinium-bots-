#pragma once

#include "game.h"

#include <vector>

struct Bot
{
    public:
        Bot(const Game& game);

        void crunch_it_baby(const Game& game, const OmpFlag& continue_flag, const double& start_time, const double& duration);
        Direction get_move(const Game& game) const;
        void advance_game(Game& game, const Direction& direction);

        static Tile getHeroFromIndex(int index);

    private:
        int _playerIndex;
        Tile _playerMine;
        std::vector<Tile> _otherMines;

};

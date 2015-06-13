#pragma once

#include "game.h"
#include "Strategy.h"

struct Bot
{
    Bot(const Game& game, Rng& rng);

    void
    crunch_it_baby(const Game& game, const OmpFlag& continue_flag, const double& start_time, const double& duration);

    Direction
    get_move(const Game& game);

    void
    advance_game(Game& game, const Direction& direction);

    ~Bot();

private:

    void _savePriorities();

    std::vector<std::pair<Strategy*,std::vector<int>>> _strategy;
    Rng& _rng;
    int _countdown;
    int _current;
    int _beginMines;
    int _beginLife;

};



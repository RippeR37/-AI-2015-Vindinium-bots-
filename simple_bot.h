#pragma once

#include "game.h"
#include "SimpleStrategy.h"
#include "AggressiveStrategy.h"

struct Bot
{
    Bot(const Game& game);

    void
    crunch_it_baby(const Game& game, const OmpFlag& continue_flag, const double& start_time, const double& duration);

    Direction
    get_move(const Game& game);

    void
    advance_game(Game& game, const Direction& direction);

private:

    AggressiveStrategy _strategy;

};



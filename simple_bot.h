/**
 * Authors:
 * Damian Dyńdo
 * Mikołaj Nowak
*/

#pragma once

#include "game.h"
#include "SimpleStrategy.h"

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

    SimpleStrategy _strategy;

};



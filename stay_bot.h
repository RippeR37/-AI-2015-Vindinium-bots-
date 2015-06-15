/**
 * Authors:
 * Damian Dyńdo
 * Mikołaj
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
    get_move(const Game& game) const;

    void
    advance_game(Game& game, const Direction& direction);

private:

    Rng& rng;
    mutable SimpleStrategy strategy;

};



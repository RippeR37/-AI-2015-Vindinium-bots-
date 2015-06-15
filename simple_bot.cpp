/**
 * Authors:
 * Damian Dyńdo
 * Mikołaj Nowak
*/

#include "simple_bot.h"

Bot::Bot(const Game& game) :
    _strategy(game)
{
}

void
Bot::crunch_it_baby(const Game& game, const OmpFlag& continue_flag, const double& start_time, const double& duration_max)
{
}

Direction
Bot::get_move(const Game& game)
{
    return _strategy.getMove();
}

void
Bot::advance_game(Game& game, const Direction& direction)
{
}


#include "stay_bot.h"

Bot::Bot(const Game& game) :
    rng(rng), strategy(game)
{
}

void
Bot::crunch_it_baby(const Game& game, const OmpFlag& continue_flag, const double& start_time, const double& duration_max)
{
}

Direction
Bot::get_move(const Game& game) const
{
    typedef UniformRng<uint8_t> UniformRngUInt8;
    UniformRngUInt8 uniform(rng, 5);
    //return static_cast<Direction>(uniform());
    return Direction::STAY;
}

void
Bot::advance_game(Game& game, const Direction& direction)
{
}


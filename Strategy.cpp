/**
 * Authors:
 * Damian Dyńdo
 * Mikołaj Nowak
*/

#include "Strategy.h"

Strategy::Strategy(const Game& game) : _game(game) {
    _heroNumber = _game.state.next_hero_index;
}


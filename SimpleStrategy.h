/**
 * Authors:
 * Damian Dyńdo
 * Mikołaj Nowak
*/

#pragma once

#include <vector>

#include "Strategy.h"

class SimpleStrategy : public Strategy {
    public:
        SimpleStrategy(const Game& game);
        Direction getMove();
    private:
        bool _scheduledUpdate;
        void _newGoal();
        std::vector<Tile> _goal;
};


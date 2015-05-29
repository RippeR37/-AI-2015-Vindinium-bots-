#pragma once

#include "utils.h"
#include "game.h"

class Strategy {
    public:
        Strategy(const Game& game);
        virtual Direction getMove() = 0;
    protected:
        const Game& _game;
};


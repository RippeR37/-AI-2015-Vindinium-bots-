#pragma once

#include "utils.h"
#include "game.h"

class Strategy {
    public:
        Strategy(Game& game);
        virtual Direction getMove() = 0;
    protected:
        Game& _game;
};


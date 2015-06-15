/**
 * Authors:
 * Damian Dyńdo
 * Mikołaj Nowak
*/

#include "SafeStrategy.h"
#include "Path.h"

SafeStrategy::SafeStrategy(const Game& game) : Strategy(game) {
    Tile playerMine;

    switch(_heroNumber) {
        case 0: playerMine = MINE1; _playerTile = HERO1; break;
        case 1: playerMine = MINE2; _playerTile = HERO2; break;
        case 2: playerMine = MINE3; _playerTile = HERO3; break;
        case 3: playerMine = MINE4; _playerTile = HERO4; break;
        default: playerMine = UNKNOWN; break;
    }

    for(Tile t: {MINE, MINE1, MINE2, MINE3, MINE4}) {
        if(t != playerMine) {
            _goal.push_back(t);
        }
    }

    for(Tile t: {HERO1, HERO2, HERO3, HERO4}) {
        if(t != _playerTile) {
            _avoid.push_back(t);
        }
    }

    _tavern.push_back(TAVERN);
}

Direction SafeStrategy::getMove() {
    int health = _game.state.heroes[_heroNumber].life;

    Path::PathType path1 = Path::getPath(_game.state, _game.state.heroes[_heroNumber].position, _goal, _avoid);
    Path::PathType path2 = Path::getPath(_game.state, _game.state.heroes[_heroNumber].position, _tavern, _avoid);

    Path::PathType path;

    if(health-(int)path1.size() < 50) {
        path = path2;
    } else {
        path = path1;
    }

    if(path.size() == 0) {
        return STAY;
    }

    return Path::getDirection(_game.state.heroes[_heroNumber].position, path.front());
}

Tile SafeStrategy::getHeroFromIndex(int index) {
    Tile result;

    switch(index) {
        case 0: result = Tile::HERO1; break;
        case 1: result = Tile::HERO2; break;
        case 2: result = Tile::HERO3; break;
        case 3: result = Tile::HERO4; break;

        default: result = Tile::UNKNOWN;
    }

    return result;
}


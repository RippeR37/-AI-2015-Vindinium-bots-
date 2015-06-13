#include "AggressiveStrategy.h"
#include "Path.h"

AggressiveStrategy::AggressiveStrategy(const Game& game) : Strategy(game) {
    int heroNumber = _game.state.next_hero_index;
    Tile playerMine;

    switch(heroNumber) {
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

Direction AggressiveStrategy::getMove() {
    int heroNumber = _game.state.next_hero_index;

    std::vector<Tile> goal = _goal;

    for(int i=0; i<4; ++i) {
        if(i != heroNumber && _game.state.heroes[i].mine_positions.size() > 0) {
            
        }
    }

    Path::PathType path1 = Path::getPath(_game.state, _game.state.heroes[heroNumber].position, _goal);
    Path::PathType path2 = Path::getPath(_game.state, _game.state.heroes[heroNumber].position, _tavern, _avoid);

    int health = _game.state.heroes[heroNumber].life;

    Path::PathType path;

    if(health < 20) {
        path = path2;
    } else {
        path = path1;
    }

    if(path.size() == 0) {
        return STAY;
    }

    return Path::getDirection(_game.state.heroes[heroNumber].position, path.front());
}

Tile AggressiveStrategy::getHeroFromIndex(int index) {
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


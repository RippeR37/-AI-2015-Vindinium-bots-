#include "smart_bot.h"
#include "utils.h"
#include "Path.h"

Bot::Bot(const Game& game) {
    _playerIndex = game.state.next_hero_index;

    switch(_playerIndex) {
        case 0:  _playerMine = MINE1;   break;
        case 1:  _playerMine = MINE2;   break;
        case 2:  _playerMine = MINE3;   break;
        case 3:  _playerMine = MINE4;   break;
        default: _playerMine = UNKNOWN; break;
    }

    for(Tile t : {MINE, MINE1, MINE2, MINE3, MINE4}) {
        if(t != _playerMine) {
            _otherMines.push_back(t);
        }
    }
}

void Bot::crunch_it_baby(const Game&, const OmpFlag&, const double&, const double&)
{
    // empty
}

Direction Bot::get_move(const Game& game) const
{
    const Position& playerPosition = game.state.heroes[_playerIndex].position;

    int playerHP = game.state.heroes[_playerIndex].life;
    int minesHold = game.state.heroes[_playerIndex].mine_positions.size();

    Path::PathType pathToMine;
    Path::PathType pathToTavern;
    Path::PathType pathToEnemy[4];
    std::vector<Tile> goalTavern = { Tile::TAVERN };

    // List enemies that are stronger then us (have more HP then we do)
    // unless we want to fight specific hero, we should avoid stronger heroes then us
    std::vector<Tile> strongerEnemies;
    for(int i = 0; i < 4; ++i) {
        if(i != _playerIndex) {
            if(game.state.heroes[i].life > game.state.heroes[_playerIndex].life) {
                strongerEnemies.push_back(getHeroFromIndex(i));
            }
        }
    }
    int minesCount = 0;
    int mapSize = game.background_tiles.shape()[0];
    for(int i = 0; i < mapSize; ++i) {
        for(int j = 0; j < mapSize; ++j) {
            Position position(i, j);
            Tile t = game.state.get_tile_from_background(position);
            if(t == MINE || t == MINE1 || t == MINE2 || t == MINE3 || t == MINE4) {
                minesCount++;
            }
        }
    }
    double minesFactor = minesHold * 85 / minesCount;

    // If player is wounded and have small number of health go to tavern to regain it (but be careful of enemies)
    // be advised, that if player's hp is smaller than 21 then he's best bet is to go to tavern
    pathToTavern = Path::getPath(game.state, playerPosition, goalTavern, strongerEnemies);
    if((playerHP < std::min(75.0, minesFactor * minesHold)) ||
       (playerHP < 21 && minesHold > 0) ||
       (playerHP < 75 && pathToTavern.size() < 3 && pathToTavern.size() > 0))
    {
        if(pathToTavern.size() > 0) {
            return Path::getDirection(playerPosition, pathToTavern.front());
        } else {
            return Direction::STAY; // we can't get to tavern
        }
    }

    // Up here - player is pretty healthy and it's not good choice to go to tavern
    // Next target would be wealthy (as in owning a lot of mines) enemies
    // If enemy has lower health then us, and has some mines and are not far from us it's good idea to go after them
    int bestEnemyCost = -1;
    Direction bestEnemyDirection = Direction::STAY;
    int bestEnemyIndex = 0;

    for(int enemyIndex = 0; enemyIndex < 4; ++enemyIndex) {
        if(enemyIndex != _playerIndex) {
            // This is not us, so let's see how for is he and how many mines does he have
            int enemyMinesHold = game.state.heroes[enemyIndex].mine_positions.size();
            int enemyHP = game.state.heroes[enemyIndex].life;

            // Check if we have a chance to win
            if(enemyHP < playerHP) {
                // We do, so calculate if it's work for us
                int currentEnemyCost = 0;
                std::vector<Tile> enemyGoal = { getHeroFromIndex(enemyIndex) };
                pathToEnemy[enemyIndex] = Path::getPath(game.state, playerPosition, enemyGoal, strongerEnemies);

                if(pathToEnemy[enemyIndex].size() > 0) {
                    currentEnemyCost = (6 * enemyMinesHold * enemyMinesHold) / pathToEnemy[enemyIndex].size();

                    if(enemyHP < playerHP - 20 && pathToEnemy[enemyIndex].size() < 2 && enemyMinesHold > 1) {
                        currentEnemyCost = currentEnemyCost + 500;
                    }

                    if (currentEnemyCost > bestEnemyCost) {
                        bestEnemyCost = currentEnemyCost;
                        bestEnemyDirection = Path::getDirection(playerPosition, pathToEnemy[enemyIndex].front());
                        bestEnemyIndex = enemyIndex;
                    }
                }
            }
        }
    }

    // Now let's see what is the distance to nearest mine -if it's short then it might be better for us to take it
    // instead of fighting
    int costForMine = -1;
    pathToMine = Path::getPath(game.state, playerPosition, _otherMines, strongerEnemies);
    Direction directionToMine = Direction::STAY;

    if(pathToMine.size() > 0) {
        costForMine = (20 - pathToMine.size()) * 8;
        directionToMine = Path::getDirection(playerPosition, pathToMine.front());
    }

    if(bestEnemyCost > costForMine) {
        return bestEnemyDirection;
    } else {
        return directionToMine;
    }
}

void Bot::advance_game(Game& game, const Direction& direction)
{
    // empty
}


Tile Bot::getHeroFromIndex(int index) {
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


/**
 * Authors:
 * Damian Dyńdo
 * Mikołaj Nowak
*/

#include "learning_bot.h"
#include "AggressiveStrategy.h"
#include "AggressiveStrategy2.h"
#include "MediumStrategy.h"
#include "SafeStrategy.h"

#include <iostream>
#include <fstream>

Bot::Bot(const Game& game, Rng& rng) :
    _rng(rng)
{
    std::ifstream in("../learningdata.txt");
    _strategy.push_back(std::make_pair(new AggressiveStrategy(game),std::vector<int>()));
    _strategy.push_back(std::make_pair(new AggressiveStrategy2(game),std::vector<int>()));
    _strategy.push_back(std::make_pair(new MediumStrategy(game),std::vector<int>()));
    _strategy.push_back(std::make_pair(new SafeStrategy(game),std::vector<int>()));
    if(in) {
        for(int i=0; i<4; ++i) {
            _strategy[i].second.resize(10);
            for(int j=0; j<10; ++j) {
                in >> _strategy[i].second[j];
            }
        }
    } else {
        for(int i=0; i<4; ++i) {
            _strategy[i].second.resize(10);
            for(int j=0; j<10; ++j) {
                _strategy[i].second[j] = 1;
            }
        }
    }
    in.close();
    _countdown = _current = _beginMines = 0;
    _beginLife = 100;
}

void
Bot::crunch_it_baby(const Game& game, const OmpFlag& continue_flag, const double& start_time, const double& duration_max)
{
}

Direction
Bot::get_move(const Game& game)
{
    int heroNumber = game.state.next_hero_index;

    int health = game.state.heroes[heroNumber].life;
    int priorsum = 0;
    if(_countdown-- != 0) {
        std::cout << "Current strategy: " << _current << std::endl;
        return _strategy[_current].first->getMove();
    } else {
        std::cout << "Changing strategy" << std::endl;
        _countdown = 10;
        _strategy[_current].second[(_beginLife-1)/10] += (game.state.heroes[heroNumber].mine_positions.size() - _beginMines);
        int plus = 1;
        for(int i=0; i<4; ++i) {
            int s = _strategy[i].second[(_beginLife-1)/10];
            if(s < plus) {
                plus = s;
            }
        }
        if(plus <= 0) {
            plus = -plus+1;
        } else {
            plus = 0;
        }
        for(int i=0; i<4; ++i) {
            _strategy[i].second[(_beginLife-1)/10] += plus;
        }
        _savePriorities();
        for(int i=0; i<4; ++i) {
            priorsum += _strategy[i].second[(health-1)/10];
        }
        _beginLife = health;
        _beginMines = game.state.heroes[heroNumber].mine_positions.size();
        typedef UniformRng<uint32_t> UniformRngUInt32;
        UniformRngUInt32 uniform(_rng, priorsum);
        int uni = uniform();
        int sum = 0;
        for(int i=0; i<4; ++i) {
            sum += _strategy[i].second[(_beginLife-1)/10];
            if(uni < sum) {
                _current = i;
                break;
            }
        }
        return _strategy[_current].first->getMove();
    }
    return STAY;
}

void
Bot::advance_game(Game& game, const Direction& direction)
{
}

Bot::~Bot() {
    for(int i=0; i<4; ++i) {
        delete _strategy[i].first;
    }
}

void
Bot::_savePriorities() {
    std::ofstream out("../learningdata.txt");
    for(int i=0; i<4; ++i) {
        for(int j=0; j<10; ++j) {
            out << _strategy[i].second[j] << " ";
        }
        out << std::endl;
    }
    out.close();
}


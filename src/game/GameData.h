//
// Created by user on 04/02/2019.
//

#ifndef DONKEYKONG_GAMEDATA_H
#define DONKEYKONG_GAMEDATA_H

#include "pch.h"

#define LIFE_PLAYER 3

class GameData
{
public:
    GameData(unsigned int timeBeginMs, unsigned int lifeCount, unsigned int scoreValue);

    static GameData INSTANCE;
    inline static GameData &GetInstance(){ return INSTANCE; };

private:
    sf::Time gameTimer;

    sf::Text playerLife;
    unsigned int lifeNumber;

    sf::Text score;
    unsigned int scoreValue;
};


#endif //DONKEYKONG_GAMEDATA_H

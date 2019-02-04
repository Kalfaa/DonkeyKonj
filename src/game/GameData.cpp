//
// Created by user on 04/02/2019.
//

#include "GameData.h"


GameData::GameData(unsigned int timeBegin, unsigned int lifeCount, unsigned int scoreValue)
: lifeNumber(lifeCount), scoreValue(scoreValue)
{
    gameTimer = sf::milliseconds(timeBegin);
}

GameData GameData::INSTANCE = GameData(0, LIFE_PLAYER, 0);

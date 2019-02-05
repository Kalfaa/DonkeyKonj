//
// Created by user on 04/02/2019.
//

#include "GameData.h"
#include "EntityManager.h"


GameData::GameData(unsigned int timeBegin, unsigned int lifeCount, unsigned int scoreValue, const std::string& fontPath)
: lifeNumber(lifeCount), scoreValue(scoreValue)
{
    font = sf::Font();
    font.loadFromFile(fontPath);
    gameTimer = sf::milliseconds(timeBegin);
}

GameData GameData::INSTANCE = GameData(0, LIFE_PLAYER, 0, EntityManager::MEDIA_PATH + "/emulogic.ttf");


void GameData::setGameTimer(const sf::Time &gameTimer)
{
    this->gameTimer = gameTimer;
}

void GameData::setLifeNumber(unsigned int lifeNumber)
{
    this->lifeNumber = lifeNumber;
    this->playerLife.setString("X " + std::to_string(lifeNumber));
}

void GameData::setScoreValue(unsigned int scoreValue)
{
    this->scoreValue = scoreValue;
    this->score.setString(std::to_string(scoreValue));
}

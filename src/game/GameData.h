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
    GameData(unsigned int timeBeginMs, unsigned int lifeCount, unsigned int scoreValue, const std::string& fontPath);

    static GameData INSTANCE;
    inline static GameData &GetInstance(){ return INSTANCE; }

public:
    void setGameTimer(const sf::Time &gameTimer);
    void setLifeNumber(unsigned int lifeNumber);
    void setScoreValue(unsigned int scoreValue);

private:
    sf::Time gameTimer;

    sf::Text playerLife;
    unsigned int lifeNumber;

    sf::Text score;
    unsigned int scoreValue;

    sf::Font font;
};


#endif //DONKEYKONG_GAMEDATA_H

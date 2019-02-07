//
// Created by user on 04/02/2019.
//

#ifndef DONKEYKONG_GAMEDATA_H
#define DONKEYKONG_GAMEDATA_H

#include "pch.h"

class GameData : public sf::Drawable
{
protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    GameData(unsigned int timeBegin,
            sf::Text timer,
            unsigned int lifeCount,
            sf::Text playerLife,
            unsigned int scoreValue,
            sf::Text score,
            const std::string& fontPath);
    ~GameData() = default;

public:
    void setGameTimer(sf::Int32 gameTimer);
    void setLifeNumber(unsigned int lifeNumber);
    void setScoreValue(unsigned int scoreValue);
    const sf::Int32 getGameTimer() const;
    unsigned int getLifeNumber() const;
    unsigned int getScoreValue() const;

    void updateTimer(sf::Int32 gameTimer);
    void updateLife(unsigned int lifePlayer);
    void updateScore(unsigned int score);

private:
    sf::Text timer;
    sf::Time gameTimer;

    sf::Text playerLife;
    unsigned int lifeNumber;

    sf::Text score;
    unsigned int scoreValue;

    sf::Font font;
};


#endif //DONKEYKONG_GAMEDATA_H

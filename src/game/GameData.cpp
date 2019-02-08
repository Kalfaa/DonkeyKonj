//
// Created by user on 04/02/2019.
//

#include "GameData.h"
#include "EntityManager.h"

GameData::GameData(unsigned int timeBegin, sf::Text &timer, unsigned int lifeCount, sf::Text &playerLife,
                   unsigned int scoreValue, sf::Text &score, const sf::Font &font)
        : lifeNumber(lifeCount), scoreValue(scoreValue), timerValue(timer), playerLife(playerLife), score(score)
{
    timerName.setFont(font);
    timerName.setString("Timer: ");
    timerName.setPosition(timerValue.getPosition().x - (timerName.getGlobalBounds().width / 2),
                          timerValue.getPosition().y);
    timerName.setCharacterSize(15);

    lifeName.setFont(font);
    lifeName.setString("Life X");
    lifeName.setPosition(playerLife.getPosition().x - (lifeName.getGlobalBounds().width / 2),
                         playerLife.getPosition().y);
    lifeName.setCharacterSize(15);

    gameTimer = sf::seconds(timeBegin);
}


void GameData::setGameTimer(sf::Int32 gameTimer)
{
    this->gameTimer = sf::seconds(gameTimer);
    timerValue.setString(std::to_string(gameTimer));
}

void GameData::setLifeNumber(unsigned int lifeNumber)
{
    this->lifeNumber = lifeNumber;
    this->playerLife.setString(std::to_string(lifeNumber));
}

void GameData::setScoreValue(unsigned int scoreValue)
{
    this->scoreValue = scoreValue;
    this->score.setString(std::to_string(scoreValue));
}

const sf::Int32 GameData::getGameTimer() const
{
    return static_cast<const sf::Int32>(gameTimer.asSeconds());
}

unsigned int GameData::getLifeNumber() const
{
    return lifeNumber;
}

unsigned int GameData::getScoreValue() const
{
    return scoreValue;
}

void GameData::updateTimer(sf::Int32 gameTimer)
{
    if (gameTimer != this->gameTimer.asSeconds()) setGameTimer(gameTimer);
}

void GameData::updateLife(unsigned int lifePlayer)
{
    if (lifePlayer != lifeNumber) setLifeNumber(lifePlayer);
}

void GameData::updateScore(unsigned int score)
{
    if (score != scoreValue) setScoreValue(score);
}

void GameData::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(timerName);
    target.draw(timerValue, states);
    target.draw(lifeName);
    target.draw(playerLife, states);
    target.draw(score, states);
}

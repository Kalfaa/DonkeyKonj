//
// Created by Kalfa on 20/12/2018.
//

#ifndef DONKEYKONG_MARIO_H
#define DONKEYKONG_MARIO_H

#include "pch.h"

class Mario
{
public:
    Mario();
    Mario(const sf::Vector2f &posMario, const sf::Texture &mTexture);
    void move(int value);
    void update(sf::Time);
    void render();

private:



private:
    //sf::Vector2f movement;
    int direction ;
    sf::Vector2f posMario;
    sf::Texture mTexture;
    sf::Vector2u _sizeBlock;
    sf::Vector2u _sizeMario;
    sf::Sprite sprite;
public:
    const sf::Sprite &getMPlayer() const;
};


#endif //DONKEYKONG_MARIO_H

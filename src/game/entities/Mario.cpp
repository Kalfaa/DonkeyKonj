//
// Created by Kalfa on 20/12/2018.
//

#include "Mario.h"

//const float playerSpeed = 100.f;

Mario::Mario(const sf::Vector2f &posPlayer, const sf::Texture &mTexture, EntityType type, float playerSpeed)
    : Player(posPlayer, mTexture, type, playerSpeed)
{}

void Mario::render(){}
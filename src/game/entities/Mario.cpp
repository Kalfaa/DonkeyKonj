//
// Created by Kalfa on 20/12/2018.
//

#include "Mario.h"

//const float playerSpeed = 100.f;

Mario::Mario(const sf::Sprite &sprite, const sf::Vector2f &posPlayer, EntityType type, float playerSpeed, SpritesPatterns spritesPtns)
    : Player(sprite, posPlayer, type, playerSpeed, spritesPtns)
{}

void Mario::render(){}
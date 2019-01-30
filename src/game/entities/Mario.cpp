//
// Created by Kalfa on 20/12/2018.
//

#include "Mario.h"
#include "Map.h"

//const float playerSpeed = 100.f;

Mario::Mario(const sf::Sprite &sprite, const sf::Vector2f &posPlayer, EntityType type, float playerSpeed,
             SpritesPatterns spritesPtns)
        : Player(sprite, posPlayer, type, playerSpeed, spritesPtns)
{}

void Mario::render()
{}

void Mario::update(sf::Time time, std::shared_ptr<Map> map)
{
    Player::update(time, map);
}

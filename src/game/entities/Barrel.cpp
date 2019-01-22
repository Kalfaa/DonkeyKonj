//
// Created by theo on 16/01/19.
//

#include "Barrel.h"
#include "Map.h"

Barrel::Barrel(const sf::Sprite &sprite, const sf::Vector2f &posPlayer, EntityType type,
               const SpritesPatterns &patterns)
        : Entity(sprite, posPlayer, type)
{

}

void Barrel::update(sf::Time elapsedTime, Map map)
{
    sf::Vector2f grindLadder(0.f, -BARREL_SPEED * 2); // en attendant de trouver une maniere plus propre
    sf::Vector2f moveJump(0.f, -BARREL_SPEED);
    sf::Vector2f moveNotJump(0.f, +BARREL_SPEED);
    sf::Vector2f movement(0.f, 0.f);
    sf::Vector2f moveDown(0.f, BARREL_SPEED);
    sf::Vector2f moveUp(0.f, -BARREL_SPEED);
    sf::Vector2f moveRight(BARREL_SPEED, 0.f);
    sf::Vector2f moveLeft(-BARREL_SPEED, 0.f);
    sprite.move(moveDown * elapsedTime.asSeconds());
    if (!map.collide(sprite, EntityType::PLATFORM, DOWN)->collide)
    {

    }
    else
    {
        sprite.move(moveUp * elapsedTime.asSeconds());
    }
}

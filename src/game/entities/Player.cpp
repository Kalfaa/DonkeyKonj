//
// Created by user on 25/12/2018.
//

#include "Player.h"

Player::Player(const sf::Vector2f& posPlayer, const sf::Texture& texture, EntityType type, float playerSpeed)
    : Entity(posPlayer, texture, type), playerSpeed(playerSpeed){}

void Player::update(sf::Time elapsedTime)
{
    switch (direction)
    {
        case UP:
            position.y -= playerSpeed;
            break;
        case DOWN:
            position.y += playerSpeed;
            break;
        case LEFT:
            position.x -= playerSpeed;
            break;
        case RIGHT:
            position.x += playerSpeed;
            break;
        default: ;
    }
    sprite.setPosition(position * elapsedTime.asSeconds());
    direction = NONE;
}

void Player::move(Direction direction)
{
    this->direction = direction;
}


//
// Created by user on 25/12/2018.
//

#include <map/Map.h>
#include "Player.h"

Player::Player(const sf::Vector2f& posPlayer, const sf::Texture& texture, EntityType type, float playerSpeed)
    : Entity(posPlayer, texture, type), playerSpeed(playerSpeed){}

void Player::update(sf::Time elapsedTime,Map map)
{
    unsigned int x = static_cast<unsigned int>(sprite.getPosition().x/32 );
    unsigned int y = static_cast<unsigned int>( ((sprite.getPosition().y)+64)/32);
    std::shared_ptr<Entity> entity = map.entity2DArray.at( x).at(y);
    if (entity == nullptr || !entity->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())){
        position.y += playerSpeed;
    }
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


//
// Created by user on 25/12/2018.
//

#include <map/Map.h>
#include "Player.h"


Player::Player(const sf::Vector2f& posPlayer, const sf::Texture& texture, EntityType type, float playerSpeed)
    : Entity(posPlayer, texture, type), playerSpeed(playerSpeed){}

void Player::update(sf::Time elapsedTime,Map map)
{

    sf::Vector2f movement(0.f, 0.f);
    if (!collide_down(map)){
        movement.y += playerSpeed;
    }
    switch (direction)
    {
        /*case UP:
            position.y -= playerSpeed;
            break;*/
        case DOWN:
            movement.y += playerSpeed;
            break;
        case LEFT:
            movement.x -= playerSpeed;
            break;
        case RIGHT:
            movement.x += playerSpeed;
            break;
        default: ;
    }
    sprite.move(movement * elapsedTime.asSeconds());
    direction = NONE;
}

void Player::move(Direction direction)
{
    this->direction = direction;
}

bool Player::collide_down(Map map)
{

    auto x = static_cast<unsigned int>(sprite.getPosition().x) /32 ;
    auto x2 =  static_cast<unsigned int>( (sprite.getPosition().x+MARIO_WIDTH )/32 );
    auto y = static_cast<unsigned int>( ((sprite.getPosition().y)+MARIO_HEIGHT)/32);
    std::shared_ptr<Entity> entity = map.entity3DArray.at(x).at(y);
    std::shared_ptr<Entity> entity2 = map.entity3DArray.at(x2).at(y);
    if(entity!= nullptr){
        if(entity->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())){
            return true;
        }
    }
    if(entity2!= nullptr){
        if(entity2->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())){
            return true;
        }
    }
    return false ;
}




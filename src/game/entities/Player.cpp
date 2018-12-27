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
    if (!collide_down(map)&& playerState!= JUMP){
        movement.y += playerSpeed;
    }else{
        if(playerState==STARTJUMP){
            playerState = JUMP;
            jumpvalue=MARIO_JUMP_MAX ;
        }
    }
    switch (direction)
    {
        case UP:
            position.y -= playerSpeed;
            break;
        case DOWN:
            if(!collide_down(map))
            {
                movement.y += playerSpeed;
            }
            break;
        case LEFT:
            movement.x -= playerSpeed;
            break;
        case RIGHT:
            movement.x += playerSpeed;
            break;
        default: ;
    }
    switch(playerState){
        case JUMP:
            jumpvalue -= MARIO_JUMP_SPEED;
            movement.y -= MARIO_JUMP_SPEED;
            if(jumpvalue<=0){
                playerState=IDLE;
            }
        default:;
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
    std::vector<std::shared_ptr<Entity>> list_entity;
    auto x = static_cast<unsigned int>(sprite.getPosition().x) /32 ;
    auto x2 =  static_cast<unsigned int>( (sprite.getPosition().x+MARIO_WIDTH )/32 );
    auto y = static_cast<unsigned int>( ((sprite.getPosition().y)+MARIO_HEIGHT)/32);

    for (const auto &i : map.entity3DArray.at(x).at(y))
    {
       list_entity.push_back(i) ;
    }
    for (const auto &i : map.entity3DArray.at(x2).at(y))
    {
        list_entity.push_back(i) ;
    }
    for(const auto &entity : list_entity){
        if(entity->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())){
            return true;
        }
    }
    return false ;
}

void Player::jump()
{
    playerState= STARTJUMP;
}

bool Player::checkIfCollideWithLadder(Map map)
{
    return false;
}




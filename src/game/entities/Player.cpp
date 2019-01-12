//
// Created by user on 25/12/2018.
//

#include <map/Map.h>
#include <Game.h>
#include "Player.h"
#include "Ladder.h"

Player::Player(const sf::Sprite& sprite, const sf::Vector2f& posPlayer, EntityType type, float playerSpeed)
    : Entity(sprite, posPlayer, type), playerSpeed(playerSpeed){}

void Player::update(sf::Time elapsedTime,Map map)
{
    sf::Vector2f movement(0.f, 0.f);
    if (!collide_down(map)&& playerState != JUMP && playerState != STARTJUMP  ){
        movement.y += playerSpeed;
        playerState=FALLING;
    }else{
        if(playerState==FALLING){
            playerState=IDLE;
        }
        if(playerState==STARTJUMP)
        {
            printf("jump");
            playerState = JUMP;
            jumpvalue = MARIO_JUMP_MAX;
        }
    }
    switch (direction)
    {
        case UP:
            if(checkIfCollideWithLadder(map)){
                movement.y -= playerSpeed*2;
                printf("ok");
            }
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
    auto left = static_cast<unsigned int>(sprite.getPosition().x) /CASE_AREA ;
    auto right =  static_cast<unsigned int>( (sprite.getPosition().x+MARIO_WIDTH )/CASE_AREA );
    auto bottom = static_cast<unsigned int>( ((sprite.getPosition().y)+MARIO_HEIGHT)/CASE_AREA);

    for (const auto &i : map.entity3DArray.at(bottom).at(left))
    {
        if(i->type==PLATFORM)list_entity.push_back(i) ;
    }
    for (const auto &i : map.entity3DArray.at(bottom).at(right))
    {
        if(i->type==PLATFORM)list_entity.push_back(i) ;
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
    if(FALLING != playerState)playerState= STARTJUMP;
}

bool Player::checkIfCollideWithLadder(Map map)
{
    std::vector<std::shared_ptr<Entity>> list_entity;
    auto left = static_cast<unsigned int>(sprite.getPosition().x) /CASE_AREA;
    auto right =  static_cast<unsigned int>( (sprite.getPosition().x+MARIO_WIDTH )/CASE_AREA );
    auto bottom = static_cast<unsigned int>( ((sprite.getPosition().y)+MARIO_HEIGHT)/CASE_AREA);

    for (const auto &i : map.entity3DArray.at(bottom).at(left))
    {
        if(i->type==LADDER) list_entity.push_back(i) ;
    }
    for (const auto &i : map.entity3DArray.at(bottom).at(right))
    {
        if(i->type==LADDER)list_entity.push_back(i) ;
    }
    for(const auto &entity : list_entity){
        if( entity->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())){
            return true;
        }
    }
    return false ;
}






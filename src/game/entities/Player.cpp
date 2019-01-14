//
// Created by user on 25/12/2018.
//

#include <map/Map.h>
#include <Game.h>
#include "Player.h"
#include "Ladder.h"

Player::Player(const sf::Sprite& sprite, const sf::Vector2f& posPlayer, EntityType type, float playerSpeed, const SpritesPatterns& playerSprites)
    : Entity(sprite, posPlayer, type),
    playerSpeed(playerSpeed), spritesPtns(playerSprites)
{
    MARIO_WIDTH = abs(sprite.getScale().x*sprite.getTextureRect().width);
    MARIO_HEIGHT = abs(sprite.getScale().y*sprite.getTextureRect().height);
}

void Player::update(sf::Time elapsedTime,Map map)
{
    sf::Vector2f grindLadder(0.f, -playerSpeed*2); // en attendant de trouver une maniere plus propre
    sf::Vector2f moveJump(0.f, -MARIO_JUMP_SPEED);
    sf::Vector2f moveNotJump(0.f, +MARIO_JUMP_SPEED);
    sf::Vector2f movement(0.f,0.f);
    sf::Vector2f moveDown(0.f, playerSpeed);
    sf::Vector2f moveUp(0.f, -playerSpeed);
    sf::Vector2f moveRight(playerSpeed, 0.f);
    sf::Vector2f moveLeft(-playerSpeed, 0.f);
    if ( playerState != JUMP && playerState != STARTJUMP  ){
        sprite.move(moveDown * elapsedTime.asSeconds());
        if(!collide(map,EntityType::PLATFORM,DOWN )){
            playerState=FALLING;
        }else{
            sprite.move(moveUp * elapsedTime.asSeconds());
            playerState=IDLE;
        }
    }else{
        //sprite.move(0.f,-playerSpeed);
        if(playerState==STARTJUMP)
        {
            printf("jump");
            playerState = JUMP;
            jumpValue = MARIO_JUMP_MAX;
        }
    }

    switch (direction)
    {
        case UP:
            if(collide(map,EntityType::LADDER,DOWN)){
                sprite.move(grindLadder * elapsedTime.asSeconds());

            }
            break;
        case DOWN:
            /*if(!collide(map,EntityType::PLATFORM,DOWN))
                movement.y += playerSpeed;*/
            break;
        case LEFT:
            sprite.move(moveLeft * elapsedTime.asSeconds());
            if(collide(map,EntityType::PLATFORM,RIGHT))sprite.move(moveRight * elapsedTime.asSeconds());
            break;
        case RIGHT:
            sprite.move(moveRight * elapsedTime.asSeconds());
            if(collide(map,EntityType::PLATFORM,RIGHT))sprite.move(moveLeft * elapsedTime.asSeconds());
            break;
        default: ;
    }
    switch(playerState){
        case JUMP:
            sprite.move(moveJump * elapsedTime.asSeconds());
            if(!collide(map,EntityType::PLATFORM,RIGHT))
            {
                jumpValue -= MARIO_JUMP_SPEED;
            }else{
                sprite.move(moveNotJump * elapsedTime.asSeconds());
                jumpValue =0;
            }
            if(jumpValue<=0){
                playerState=IDLE;
            }
        default:;
    }
    direction = NONE;
}

void Player::move(Direction direction)
{
    this->direction = direction;
}

bool Player::collide(Map map,EntityType entityType,Direction direction)
{
    std::vector<std::shared_ptr<Entity>> list_entity;
    auto left = static_cast<unsigned int>(sprite.getPosition().x) /CASE_AREA ;
    auto right =  static_cast<unsigned int>( (sprite.getPosition().x+MARIO_WIDTH )/CASE_AREA );
    auto bottom = static_cast<unsigned int>( ((sprite.getPosition().y)+MARIO_HEIGHT)/CASE_AREA);
    auto top = static_cast<unsigned int>( ((sprite.getPosition().y))/CASE_AREA);
    unsigned y1;
    unsigned x1;
    unsigned y2;
    unsigned x2;
    switch (direction)
    {
        case UP:
             y1 = top;
             x1 =left ;
             y2 =top ;
             x2 = right ;
            break;
        case DOWN:
             y1 = bottom;
             x1 = left ;
             y2 = bottom ;
             x2 = right ;
             break;
        case LEFT:
            y1 = top;
            x1 = left ;
            y2 = bottom ;
            x2 = left ;
            break;
        case RIGHT:
            y1 =top ;
            x1 = right ;
            y2 = bottom ;
            x2 = right ;
            break;
        default: ;
    }
    for (const auto &i : map.entity3DArray.at(y1).at(x1))
    {
        if(i->type==entityType)list_entity.push_back(i) ;
    }

        for (const auto &i : map.entity3DArray.at(y2).at(x2))
        {
            if (i->type == entityType)list_entity.push_back(i);
        }


    for (const auto &i : map.entity3DArray.at(y2-1).at(x2))
        {
            if (i->type == entityType)list_entity.push_back(i);
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







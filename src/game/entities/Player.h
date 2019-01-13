//
// Created by user on 25/12/2018.
//

#ifndef DONKEYKONG_PLAYER_H
#define DONKEYKONG_PLAYER_H

#include "pch.h"
#include "Entity.h"
#include <map/Map.h>


#define MARIO_JUMP_MAX 3500
#define MARIO_JUMP_SPEED 700
class Player : public Entity
{
public:
    Player(const sf::Sprite&, const sf::Vector2f& posPlayer, EntityType, float playerSpeed);
    ~Player() override = default;
     int MARIO_HEIGHT ;
     int MARIO_WIDTH;
public:
    void update(sf::Time,Map map) ;
    void move(Direction elapsedTime);
    void jump();
    PlayerState playerState = IDLE;

protected:
    float playerSpeed;
    Direction direction;
    bool collide(Map map,EntityType entityType,Direction direction);
    float jumpvalue;
};


#endif //DONKEYKONG_PLAYER_H

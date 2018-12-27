//
// Created by user on 25/12/2018.
//

#ifndef DONKEYKONG_PLAYER_H
#define DONKEYKONG_PLAYER_H

#include "pch.h"
#include "Entity.h"
#include <map/Map.h>

#define MARIO_HEIGHT 53
#define MARIO_WIDTH 45

class Player : public Entity
{
public:
    Player(const sf::Vector2f& posPlayer, const sf::Texture&, EntityType, float playerSpeed);
    ~Player() override = default;

public:
    void update(sf::Time,Map map) ;
    void move(Direction elapsedTime);

protected:
    float playerSpeed;
    Direction direction;
    bool collide_down(Map map);
    void jump();
    PlayerState playerState = IDLE;
};


#endif //DONKEYKONG_PLAYER_H

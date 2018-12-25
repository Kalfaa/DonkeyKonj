//
// Created by user on 25/12/2018.
//

#ifndef DONKEYKONG_PLAYER_H
#define DONKEYKONG_PLAYER_H

#include "pch.h"
#include "Entity.h"

class Player : public Entity
{
public:
    Player(const sf::Vector2f& posPlayer, const sf::Texture&, EntityType, float playerSpeed);
    ~Player() override = default;

public:
    void update(sf::Time) override;
    void move(Direction elapsedTime);

protected:
    float playerSpeed;
    Direction direction;
};


#endif //DONKEYKONG_PLAYER_H

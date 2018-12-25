//
// Created by Kalfa on 20/12/2018.
//

#ifndef DONKEYKONG_MARIO_H
#define DONKEYKONG_MARIO_H

#include "pch.h"
#include "Player.h"

class Mario : public Player
{
public:
    Mario(const sf::Vector2f& posMario, const sf::Texture&, EntityType, float playerSpeed);

    ~Mario() override = default;

public:
    //void update(sf::Time time) override;
    //void move(Direction direction);
    void render();

private:
    Direction direction;
};


#endif //DONKEYKONG_MARIO_H

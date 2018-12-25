//
// Created by Kalfa on 20/12/2018.
//

#ifndef DONKEYKONG_MARIO_H
#define DONKEYKONG_MARIO_H

#include "pch.h"
#include "Entity.h"

class Mario : public Entity
{
public:
    Mario(const sf::Vector2f &posMario, const sf::Texture &mTexture, EntityType);

    ~Mario() override = default;

public:
    void update(sf::Time time1) override;
    void move(Direction direction);
    void render();

private:
    Direction direction;
};


#endif //DONKEYKONG_MARIO_H

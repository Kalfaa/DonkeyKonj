//
// Created by user on 26/12/2018.
//

#ifndef DONKEYKONG_FLOOR_H
#define DONKEYKONG_FLOOR_H

#include "pch.h"
#include "StaticEntity.h"

class Platform : public StaticEntity
{
public:
    Platform();

    Platform(const sf::Vector2f &position, const sf::Texture &, EntityType type);
};


#endif //DONKEYKONG_FLOOR_H

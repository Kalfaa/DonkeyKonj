//
// Created by user on 26/12/2018.
//

#ifndef DONKEYKONG_LADDER_H
#define DONKEYKONG_LADDER_H

#include "pch.h"
#include "StaticEntity.h"

//class Map;

class Ladder : public StaticEntity
{
public:
    Ladder(const sf::Sprite &, const sf::Vector2f &position, EntityType type);
};


#endif //DONKEYKONG_LADDER_H

//
// Created by user on 25/12/2018.
//

#ifndef DONKEYKONG_STATICENTITY_H
#define DONKEYKONG_STATICENTITY_H

#include "pch.h"
#include "Entity.h"

class StaticEntity : public Entity
{
public:
    StaticEntity(const sf::Sprite &, const sf::Vector2f &position, EntityType type);
};


#endif //DONKEYKONG_STATICENTITY_H

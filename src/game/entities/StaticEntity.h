//
// Created by user on 25/12/2018.
//

#ifndef DONKEYKONG_STATICENTITY_H
#define DONKEYKONG_STATICENTITY_H

class Map;

#include "pch.h"
#include "Entity.h"


class StaticEntity : public Entity
{
public:
    StaticEntity(const sf::Sprite &, const sf::Vector2f &position, EntityType type);

    void update(sf::Time time1) override;
};


#endif //DONKEYKONG_STATICENTITY_H

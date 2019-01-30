//
// Created by user on 25/12/2018.
//

#include "StaticEntity.h"
#include "Map.h"

StaticEntity::StaticEntity(const sf::Sprite &sprite, const sf::Vector2f &position, EntityType type)
        : Entity(sprite, position, type)
{}

void StaticEntity::update(sf::Time time1, std::shared_ptr<Map> map)
{
}

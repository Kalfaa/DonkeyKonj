//
// Created by Damso on 25/12/2018.
//

#include "Entity.h"
#include "Map.h"


Entity::Entity(const sf::Sprite &sprite, EntityType type)
        : sprite(sprite), type(type)
{
    position = sprite.getPosition();
    texture = (*sprite.getTexture());
    size = texture.getSize();
}

Entity::Entity(const sf::Sprite &sprite, const sf::Vector2f &pos, EntityType type)
        : sprite(sprite), type(type)
{
    position = sprite.getPosition();
    this->sprite.setPosition(pos);
    texture = (*sprite.getTexture());
    size = texture.getSize();
}

const sf::Sprite &Entity::getSprite() const
{
    return sprite;
}

Entity::Entity(EntityType)
{
}

void Entity::update(sf::Time, Map)
{

}

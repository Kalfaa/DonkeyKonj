#include "pch.h"
#include "Entity.h"

Entity::Entity(const sf::Sprite& sprite, EntityType type)
    : sprite(sprite), type(type)
{
    position = sprite.getPosition();
    texture = (*sprite.getTexture());
    size = texture.getSize();
}

Entity::Entity(const sf::Vector2f &pos, const sf::Texture &texture, EntityType type)
    : texture(texture), type(type)
{
    sprite.setPosition(pos);
    position = pos;
    sprite.setTexture(texture);
    size = texture.getSize();
}

const sf::Sprite &Entity::getSprite() const
{
    return sprite;
}

void Entity::update(sf::Time)
{

}

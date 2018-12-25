//
// Created by Kalfa on 20/12/2018.
//

#include "Mario.h"

const float PlayerSpeed = 100.f;

Mario::Mario(const sf::Vector2f &posMario, const sf::Texture &mTexture, EntityType type) : Entity(posMario, mTexture, type)
{
    size = mTexture.getSize();
    sprite = sf::Sprite();
    sprite.setTexture(mTexture);
    sprite.setPosition(posMario);

}

void Mario::update(sf::Time elapsedTime)
{
    switch (direction)
    {
        case UP:
            position.y -= PlayerSpeed;
            break;
        case DOWN:
            position.y += PlayerSpeed;
            break;
        case LEFT:
            position.x -= PlayerSpeed;
            break;
        case RIGHT:
            position.x += PlayerSpeed;
            break;
        default: ;
    }
    sprite.setPosition(position * elapsedTime.asSeconds());
    direction = DEFAULT;
}

void Mario::move(Direction direction)
{
    this->direction = direction;
}

void Mario::render()
{

}
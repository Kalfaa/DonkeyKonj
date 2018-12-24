//
// Created by Kalfa on 20/12/2018.
//

#include "Mario.h"

const float PlayerSpeed = 100.f;

Mario::Mario(const sf::Vector2f &posMario, const sf::Texture &mTexture) : posMario(posMario), mTexture(mTexture)
{
    sizeMario = mTexture.getSize();
    sprite = sf::Sprite();
    sprite.setTexture(mTexture);
    sprite.setPosition(posMario);

}

void Mario::update(sf::Time elapsedTime)
{
    switch (direction)
    {
        case UP:
            posMario.y -= PlayerSpeed;
            break;
        case DOWN:
            posMario.y += PlayerSpeed;
            break;
        case LEFT:
            posMario.x -= PlayerSpeed;
            break;
        case RIGHT:
            posMario.x += PlayerSpeed;
            break;
        default: ;
    }
    sprite.setPosition(posMario * elapsedTime.asSeconds());
    direction = DEFAULT;
}

void Mario::move(Direction direction)
{
    this->direction = direction;
}

Mario::Mario() = default;

void Mario::render()
{

}

const sf::Sprite &Mario::getMPlayer() const
{
    return sprite;
}

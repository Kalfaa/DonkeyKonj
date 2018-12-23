//
// Created by Kalfa on 20/12/2018.
//

#include "Mario.h"
enum Direction { UP=1,DOWN= 2, LEFT = 3, RIGHT = 4 };
const float PlayerSpeed = 100.f;
Mario::Mario(const sf::Vector2f &posMario, const sf::Texture &mTexture) : posMario(posMario), mTexture(mTexture) {
    _sizeMario = mTexture.getSize();
    sprite =  sf::Sprite();
    sprite.setTexture(mTexture);
    sprite.setPosition(posMario);

}

void Mario::update(sf::Time elapsedTime) {
    if (direction==UP)
        posMario.y -= PlayerSpeed ;
    if (direction==DOWN)
        posMario.y += PlayerSpeed;
    if (direction==LEFT)
        posMario.x -= PlayerSpeed;
    if (direction==RIGHT)
        posMario.x += PlayerSpeed;
    sprite.setPosition(posMario* elapsedTime.asSeconds());
    direction =0;
}

void Mario::move(int value)
{
    direction=value;
}

Mario::Mario()
{

}

void Mario::render()
{

}

const sf::Sprite &Mario::getMPlayer() const
{
    return sprite;
}

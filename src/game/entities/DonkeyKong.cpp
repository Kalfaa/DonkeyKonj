//
// Created by Kalfa on 28/01/2019.
//

#include "DonkeyKong.h"

DonkeyKong::DonkeyKong(const sf::Sprite &sprite, const sf::Vector2f &posPlayer, EntityType type,
               const SpritesPatterns &donkeyKong)
        : Entity(sprite, posPlayer, type),
          patterns(donkeyKong)
{
    HP =3;
    state =GRINDING;
    timeAnimation =0;
}

void DonkeyKong::update(sf::Time elapsedTime, Map map) {
    sf::Vector2f grindLadder(0.f, -DK_SPEED*2); // en attendant de trouver une maniere plus propre
    sf::Vector2f moveJump(0.f, -DK_SPEED);
    sf::Vector2f moveNotJump(0.f, +DK_SPEED);
    sf::Vector2f movement(0.f,0.f);
    sf::Vector2f moveDown(0.f, DK_SPEED);
    sf::Vector2f moveUp(0.f, -DK_SPEED);
    sf::Vector2f moveRight(DK_SPEED, 0.f);
    sf::Vector2f moveLeft(-DK_SPEED, 0.f);



    timeAnimation += elapsedTime.asMilliseconds();

    sprite.move(moveDown * elapsedTime.asSeconds());
    if(!map.collide(sprite,EntityType::PLATFORM,DOWN )->collide ){
    }else{
        sprite.move(moveUp * elapsedTime.asSeconds());
    }
}

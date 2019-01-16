//
// Created by theo on 16/01/19.
//

#include "Barrel.h"

Barrel::Barrel(const sf::Sprite &, const sf::Vector2f &posPlayer, EntityType, float playerSpeed,
               const Barrel::SpritesPatterns &) : Entity(sprite, posPlayer, type) {

}

void Barrel::update(sf::Time,Map map) {

    /*if(!map.collide(sprite,EntityType::PLATFORM,DOWN )){
        playerState=FALLING;
    }else{
        sprite.move(moveUp * elapsedTime.asSeconds());
        playerState=IDLE;
    }*/
}

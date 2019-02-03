//
// Created by theo on 01/02/19.
//

#include "Peach.h"

Peach::Peach(const sf::Sprite &sprite, const sf::Vector2f &posPlayer, EntityType type,
        const Peach::SpritesPatterns &spritesPatterns) :Entity(sprite, posPlayer, type),
        patterns(spritesPatterns)
{

}

void Peach::update(sf::Time elapsedTime) {

}

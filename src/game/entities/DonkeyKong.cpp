//
// Created by Kalfa on 28/01/2019.
//

#include "DonkeyKong.h"

DonkeyKong::DonkeyKong(const sf::Sprite &sprite, const sf::Vector2f &posPlayer, EntityType type,
               const SpritesPatterns &donkeyKong)
        : Entity(sprite, posPlayer, type),
          patterns(donkeyKong)
{

}
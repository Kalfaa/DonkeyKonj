//
// Created by DamSo on 16/01/2019.
//

#include "BonusItem.h"

BonusItem::BonusItem(const sf::Sprite &sprite, const sf::Vector2f &position, EntityType type, unsigned int valueBonus,
                     const sf::Sprite &spBonus)
        : StaticEntity(sprite, position, type),
          value(valueBonus), valueSprite(spBonus)
{
}

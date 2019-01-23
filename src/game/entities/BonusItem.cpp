//
// Created by DamSo on 16/01/2019.
//

#include "BonusItem.h"
#include "Map.h"

BonusItem::BonusItem(const sf::Sprite &sprite, const sf::Vector2f &position, EntityType type, unsigned int valueBonus,
                     const sf::Sprite &spBonus)
        : StaticEntity(sprite, position, type),
          value(valueBonus), valueSprite(spBonus)
{
}

unsigned int BonusItem::catchBonus()
{
    isCatch = true;
    valueSprite.setPosition(sprite.getPosition());
    sprite = valueSprite;
    return value;
}

void BonusItem::update(sf::Time time1, Map map)
{
    if(!isCatch) this->catchBonus();
    //else map.removeEntityToMatrix(this);
}

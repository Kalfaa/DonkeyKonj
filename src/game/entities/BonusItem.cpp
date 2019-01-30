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

unsigned int BonusItem::catchBonus(sf::Time elapsedTime)
{
    isCatch = true;
    valueSprite.setPosition(sprite.getPosition());
    sprite = valueSprite;
    //timeValueAppear = elapsedTime;
    return value;
}

void BonusItem::update(sf::Time elapsedTime, std::shared_ptr<Map> map)
{
    if (map->collide(sprite, EntityType::PLAYER, RIGHT)->collide)
    {
        if (!isCatch)
        {
            map->removeEntityToMatrix(this);
            //this->catchBonus(elapsedTime);
        }
    }
    //if(elapsedTime - timeValueAppear >= timeValueStay) map.removeEntityToMatrix(this);
    //else map.removeEntityToMatrix(this);
}

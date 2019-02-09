//
// Created by DamSo on 16/01/2019.
//

#ifndef DONKEYKONG_BONUSITEM_H
#define DONKEYKONG_BONUSITEM_H

#include "pch.h"
#include "StaticEntity.h"

//class Map;


class BonusItem : public StaticEntity
{
public:
    BonusItem(const sf::Sprite &sprite, const sf::Vector2f &position, EntityType type, unsigned int valueBonus,
              const sf::Sprite &valueSprite);

public:
    unsigned int catchBonus(sf::Time elapsedTime);
    unsigned int consume();

    void update(sf::Time time1) override;

public:
    unsigned int value;
    bool isCatch = false;
    bool consumed = false;

private:
    sf::Sprite valueSprite;
    //sf::Time timeValueStay;
    //sf::Time timeValueAppear;
};


#endif //DONKEYKONG_BONUSITEM_H
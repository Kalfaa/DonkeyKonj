//
// Created by Kalfa on 28/01/2019.
//

#ifndef DONKEYKONG_DONKEYKONG_H
#define DONKEYKONG_DONKEYKONG_H


#include "StaticEntity.h"

class DonkeyKong : public Entity
{

public:
    enum PatternType
    {
        donkeyFace,
        barrelVertical,
        barrelHorizontal,

    };
    typedef std::map<DonkeyKong::PatternType, std::vector<sf::Sprite>> SpritesPatterns;
    enum BarrelState
    {
        LEFT,
        RIGHT,
        SOONRIGHT,
        SOONLEFT,
        GRINDING,
        FALL,
        NONE,
    };
    DonkeyKong(const sf::Sprite&, const sf::Vector2f& posPlayer, EntityType,const SpritesPatterns &);
    SpritesPatterns patterns;
};




#endif //DONKEYKONG_DONKEYKONG_H

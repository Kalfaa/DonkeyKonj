//
// Created by Kalfa on 28/01/2019.
//

#ifndef DONKEYKONG_DONKEYKONG_H
#define DONKEYKONG_DONKEYKONG_H


#include "StaticEntity.h"
#include "Map.h"


#define DK_SPEED 65

class Map;
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
    enum DonkeyState
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
    int HP;
    DonkeyState state ;
    bool invulnerable;
    void update(sf::Time elapsedTime, Map map );
    int timeAnimation;

};




#endif //DONKEYKONG_DONKEYKONG_H

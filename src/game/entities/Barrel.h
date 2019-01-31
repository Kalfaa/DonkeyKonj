//
// Created by theo on 16/01/19.
//

#ifndef DONKEYKONG_BARREL_H
#define DONKEYKONG_BARREL_H

#include "Entity.h"
#include "pch.h"
#include "Map.h"

class Map;

#define BARREL_SPEED 65

class Barrel : public Entity
{
public:
    enum PatternType
    {
        barrel,
        barrelVertical,
        barrelHorizontal,

    };
    typedef std::map<Barrel::PatternType, std::vector<sf::Sprite>> SpritesPatterns;
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

public:
    Barrel(const sf::Sprite &, const sf::Vector2f &posPlayer, EntityType, const SpritesPatterns &);
    ~Barrel() override = default;

public:
    sf::FloatRect getHitboxLadder();

    void update(sf::Time elapsedTime) override;

public:
    SpritesPatterns patterns;
    BarrelState barrelState;
    int countBeforeGrind;
    std::shared_ptr<CollideRes> grindingLadder = std::make_shared<CollideRes>(false, std::shared_ptr<Entity>());
private:
    int timeAnimation;

};


#endif //DONKEYKONG_BARREL_H

//
// Created by theo on 16/01/19.
//

#ifndef DONKEYKONG_BARREL_H
#define DONKEYKONG_BARREL_H

#include "Entity.h"
#include "pch.h"

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

public:
    Barrel(const sf::Sprite &, const sf::Vector2f &posPlayer, EntityType, const SpritesPatterns &);

    ~Barrel() override = default;

    void update(sf::Time elapsedTime, Map map) override;


};


#endif //DONKEYKONG_BARREL_H

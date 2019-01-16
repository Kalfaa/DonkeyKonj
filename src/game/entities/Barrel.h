//
// Created by theo on 16/01/19.
//

#ifndef DONKEYKONG_BARREL_H
#define DONKEYKONG_BARREL_H


#include <SFML/System.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include <map/Map.h>
#include "Entity.h"
#include "pch.h"

class Barrel: public Entity {
public:
    enum PatternType
    {
        barrel,
        barrelVertical,
        barrelHorizontal,

    };
    typedef std::map<Barrel::PatternType, std::vector<sf::Sprite>> SpritesPatterns;

public:
    Barrel(const sf::Sprite&, const sf::Vector2f& posPlayer, EntityType, float playerSpeed, const SpritesPatterns&);
    ~Barrel() override = default;
    void update(sf::Time,Map map) ;


};


#endif //DONKEYKONG_BARREL_H

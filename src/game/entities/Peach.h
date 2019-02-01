//
// Created by theo on 01/02/19.
//

#ifndef DONKEYKONG_PEACH_H
#define DONKEYKONG_PEACH_H


#include "Entity.h"

class Peach : public Entity {

    enum PatternType
    {
        peach,
        peachKiss,
        barrelHorizontal,

    };
    typedef std::map<Peach::PatternType, std::vector<sf::Sprite>> SpritesPatterns;
    public:
        Peach(const sf::Sprite &sprite, const sf::Vector2f &posPlayer, EntityType type, const SpritesPatterns &spritesPatterns);
        SpritesPatterns patterns;
};


#endif //DONKEYKONG_PEACH_H

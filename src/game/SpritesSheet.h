//
// Created by user on 26/12/2018.
//

#ifndef DONKEYKONG_SPRITESSHEET_H
#define DONKEYKONG_SPRITESSHEET_H

#include "pch.h"
#include "EntityManager.h"

class SpritesSheet
{
public:
    static bool loadSprites(std::string file);

private:
    static std::map<std::string, std::array<int, 4>> loadSpriteSetting(std::string file);

public:
    static std::map<const std::string, sf::IntRect> sprites;
    static std::map<const std::string, std::vector<sf::IntRect>> spritesPaterns;

    // TODO : Exception if setting file not found
};


#endif //DONKEYKONG_SPRITESSHEET_H

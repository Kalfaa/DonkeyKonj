//
// Created by user on 26/12/2018.
//

#ifndef DONKEYKONG_SPRITESSHEET_H
#define DONKEYKONG_SPRITESSHEET_H

#include "pch.h"
#include "EntityManager.h"

typedef std::map<const std::string, sf::IntRect> MapSprites;
typedef std::map<const std::string, std::vector<sf::IntRect>> MapPatterns;

class SpritesSheet
{
public:
    static bool loadSprites(std::string file);

private:
    static std::map<std::string, std::array<int, 4>> loadSpriteSetting(std::string file);
    static size_t isPattern(std::string currentSprite, std::string lastSpriteName);

public:
    static std::map<const std::string, sf::IntRect> sprites;
    static std::map<const std::string, std::vector<sf::IntRect>> spritesPatterns;

private:
    static int lastNumSprite;
    // TODO : Exception if setting file not found
};


#endif //DONKEYKONG_SPRITESSHEET_H

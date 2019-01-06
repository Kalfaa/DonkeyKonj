//
// Created by user on 26/12/2018.
//

#ifndef DONKEYKONG_SPRITESSHEET_H
#define DONKEYKONG_SPRITESSHEET_H

#include "pch.h"
#include "EntityManager.h"

typedef std::map<const std::string, sf::IntRect> MapTextures;
typedef std::map<const std::string, std::vector<sf::IntRect>> MapPatterns;

class SpritesSheet
{
public:
    static SpritesSheet& GetInstance() { return INSTANCE; };

public:
    friend std::ostream &operator<<(std::ostream &os, const SpritesSheet &sheet);
    friend std::ostream &operator<<(std::ostream &os, const sf::IntRect &sheet);

public:
    static bool loadSprites(std::string file);

    sf::Texture getTexture(const std::string& name);
    sf::Texture getOppositeTexture(const std::string& name);
    std::vector<sf::Texture> getPattern(const std::string& name);
    std::vector<sf::Texture> getOppositePattern(const std::string& name);

private:
    static std::map<std::string, std::array<int, 4>> loadSpriteSetting(std::string file);
    static size_t isPattern(std::string currentSprite, std::string lastSpriteName);

private:
    static SpritesSheet INSTANCE;
    static sf::Image mainImage;

    static MapTextures posTexture;
    static MapPatterns posTexturePatterns;

    static int lastNumTex;
    // TODO : Exception if setting file not found
};


#endif //DONKEYKONG_SPRITESSHEET_H

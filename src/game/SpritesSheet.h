//
// Created by user on 26/12/2018.
//

#ifndef DONKEYKONG_SPRITESSHEET_H
#define DONKEYKONG_SPRITESSHEET_H

#include "pch.h"
#include "EntityManager.h"


class SpriteLoader
{
public:
    explicit SpriteLoader(const sf::Image &spriteSheet, const sf::IntRect &pos);

    virtual ~SpriteLoader();

public:
    std::shared_ptr<sf::Texture> getTexture(const sf::Image &spriteSheet);

private:
    std::shared_ptr<sf::Texture> texture;
};

class SpritesSheet
{
public:
    inline static SpritesSheet &GetInstance()
    { return INSTANCE; };

public:
    friend std::ostream &operator<<(std::ostream &os, const SpritesSheet &sheet);

    friend std::ostream &operator<<(std::ostream &os, const sf::IntRect &sheet);

public:
    typedef std::map<const std::string, std::shared_ptr<SpriteLoader>> MapSprites;
    typedef std::map<const std::string, std::vector<std::shared_ptr<SpriteLoader>>> MapPatterns;

public:
    //bool loadSprites(std::string file);
    bool loadSprites(std::string file, float extendRatio = 0);

    sf::Sprite getSprite(const std::string &name);

    sf::Sprite getOppositeSprite(const std::string &name);

    std::vector<sf::Sprite> getPattern(const std::string &name);

    std::vector<sf::Sprite> getOppositePattern(const std::string &name);

    std::array<float, 2> getSpriteSize(const std::string &name);

private:
    static std::map<std::string, std::array<int, 4>> loadSpriteSetting(std::string file);

    static size_t isPattern(std::string currentSprite, std::string lastSpriteName, int &lastNumSprite);

private:
    static SpritesSheet INSTANCE;
    sf::Image mainImage;

    MapSprites posSprites;
    MapPatterns posPatterns;

    float extendRatio = 0.f;

    // TODO : Exception if setting file not found
};


#endif //DONKEYKONG_SPRITESSHEET_H

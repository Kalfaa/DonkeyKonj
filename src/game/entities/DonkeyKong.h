//
// Created by Kalfa on 28/01/2019.
//

#ifndef DONKEYKONG_DONKEYKONG_H
#define DONKEYKONG_DONKEYKONG_H


#include "StaticEntity.h"
#include "Map.h"
#include "Barrel.h"


#define DK_SPEED 65
#define BARREL_FREQUENCY 2000
#define BARREL_WAVE_FREQUENCY 3000

class Map;

class DonkeyKong : public Entity
{

public:
    enum PatternType
    {
        donkeyFace,

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
        LAUNCHBARREL,
    };

public:
    DonkeyKong(const sf::Sprite &, const sf::Vector2f &posPlayer, EntityType, const SpritesPatterns &,
               const Barrel::SpritesPatterns &);

public:
    int HP;
    int timeBarrelLaunch;
    bool invulnerable;
    int timeAnimation;
    int BarrelCount;
    SpritesPatterns patterns;
    DonkeyState state;
    Barrel::SpritesPatterns barrelPattern;
    int barrelFrequency;
public:
    void update(sf::Time elapsedTime) override;

    void createBarrel(Map map, sf::Vector2f pos, Barrel::BarrelState state);
};


#endif //DONKEYKONG_DONKEYKONG_H

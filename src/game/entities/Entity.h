#ifndef DONKEYKONG_ENTITY_H
#define DONKEYKONG_ENTITY_H

#include "pch.h"

class Map;

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

enum PlayerState
{
    JUMP,
    IDLE,
    MOOVING,
    STARTJUMP,
    FALLING,
    GRINDING,
    DYING,
};

enum EntityType
{
    PLAYER,
    PEACH,
    PLATFORM,
    LADDER,
    BONUS_ITEM,
    SCORE_TAB,
    BARREL,
    DONKEYKONG,
    UNKNOWN
};

class Entity
{
public:
    Entity(EntityType = EntityType::UNKNOWN);

    Entity(const sf::Sprite &, EntityType);

    Entity(const sf::Sprite &, const sf::Vector2f &pos, EntityType);

    //Entity(const sf::Vector2f& position, const sf::Texture&, EntityType type);
    virtual ~Entity() = default;

public:
    virtual void update(sf::Time) = 0;

    void changeSprite(sf::Sprite newSprite);

    const sf::Sprite &getSprite() const;

    sf::Sprite updateAnimation(int *now, int frequency, std::vector<sf::Sprite> sprite);


public:
    sf::Vector2u size;
    sf::Vector2f position;
    sf::Texture texture;
    sf::Sprite sprite;

    EntityType type = EntityType::UNKNOWN;
    bool enabled = true;
};

#endif // DONKEYKONG_ENTITY
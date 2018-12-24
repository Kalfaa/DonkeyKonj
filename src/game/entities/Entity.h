#pragma once


enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    DEFAULT
};

enum EntityType
{
    player,
    block,
    scale,
    unknown
};

class Entity
{
public:
    Entity() = default;

    ~Entity() = default;

public:
    sf::Sprite sprite;
    sf::Vector2u size;
    sf::Vector2f position;
    EntityType type = EntityType::unknown;
    bool enabled = true;

    // Enemy only
    bool bLeftToRight = true;
    int times = 0;
};


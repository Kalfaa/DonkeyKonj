#pragma once


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
    FALLING
};
enum EntityType
{
    PLAYER,
    PLATFORM,
    LADDER,
    BONUS_ITEM,
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
    virtual void update(sf::Time);

    const sf::Sprite &getSprite() const;

public:
    sf::Vector2u size;
    sf::Vector2f position;
    sf::Texture texture;
    sf::Sprite sprite;

    EntityType type = EntityType::UNKNOWN;
    bool enabled = true;

    // Enemy only
    bool bLeftToRight = true;
    int times = 0;
};


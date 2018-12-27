#pragma once


enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

enum PlayerState {
    JUMP,
    IDLE,
    MOOVING,
    STARTJUMP
};
enum EntityType
{
    player,
    platform,
    ladder,
    unknown
};

class Entity
{
public:
    Entity(const sf::Sprite&, EntityType);
    Entity(const sf::Vector2f& position, const sf::Texture&, EntityType type);
    virtual ~Entity() = default;

public:
    virtual void update(sf::Time);

    const sf::Sprite& getSprite() const;

public:
    sf::Vector2u size;
    sf::Vector2f position;
    sf::Texture texture;
    sf::Sprite sprite;

    EntityType type = EntityType::unknown;
    bool enabled = true;

    // Enemy only
    bool bLeftToRight = true;
    int times = 0;
};


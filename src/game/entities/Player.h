//
// Created by user on 25/12/2018.
//

#ifndef DONKEYKONG_PLAYER_H
#define DONKEYKONG_PLAYER_H

#include "pch.h"
#include "Entity.h"

class Map;

#define MARIO_JUMP_MAX 4000
#define MARIO_JUMP_SPEED 300

class Player : public Entity
{
public:
    enum PatternType
    {
        deadPatternLeft,
        deadPatternRight,
        movePatternLeft,
        movePatternRight,
        climbPatternLeft,
        climbPatternRight,
        fightPatternLeft,
        fightPatternRight,
        moveFightPatternLeft,
        moveFightPatternRight,
        jumpPatternLeft,
        jumpPatternRight
    };

    typedef std::map<PatternType, std::vector<sf::Sprite>> SpritesPatterns;

public:
    Player(const sf::Sprite &, const sf::Vector2f &posPlayer, EntityType, float playerSpeed, const SpritesPatterns &);

    ~Player() override = default;

    sf::Sprite hitboxUseForCollision;
    int MARIO_HEIGHT;
    int MARIO_WIDTH;
public:
    void update(sf::Time) override;

    void move(Direction elapsedTime);

    void jump();

    sf::FloatRect getRectUnderMario();

    sf::FloatRect getHitboxLadder();

    sf::FloatRect getUpHitboxLadder();

    PlayerState playerState = IDLE;
    int life;

    void kill();

protected:
    //bool collide(Map map, EntityType entityType, Direction direction);
    bool collide(Map map, EntityType entityType, Direction direction);

    bool collide(Map map, EntityType entityType, Direction direction, sf::FloatRect rect);

    sf::Vector2f moveUp();

    sf::Vector2f moveDown();

    sf::Vector2f moveLeft();

    sf::Vector2f moveRight();

    void applyGravity(sf::Time elapsedTime);

    void move(sf::Time elapsedTime);

protected:
    float playerSpeed;
    Direction direction;
    Direction lastDirection;
    float jumpValue;
    int TimeAnimation;

    SpritesPatterns spritesPtns;
};


#endif //DONKEYKONG_PLAYER_H

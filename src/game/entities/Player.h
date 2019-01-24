//
// Created by user on 25/12/2018.
//

#ifndef DONKEYKONG_PLAYER_H
#define DONKEYKONG_PLAYER_H

#include "pch.h"
#include "Entity.h"

#define MARIO_JUMP_MAX 3500
#define MARIO_JUMP_SPEED 700

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
    sf::Sprite hitboxUseForCollision ;
    int MARIO_HEIGHT;
    int MARIO_WIDTH;
public:
    void update(sf::Time, Map map) override;


    void move(Direction elapsedTime);

    void jump();
    sf::FloatRect getRectUnderMario();
    sf::FloatRect getHitboxLadder();
    PlayerState playerState = IDLE;

protected:
    //bool collide(Map map, EntityType entityType, Direction direction);

    void changeSprite(sf::Sprite newSprite);

    sf::Sprite updateAnimation(int *now, int frequency, std::vector<sf::Sprite> sprite);
    bool collide(Map map,EntityType entityType,Direction direction);
    bool collide(Map map,EntityType entityType,Direction direction,sf::FloatRect rect);

protected:
    float playerSpeed;
    Direction direction;
    Direction lastDirection;
    float jumpValue;
    int TimeAnimation;

    SpritesPatterns spritesPtns;
};


#endif //DONKEYKONG_PLAYER_H

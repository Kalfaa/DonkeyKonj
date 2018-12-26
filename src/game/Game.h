#pragma once

#include "pch.h"
#include "StringHelpers.h"
#include "EntityManager.h"
#include "Platform.h"
#include "Ladder.h"
#include "Player.h"
#include "Mario.h"

#define LADDER_COUNT 4
#define BLOCK_COUNT_X 8
#define BLOCK_COUNT_Y 5
#define BLOCK_SPACE 110.f

#define MARIO_SPEED 100.f

class Game
{
public:
    Game();

    ~Game() = default;

    void run();

private:
    void processEvents();

    void update(sf::Time elapsedTime);

    void render();

    void updateStatistics(sf::Time elapsedTime);

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
    static const float PlayerSpeed;
    static const sf::Time timePerFrame;
    Map map;
    sf::RenderWindow mWindow;
    sf::Texture mTexture;
    sf::Sprite mPlayer;
    sf::Font mFont;
    sf::Text mStatisticsText;
    sf::Time mStatisticsUpdateTime;

    std::size_t mStatisticsNumFrames;
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingRight;
    bool mIsMovingLeft;

    sf::Texture textureLadder;
    sf::Sprite ladder[LADDER_COUNT];
    sf::Texture texturePlatform;
    sf::Sprite block[BLOCK_COUNT_X][BLOCK_COUNT_Y];
    sf::Texture textureWeapon;
    sf::Sprite weapon;
    sf::Vector2u sizeBlock;
    sf::Vector2u sizeMario;
};


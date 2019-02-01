#ifndef DONKEYKONG_GAME_H
#define DONKEYKONG_GAME_H

#include "pch.h"
#include "StringHelpers.h"
#include "EntityManager.h"
#include "SpritesSheet.h"

#include "Platform.h"
#include "Ladder.h"
#include "Player.h"
#include "Mario.h"
#include "BonusItem.h"
#include "ScoreTab.h"
#include "Barrel.h"

//#include "Map.h"
#include "GenerateMap.h"

#define MARIO_SPEED 100.f

class Map;

class Game
{
public:
    Game();

    ~Game() = default;

    void run();


    enum GameState
    {
        INGAME
    };


private:

    Map *createMap(std::ifstream mapFile);

    void processEvents();

    void update(sf::Time elapsedTime);

    void draw();

    void updateStatistics(sf::Time elapsedTime);

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    Map *basicMap();

    void addBlockLine(Map &map, int number, int posx, int posy);

    void addLadder(Map &map, int height, int posx, int posy);

    void addBonus(Map &map, int posx[3], int posy[3]);

    void addScoreTab(Map &map, int posx, int posy);

    sf::RectangleShape getRectangleToDraw(sf::FloatRect rectFloat, sf::Color color);

    void removeFromEntities(std::shared_ptr<Entity> ent);

    bool checkIfEntityIsOutOfMap(std::shared_ptr<Entity> ent);

private:

    static const float PlayerSpeed;
    static const sf::Time timePerFrame;

    std::shared_ptr<Map> map;
    SpritesSheet sps;

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
    bool debug;
    bool mJump;
    bool countElement;

    GameState gameState;
};

#endif
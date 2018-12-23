#include "pch.h"
#include "StringHelpers.h"
#include "Game.h"
#include "EntityManager.h"
#include "Mario.h"


const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);
enum Direction { UP=1,DOWN= 2, LEFT = 3, RIGHT = 4 };
Game::Game()
        : mWindow(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close), mTexture(), mPlayer(), mFont(),
          mStatisticsText(), mStatisticsUpdateTime(), mStatisticsNumFrames(0), mIsMovingUp(false), mIsMovingDown(false),
          mIsMovingRight(false), mIsMovingLeft(false)
{
    mWindow.setFramerateLimit(160);

    // Draw blocks

    _TextureBlock.loadFromFile("../Media/Textures/Block.png");
    _sizeBlock = _TextureBlock.getSize();

    for (int i = 0; i < BLOCK_COUNT_X; i++)
    {
        for (int j = 0; j < BLOCK_COUNT_Y; j++)
        {
            _Block[i][j].setTexture(_TextureBlock);
            _Block[i][j].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1));

            std::shared_ptr<Entity> se = std::make_shared<Entity>();
            se->m_sprite = _Block[i][j];
            se->m_type = EntityType::block;
            se->m_size = _TextureBlock.getSize();
            se->m_position = _Block[i][j].getPosition();
            EntityManager::m_Entities.push_back(se);
        }
    }

    // Draw Ladder

    _TextureLadder.loadFromFile("../Media/Textures/Echelle.PNG");

    for (int i = 0; i < SCALE_COUNT; i++)
    {
        _Echelle[i].setTexture(_TextureLadder);
        _Echelle[i].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (i + 1) + _sizeBlock.y);

        std::shared_ptr<Entity> se = std::make_shared<Entity>();
        se->m_sprite = _Echelle[i];
        se->m_type = EntityType::scale;
        se->m_size = _TextureLadder.getSize();
        se->m_position = _Echelle[i].getPosition();
        EntityManager::m_Entities.push_back(se);
    }

    // Draw Mario
    sf::Vector2f posMario(0,0);
    mTexture.loadFromFile("../Media/Textures/Mario_small_transparent.png");
    _mario =  Mario(posMario, mTexture);
     // Mario_small.png");

    mPlayer.setTexture(mTexture);
    posMario.x = 100.f + 70.f;
    posMario.y = BLOCK_SPACE * 5 - _sizeMario.y;



  /*  std::shared_ptr<Entity> player = std::make_shared<Entity>();
    player->m_sprite = sprite;
    player->m_type = EntityType::player;
    player->m_size = mTexture.getSize();
    player->m_position = sprite.getPosition();
    EntityManager::m_Entities.push_back(player);
*/
    // Draw Statistic Font

    mFont.loadFromFile("../Media/Sansation.ttf");
    mStatisticsText.setString("Welcome to Donkey Kong 1981");
    mStatisticsText.setFont(mFont);
    mStatisticsText.setPosition(5.f, 5.f);
    mStatisticsText.setCharacterSize(10);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processEvents();
            update(TimePerFrame);
        }

        updateStatistics(elapsedTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event{};
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;

            case sf::Event::Closed:
                mWindow.close();
                break;

            default: ;
        }
    }
}

void Game::update(sf::Time elapsedTime)
{
    sf::Vector2f movement(0.f, 0.f);
    _mario.update(elapsedTime);

    for (const std::shared_ptr<Entity> &entity : EntityManager::m_Entities)
    {
        if (!entity->m_enabled || entity->m_type != EntityType::player)
        {
            continue;
        }

        entity->m_sprite.move(movement * elapsedTime.asSeconds());
    }
}

void Game::render()
{
    mWindow.clear();

    for (const std::shared_ptr<Entity> &entity : EntityManager::m_Entities)
    {
        if (!entity->m_enabled)
        {
            continue;
        }

        mWindow.draw(entity->m_sprite);
    }
    mWindow.draw(_mario.getMPlayer());
    mWindow.draw(mStatisticsText);
    mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
    mStatisticsUpdateTime += elapsedTime;
    mStatisticsNumFrames += 1;

    if (mStatisticsUpdateTime >= sf::seconds(1.0f))
    {
        mStatisticsText.setString(
                "Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
                "Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }

    //
    // Handle collision
    //

    if (mStatisticsUpdateTime >= sf::seconds(0.050f))
    {
        // Handle collision weapon enemies
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    switch (key)
    {
        case sf::Keyboard::Up:
            _mario.move(UP);
            break;
        case sf::Keyboard::Down:
            _mario.move(DOWN);
            break;
        case sf::Keyboard::Left:
            _mario.move(LEFT);
            break;
        case sf::Keyboard::Right:
            _mario.move(RIGHT);
            break;

        // TODO: Jump!!!
        case sf::Keyboard::Space:
            break;

        default: ;
    }
}

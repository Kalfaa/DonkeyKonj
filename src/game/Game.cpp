#include "Game.h"

const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
        : mWindow(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close), mTexture(), mPlayer(), mFont(),
          mStatisticsText(), mStatisticsUpdateTime(), mStatisticsNumFrames(0), mIsMovingUp(false), mIsMovingDown(false),
          mIsMovingRight(false), mIsMovingLeft(false)
{
    mWindow.setFramerateLimit(160);

    // Draw blocks

    texturePlatform.loadFromFile(EntityManager::TEXTURES_PATH + "/Block.png");
    sizeBlock = texturePlatform.getSize();

    for (int i = 0; i < BLOCK_COUNT_X; i++)
    {
        for (int j = 0; j < BLOCK_COUNT_Y; j++)
        {
            std::shared_ptr<Platform> pf = std::make_shared<Platform>(
                    sf::Vector2f(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1))
                    , texturePlatform
                    , EntityType::platform);
            EntityManager::entities.push_back(pf);
        }
    }

    // Draw Ladder

    textureLadder.loadFromFile(EntityManager::TEXTURES_PATH + "/Ladder.PNG");

    for (int i = 0; i < LADDER_COUNT; i++)
    {
        std::shared_ptr<Ladder> pf = std::make_shared<Ladder>(
                sf::Vector2f(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (i + 1) + sizeBlock.y)
                , textureLadder
                , EntityType::ladder);
        EntityManager::entities.push_back(pf);
    }

    // Draw Mario
    sf::Vector2f posMario(0, 0);
    mTexture.loadFromFile(EntityManager::TEXTURES_PATH + "/Mario_right_profile.png");
    EntityManager::player = std::make_shared<Mario>(posMario, mTexture, EntityType::player, MARIO_SPEED);

    //mPlayer.setTexture(mTexture);
    posMario.x = MARIO_SPEED + 70.f;
    posMario.y = BLOCK_SPACE * 5 - sizeMario.y;

    mFont.loadFromFile(EntityManager::MEDIA_PATH + "/Sansation.ttf");
    mStatisticsText.setString("Welcome to Donkey Kong 1981");
    mStatisticsText.setFont(mFont);
    mStatisticsText.setPosition(5.f, 5.f);
    mStatisticsText.setCharacterSize(10);

    sf::Image icon;
    if(!icon.loadFromFile("icon.ico"))
    {
        mWindow.setIcon(256,256,icon.getPixelsPtr());
    }

}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;

            processEvents();
            update(timePerFrame);
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

            default:;
        }
    }
}

void Game::update(sf::Time elapsedTime)
{
    sf::Vector2f movement(0.f, 0.f);
    EntityManager::player->update(elapsedTime);
    if(mIsMovingUp)EntityManager::player->move(UP);
    if(mIsMovingRight)EntityManager::player->move(RIGHT);
    if(mIsMovingDown)EntityManager::player->move(DOWN);
    if(mIsMovingLeft) EntityManager::player->move(LEFT);
    for (const std::shared_ptr<Entity> &entity : EntityManager::entities)
    {
        if (!entity->enabled || entity->type != EntityType::player)
        {
            continue;
        }

        entity->sprite.move(movement * elapsedTime.asSeconds());
    }
}

void Game::render()
{
    mWindow.clear();

    for (const std::shared_ptr<Entity> &entity : EntityManager::entities)
    {
        if (!entity->enabled)
        {
            continue;
        }

        mWindow.draw(entity->sprite);
    }
    for(const std::shared_ptr<Entity> &entity : EntityManager::entities)
    {
        if(entity->type == EntityType::player)
        {
            mWindow.draw(entity->getSprite());
        }
    }
    mWindow.draw(EntityManager::player->getSprite());
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
            mIsMovingUp = isPressed;
            break;
        case sf::Keyboard::Down:
            mIsMovingDown = isPressed;
            break;
        case sf::Keyboard::Left:
            mIsMovingLeft = isPressed;
            break;
        case sf::Keyboard::Right:
            mIsMovingRight = isPressed;
            break;

            // TODO: Jump!!!
        case sf::Keyboard::Space:
            break;

        default: EntityManager::player->move(NONE);
    }
}

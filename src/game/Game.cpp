#include "Game.h"


const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
        : mWindow(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close), mTexture(), mPlayer(), mFont(),
          mStatisticsText(), mStatisticsUpdateTime(), mStatisticsNumFrames(0), mIsMovingUp(false), mIsMovingDown(false),
          mIsMovingRight(false), mIsMovingLeft(false)
{
    mWindow.setFramerateLimit(160);

    // Draw blocks

    textureBlock.loadFromFile(EntityManager::TEXTURES_PATH + "/Block.png");
    sizeBlock = textureBlock.getSize();

    for (int i = 0; i < BLOCK_COUNT_X; i++)
    {
        for (int j = 0; j < BLOCK_COUNT_Y; j++)
        {
            block[i][j].setTexture(textureBlock);
            block[i][j].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1));

            std::shared_ptr<Entity> se = std::make_shared<Entity>(block[i][j], EntityType::block);
            EntityManager::entities.push_back(se);
        }
    }

    // Draw Ladder

    textureLadder.loadFromFile(EntityManager::TEXTURES_PATH + "/Ladder.PNG");

    for (int i = 0; i < SCALE_COUNT; i++)
    {
        ladder[i].setTexture(textureLadder);
        ladder[i].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (i + 1) + sizeBlock.y);

        std::shared_ptr<Entity> se = std::make_shared<Entity>(ladder[i], EntityType::ladder);
        EntityManager::entities.push_back(se);
    }

    // Draw Mario
    sf::Vector2f posMario(0, 0);
    mTexture.loadFromFile(EntityManager::TEXTURES_PATH + "/Mario_right_profile.png");
    mario = std::make_unique<Mario>(posMario, mTexture, EntityType::player);
    // Mario_small.png");

    mPlayer.setTexture(mTexture);
    posMario.x = 100.f + 70.f;
    posMario.y = BLOCK_SPACE * 5 - sizeMario.y;



    /*  std::shared_ptr<Entity> player = std::make_shared<Entity>();
      player->sprite = sprite;
      player->type = EntityType::player;
      player->size = mTexture.getSize();
      player->position = sprite.getPosition();
      EntityManager::entities.push_back(player);
  */
    // Draw Statistic Font

    mFont.loadFromFile(EntityManager::MEDIA_PATH + "/Sansation.ttf");
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
    mario->update(elapsedTime);

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
    mWindow.draw(mario->getSprite());
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
            mario->move(UP);
            break;
        case sf::Keyboard::Down:
            mario->move(DOWN);
            break;
        case sf::Keyboard::Left:
            mario->move(LEFT);
            break;
        case sf::Keyboard::Right:
            mario->move(RIGHT);
            break;

            // TODO: Jump!!!
        case sf::Keyboard::Space:
            break;

        default: mario->move(DEFAULT);
    }
}

#include "Game.h"

const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);
const int CASE_PIXEL_VALUE = 32;
Game::Game()
        : mWindow(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close), mTexture(), mPlayer(), mFont(),
          mStatisticsText(), mStatisticsUpdateTime(), mStatisticsNumFrames(0), mIsMovingUp(false), mIsMovingDown(false),
          mIsMovingRight(false), mIsMovingLeft(false) ,debug(false),mJump(false)
{
    // Load localisation of all posTexture and patterns
    SpritesSheet sps = SpritesSheet::GetInstance();
    sps.loadSprites(EntityManager::TEXTURES_PATH + "/DonkeyKong_SpritesSheet.png");

    mWindow.setFramerateLimit(160);
    map = Map(100,100) ;

    // Draw blocks

    texturePlatform = sps.getTexture("PlatformRed");
    sizeBlock = texturePlatform.getSize();
    for (int i = 0; i < BLOCK_COUNT_X; i++)
    {
        for (int j = 0; j < BLOCK_COUNT_Y; j++)
        {
            std::shared_ptr<Platform> pf = std::make_shared<Platform>(
                    sf::Vector2f(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1))
                    , texturePlatform
                    , EntityType::PLATFORM);
            EntityManager::entities.push_back(pf);
            map.addEntityToMatrix(pf);
        }
    }
    //block[0][0].setTexture(SpritesSheet::getTexture("PlatformRed"));
    //block[0][0].setPosition(100,300);
    //std::shared_ptr<Entity> se = std::make_shared<Entity>(block[0][0], EntityType::PLATFORM);
    //EntityManager::entities.push_back(se);
    //map.addEntityToMatrix(se);

    // Draw Ladder
    textureLadder = sps.getTexture("Ladder");
    //textureLadder.loadFromFile(EntityManager::TEXTURES_PATH + "/Ladder.PNG");

    for (int i = 0; i < LADDER_COUNT; i++)
    {
        std::shared_ptr<Ladder> pf = std::make_shared<Ladder>(
                sf::Vector2f(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (i + 1) + sizeBlock.y)
                , textureLadder
                , EntityType::LADDER);
        EntityManager::entities.push_back(pf);
        map.addEntityToMatrix(pf);
    }

    // Draw Mario
    sf::Vector2f posMario(100, 240);
    mTexture = sps.getTexture("MarioLeftJump");
    EntityManager::player = std::make_shared<Mario>(posMario, mTexture, EntityType::PLAYER, MARIO_SPEED);

    mPlayer.setTexture(mTexture);

    mFont.loadFromFile(EntityManager::MEDIA_PATH + "/Sansation.ttf");
    mStatisticsText.setString("Welcome to Donkey Kong 1981");
    mStatisticsText.setFont(mFont);
    mStatisticsText.setPosition(5.f, 5.f);
    mStatisticsText.setCharacterSize(10);

    sf::Image icon;
    if(icon.loadFromFile(EntityManager::TEXTURES_PATH + "/icon.png"))
    {
        mWindow.setIcon(281, 210, icon.getPixelsPtr());
    }
    else std::cerr << "Error when load " + EntityManager::TEXTURES_PATH + "/icon.png" << std::endl;
    map.printElement();
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
    EntityManager::player->update(elapsedTime, map);
    if(mIsMovingUp)EntityManager::player->move(UP);
    if(mIsMovingRight)EntityManager::player->move(RIGHT);
    if(mJump){
        EntityManager::player->jump();
        mJump=false;
    }
    if(mIsMovingDown)EntityManager::player->move(DOWN);
    if(mIsMovingLeft) EntityManager::player->move(LEFT);
    for (const std::shared_ptr<Entity> &entity : EntityManager::entities)
    {
        if (!entity->enabled || entity->type != EntityType::PLAYER)
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
        if(debug)
        {
            sf::RectangleShape rectangle(sf::Vector2f(entity->getSprite().getTextureRect().width,
                                                      entity->getSprite().getTextureRect().height));
            rectangle.setPosition(entity->getSprite().getPosition());
            rectangle.setFillColor(sf::Color(100, 250, 50));
            mWindow.draw(rectangle);
        }

    }
    for(const std::shared_ptr<Entity> &entity : EntityManager::entities)
    {
        if(entity->type == EntityType::PLAYER)
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
        case sf::Keyboard::P:
            if(isPressed)debug = !debug;
           break;
        case sf::Keyboard::Space:
            if(isPressed && EntityManager::player->playerState != JUMP )mJump = true;
            break;

        default: EntityManager::player->move(NONE);
    }
}

#include <utility>

#include <entities/Peach.h>
#include <memory>
#include "DonkeyKong.h"
#include "Game.h"

using namespace std;

const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);
const int CASE_PIXEL_VALUE = 32;

Game::Game()
        : mWindow(sf::VideoMode(860, 600), "Donkey Kong 1981", sf::Style::Close), mTexture(), mPlayer(), mFont(),
          mStatisticsText(), mStatisticsUpdateTime(), mStatisticsNumFrames(0), mIsMovingUp(false), mIsMovingDown(false),
          mIsMovingRight(false), mIsMovingLeft(false), debug(false), mJump(false), countElement(false)
{
    mWindow.setFramerateLimit(160);
    lvlcount = 0;
    // Load sprites
    sps = SpritesSheet::GetInstance();
    sps.loadSprites(EntityManager::TEXTURES_PATH + "/DonkeyKong_SpritesSheet.png", SCALE_SPRITES);

    std::string filename = EntityManager::MAP_PATH + "/" + "map_donkeykong";
    lvlList = {"map_donkeykong", "map_donkeykong2"};
    //map = std::shared_ptr<Map>(basicMap());
    map = initMap(lvlList.at(0));

    mFont.loadFromFile(EntityManager::MEDIA_PATH + "/emulogic.ttf");
    mStatisticsText.setString("Welcome to Donkey Kong 1981");
    mStatisticsText.setFont(mFont);
    mStatisticsText.setPosition(5.f, 5.f);
    mStatisticsText.setCharacterSize(6);

    sf::Image icon;
    if (icon.loadFromFile(EntityManager::TEXTURES_PATH + "/icon.png"))
    {
        mWindow.setIcon(281, 210, icon.getPixelsPtr());
    }
    else std::cerr << "Error when load " + EntityManager::TEXTURES_PATH + "/icon.png" << std::endl;

    EntityManager::map = map;
    gameState = INGAME;
    timeAnimation = 0;
    secondCount = 0;

    initGameData();
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
        draw();
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
    switch (gameState)
    {
        case INGAME:
            gameUpdate(elapsedTime);
            break;
        case MAPTRANSITION:
            updateGameTransition(elapsedTime);
            break;
        default:;
    }


}

void Game::draw()
{
    mWindow.clear();

    switch (gameState)
    {
        case INGAME:
            drawGame();
            break;

        case MAPTRANSITION:
            drawTransition();
            break;

        case GAMEOVER:
            drawGameOver();
            break;
        default:;
    }
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
            if (isPressed)debug = !debug;
            break;
        case sf::Keyboard::Space:
            if (isPressed && EntityManager::player->playerState != JUMP)mJump = true;
            break;
        case sf::Keyboard::M:
            countElement = true;
        default:
            EntityManager::player->move(NONE);
    }

}

sf::RectangleShape Game::getRectangleToDraw(sf::FloatRect rectFloat, sf::Color color)
{
    sf::RectangleShape rectangle(sf::Vector2f(rectFloat.width,
                                              rectFloat.height));
    sf::Vector2f pos(rectFloat.left, rectFloat.top);
    rectangle.setPosition(pos);
    rectangle.setFillColor(color);
    return rectangle;
}

void Game::removeFromEntities(std::shared_ptr<Entity> ent)
{
    for (auto it = EntityManager::entities.begin(); it != EntityManager::entities.end(); ++it)
    {
        if (ent == *it)
        {
            EntityManager::entities.erase(it);
            return;
        }
    }
}

bool Game::checkIfEntityIsOutOfMap(std::shared_ptr<Entity> ent)
{
    if (ent->sprite.getPosition().x < 0 - ent->sprite.getGlobalBounds().width ||
        ent->sprite.getPosition().y < 0 - ent->sprite.getGlobalBounds().height)
        return true;
    return ent->sprite.getPosition().x+ ent->sprite.getGlobalBounds().width > EntityManager::map->getEntity3DArray().at(0).size() * 32 ||
           ent->sprite.getPosition().y > EntityManager::map->getEntity3DArray().size() * 32;
}

void Game::mainMenuUpdate(sf::Time elapsedTime)
{

}

void Game::gameUpdate(sf::Time elapsedTime)
{
    sf::Vector2f movement(0.f, 0.f);
    EntityManager::player->update(elapsedTime);
    int countb = 0;

    if (checkIfEntityIsOutOfMap(EntityManager::player))
    {
        EntityManager::player->kill();
    }

    if (gameData->getLifeNumber() == 0 || gameData->getGameTimer() == 0)
    {
        gameState = GAMEOVER;
        return;
    }
    std::vector<std::shared_ptr<Entity>> willBeErased;
    const sf::Sprite player = EntityManager::player->getSprite();
    for (const auto &entity : EntityManager::entities)
    {
        if (entity->type == BARREL || entity->type == DONKEYKONG || entity->type == BONUS_ITEM)
        {
            if (checkIfEntityIsOutOfMap(entity))
            {
                willBeErased.push_back(entity);
            }
            else
            {
                int size1 = static_cast<int>(EntityManager::entities.size());
                entity->update(elapsedTime);
                if (size1 != EntityManager::entities.size()) break;
            }
            if(entity->type == BONUS_ITEM)
            {
                auto* bi = dynamic_cast<BonusItem*>(entity.get());
                if(bi->isCatch && !bi->consumed) gameData->updateScore(gameData->getScoreValue() + bi->consume());
            }
        }
        if (entity->type == PEACH)
        {
            if (map->collide(entity->sprite, EntityType::PLAYER, DOWN)->collide)
            {
                EntityManager::entities.clear();
                gameState = MAPTRANSITION;
                lvlcount++;
                return;
            }
        }
    }
    for (const auto &entity : willBeErased)
    {
        removeFromEntities(entity);
        EntityManager::map->removeMoovingObject(entity);
    }
    if (!willBeErased.empty())willBeErased.clear();
    if (countElement)
    {
        map->countElement();
        countElement = false;
    }
    if (mIsMovingUp)EntityManager::player->move(UP);
    if (mIsMovingRight)EntityManager::player->move(RIGHT);
    if (mJump)
    {
        EntityManager::player->jump();
        mJump = false;
    }
    if (mIsMovingDown) EntityManager::player->move(DOWN);
    if (mIsMovingLeft) EntityManager::player->move(LEFT);
    for (const std::shared_ptr<Entity> &entity : EntityManager::entities)
    {
        if (!entity->enabled || entity->type != EntityType::PLAYER)
        {
            continue;
        }
    }

    gameData->updateLife(static_cast<unsigned int>(EntityManager::player->life));
    if(secondCount / 1000 >= 1 && gameData->getGameTimer() > 0)
    {
        gameData->updateTimer(gameData->getGameTimer() - (secondCount / 1000));
        secondCount = 0;
    }
    else secondCount += elapsedTime.asMilliseconds();
}

void Game::gameOverUpdate(sf::Time elapsedTime)
{

}

shared_ptr<Map> Game::initMap(string mapname)
{

    shared_ptr<Map> result;
    std::map<string, EntityGenerator::FunctionPtrCreateEntity> mapElement{
            {"PLATFORM",       &EntityGenerator::createPlatform},
            {"LADDER",         &EntityGenerator::createLadder},
            {"MARIO",          &EntityGenerator::createMario},
            {"BONUS_UMBRELLA", &EntityGenerator::createUmbrellaBonus},
            {"BONUS_HANDBAG",  &EntityGenerator::createHandbagBonus},
            {"BONUS_HAT",      &EntityGenerator::createHatBonus},
            {"SCORE_TAB",      &EntityGenerator::createTabScore},
            {"DONKEY_KONG",    &EntityGenerator::createDonkeyKong},
            {"PEACH",          &EntityGenerator::createPeach}
    };

    GenerateMap gMap(sps, mapElement);
    result = gMap.createMap(860, 600, std::move(mapname));
    result->startpoint = EntityManager::player->getSprite().getPosition();
    return result;
}

void Game::initGameData()
{
//    sf::Text scoreValue = sf::Text();
//    scoreValue.setFont(mFont);
//    scoreValue.setPosition({200,300});
//    scoreValue.setString(std::to_string(gameData->getScoreValue()));
//    scoreValue.setCharacterSize(35);

    unsigned int timeV = 300;
    sf::Text time = sf::Text();
    time.setFont(mFont);
    time.setPosition({310, 20});
    time.setString(std::to_string(timeV));
    time.setCharacterSize(15);

    unsigned int lifeNumb = 3;
    sf::Text marioLife = sf::Text();
    marioLife.setFont(mFont);
    marioLife.setPosition({590, 20});
    marioLife.setString(std::to_string(lifeNumb));
    marioLife.setCharacterSize(15);

    unsigned int scoreV = 0;
    sf::Text score = sf::Text();
    score.setFont(mFont);
    score.setString(std::to_string(scoreV));
    score.setOrigin(score.getGlobalBounds().width, score.getGlobalBounds().height);
    score.setPosition({480, 46});
    score.setCharacterSize(15);

    gameData = std::unique_ptr<GameData>(new GameData(timeV, time,
                                                      lifeNumb, marioLife,
                                                      scoreV, score, mFont));

    mWindow.draw(*(gameData.get()));
    globalTimeLevel = timeV;
}

void Game::updateGameTransition(sf::Time elapsedTime)
{

    if (gameData->getGameTimer() > 0)
    {
        gameData->updateScore(gameData->getScoreValue() + 2);
        gameData->updateTimer(gameData->getGameTimer() - 1);
    }
    else
    {
        timeAnimation += elapsedTime.asMilliseconds();
        if (timeAnimation > 500)
        {
            if (lvlcount < lvlList.size())
            {
                EntityManager::map = initMap(lvlList.at(static_cast<unsigned long long int>(lvlcount)));
                gameState = INGAME;
                cerr << "TIME UPDATE !!!!!!!!!!!" << endl;
                gameData->updateTimer(globalTimeLevel);
                cerr << "TIME UPDATE !!!!!!!!!!! " << gameData->getGameTimer() << endl;
                secondCount = 0;
            }
        }
    }
}

void Game::drawGame()
{
    for (const std::shared_ptr<Entity> &entity : EntityManager::entities)
    {
        if (!entity->enabled)
        {
            continue;
        }

        mWindow.draw(entity->sprite);
        if (debug)
        {

            sf::RectangleShape rectangle(sf::Vector2f(entity->getSprite().getGlobalBounds().width,
                                                      entity->getSprite().getGlobalBounds().height));
            rectangle.setPosition(entity->getSprite().getPosition());
            rectangle.setFillColor(sf::Color(100, 250, 50));
            mWindow.draw(rectangle);
        }

    }
    for (const std::shared_ptr<Entity> &entity : EntityManager::entities)
    {
        if (entity->type == EntityType::PLAYER)
        {

            mWindow.draw(entity->getSprite());

        }
    }

    mWindow.draw(*(gameData.get()));
    mWindow.draw(EntityManager::player->getSprite());
    mWindow.draw(mStatisticsText);

    if (debug)
    {
        mWindow.draw(
                getRectangleToDraw(EntityManager::player->getSprite().getGlobalBounds(), sf::Color(250, 150, 100)));
        mWindow.draw(getRectangleToDraw(EntityManager::player->hitboxUseForCollision.getGlobalBounds(),
                                        sf::Color(100, 250, 50)));
        mWindow.draw(getRectangleToDraw(EntityManager::player->getUpHitboxLadder(), sf::Color::Red));
    }
}

void Game::drawTransition()
{
    sf::Sprite dk = sps.getSprite("DonkeyKongOrange");
    dk.setPosition(370, 75);
    mWindow.draw(dk);

    sf::Text scoreDisplay = sf::Text();
    scoreDisplay.setFont(mFont);
    scoreDisplay.setPosition({200, 200});
    scoreDisplay.setString("Score");
    scoreDisplay.setCharacterSize(35);
    mWindow.draw(scoreDisplay);

    sf::Text timeDisplay = sf::Text();
    timeDisplay.setFont(mFont);
    timeDisplay.setPosition({500, 200});
    timeDisplay.setString("Time");
    timeDisplay.setCharacterSize(35);
    mWindow.draw(timeDisplay);

    sf::Text scoreValue = sf::Text();
    scoreValue.setFont(mFont);
    scoreValue.setPosition({200, 300});
    scoreValue.setString(std::to_string(gameData->getScoreValue()));
    scoreValue.setCharacterSize(35);
    mWindow.draw(scoreValue);

    sf::Text timeValue = sf::Text();
    timeValue.setFont(mFont);
    timeValue.setPosition({500, 300});
    timeValue.setString(std::to_string(gameData->getGameTimer()));
    timeValue.setCharacterSize(35);
    mWindow.draw(timeValue);
}

void Game::drawGameOver()
{
    sf::Text gameOver = sf::Text();
    gameOver.setFont(mFont);
    gameOver.setString("GAME OVER");
    gameOver.setPosition({65, 120});
    gameOver.setCharacterSize(80);
    mWindow.draw(gameOver);

    sf::Sprite dk = sps.getSprite("DonkeyKongFaceDanceLeft");
    dk.setPosition(370, 250);
    mWindow.draw(dk);

    sf::Text scoreDisplay = sf::Text();
    scoreDisplay.setFont(mFont);
    scoreDisplay.setPosition({200, 400});
    scoreDisplay.setString("Score");
    scoreDisplay.setCharacterSize(35);
    mWindow.draw(scoreDisplay);

    sf::Text timeDisplay = sf::Text();
    timeDisplay.setFont(mFont);
    timeDisplay.setPosition({500, 400});
    timeDisplay.setString("Time");
    timeDisplay.setCharacterSize(35);
    mWindow.draw(timeDisplay);

    sf::Text scoreValue = sf::Text();
    scoreValue.setFont(mFont);
    scoreValue.setPosition({200, 500});
    scoreValue.setString(std::to_string(gameData->getScoreValue()));
    scoreValue.setCharacterSize(35);
    mWindow.draw(scoreValue);

    sf::Text timeValue = sf::Text();
    timeValue.setFont(mFont);
    timeValue.setPosition({500, 500});
    timeValue.setString(std::to_string(gameData->getGameTimer()));
    timeValue.setCharacterSize(35);
    mWindow.draw(timeValue);
}




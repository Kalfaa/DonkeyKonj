#include <entities/Peach.h>
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

    // Load sprites
    sps = SpritesSheet::GetInstance();
    sps.loadSprites(EntityManager::TEXTURES_PATH + "/DonkeyKong_SpritesSheet.png", SCALE_SPRITES);

    std::string filename = EntityManager::MAP_PATH + "/" + "map_donkeykong";

    //map = std::shared_ptr<Map>(basicMap());

    ///MAP GENERATOR
    std::map<string, EntityGenerator::FunctionPtrCreateEntity> mapElement {
            {"PLATFORM", &EntityGenerator::createPlatform},
            {"LADDER", &EntityGenerator::createLadder},
            {"MARIO", &EntityGenerator::createMario},
            {"BONUS_UMBRELLA", &EntityGenerator::createUmbrellaBonus},
            {"BONUS_HANDBAG", &EntityGenerator::createHandbagBonus},
            {"BONUS_HAT", &EntityGenerator::createHatBonus},
            {"SCORE_TAB", &EntityGenerator::createTabScore},
            {"DONKEY_KONG", &EntityGenerator::createDonkeyKong},
            {"PEACH", &EntityGenerator::createPeach}
    };

    GenerateMap gMap(sps, mapElement);
    map = gMap.createMap(860, 600, "map_donkeykong");
    /// MAP ROTARENEG

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
    //map.printElement();
    EntityManager::map = map;
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
    gameUpdate(elapsedTime);
}

void Game::draw()
{
    mWindow.clear();

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
    sf::Text marioLife = sf::Text();
    marioLife.setFont(mFont);
    marioLife.setPosition({800,60});
    marioLife.setString("x"+std::to_string(EntityManager::player->life));
    marioLife.setCharacterSize(15);
    mWindow.draw(EntityManager::player->getSprite());
    mWindow.draw(mStatisticsText);
    mWindow.draw(marioLife);
    if (debug)
    {
        mWindow.draw(
                getRectangleToDraw(EntityManager::player->getSprite().getGlobalBounds(), sf::Color(250, 150, 100)));
        mWindow.draw(getRectangleToDraw(EntityManager::player->hitboxUseForCollision.getGlobalBounds(),
                                        sf::Color(100, 250, 50)));
        mWindow.draw(getRectangleToDraw(EntityManager::player->getUpHitboxLadder(), sf::Color::Red));
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

Map *Game::createMap(std::ifstream mapFile)
{

    std::string str((std::istreambuf_iterator<char>(mapFile)),
                    std::istreambuf_iterator<char>());
    auto x = static_cast<unsigned int>(str.find('\n'));
    auto y = static_cast<unsigned int>(str.begin(), str.end(), '\n');
    Map *newMap = new Map(x, y);
    //map.entity3DArray = Matrix3d(x, std::vector<std::vector<std::shared_ptr<Entity>>>(y));
    std::vector<std::string> list_string;
    std::stringstream ss(str);
    std::string tmp;
    while (std::getline(ss, tmp, '\n'))
    {
        list_string.push_back(tmp);
    }

    for (auto &it : list_string)
    {
        std::cout << it << std::endl;
    }

    for (int i = 0; i < y - 2; i++)
    {
        std::cout << (list_string[i].size()) << std::endl;
        for (int j = 0; j < x - 1; j++)
        {

            //printf(list_string[i].size());
            sf::Sprite sprite = sf::Sprite();
            sf::Vector2f pos(j * 32, i * 32);
            switch (list_string[i][j])
            {
                case 'O':
                    break;
                case 'P' :
                {
                    std::shared_ptr<Entity> plat = std::make_shared<Platform>(sps.getSprite("PlatformRed"), pos,
                                                                              EntityType::PLATFORM);
                    EntityManager::entities.push_back(plat);
                    newMap->addEntityToMatrix(plat);
                    break;
                }
                case 'H':
                {
                    std::shared_ptr<Entity> ladder = std::make_shared<Ladder>(sps.getSprite("Ladder"), pos,
                                                                              EntityType::LADDER);
                    EntityManager::entities.push_back(ladder);
                    newMap->addEntityToMatrix(ladder);
                    break;
                }
                case 'X':
                {
                    Mario::SpritesPatterns spritesPatterns
                            {
                                    {Player::climbPatternLeft,      sps.getPattern("MarioClimbLeft")},
                                    {Player::climbPatternRight,     sps.getOppositePattern("MarioClimbLeft")},
                                    {Player::deadPatternLeft,       sps.getPattern("MarioLeftSlide")},
                                    {Player::deadPatternRight,      sps.getOppositePattern("MarioLeftSlide")},
                                    {Player::fightPatternLeft,      sps.getPattern("MarioMoveLeftArm")},
                                    {Player::fightPatternRight,     sps.getOppositePattern("MarioMoveLeftArm")},
                                    {Player::moveFightPatternLeft,  sps.getPattern("MarioLeftArm")},
                                    {Player::moveFightPatternRight, sps.getOppositePattern("MarioLeftArm")},
                                    {Player::movePatternLeft,       sps.getPattern("MarioLeft")},
                                    {Player::movePatternRight,      sps.getOppositePattern("MarioLeft")},
                                    {Player::jumpPatternLeft,       std::vector<sf::Sprite>(1, sps.getSprite(
                                            "jumpPatternLeft"))},
                                    {Player::jumpPatternRight,      std::vector<sf::Sprite>(1, sps.getOppositeSprite(
                                            "jumpPatternLeft"))}
                            };

                    // spritesPatterns.at(Player::movePatternRight)[0]
                    EntityManager::player = std::make_shared<Mario>(spritesPatterns.at(Player::movePatternLeft)[2],
                                                                    pos,
                                                                    EntityType::PLAYER,
                                                                    MARIO_SPEED,
                                                                    spritesPatterns);
                    newMap->startpoint.x = j;
                    newMap->startpoint.y = i;
                }
                default:
                    break;
            }
        }
    }
    return newMap;
}

Map *Game::basicMap()
{
    Map *newMap = new Map(100, 20);

    addBlockLine(*newMap, 30, 50, 250);
    addBlockLine(*newMap, 30, 50, 350);
    addBlockLine(*newMap, 30, 50, 450);
    addLadder(*newMap, 4, 150, 410);
    addLadder(*newMap, 4, 90, 310);

    int bonusX[3] = {50, 140, 180};
    int bonusY[3] = {static_cast<int>(250 - sps.getSpriteSize("UmbrellaBonus")[0]),
                     static_cast<int>(350 - sps.getSpriteSize("HandbagBonus")[0]),
                     static_cast<int>(450 - sps.getSpriteSize("HatBonus")[0])};
    addBonus(*newMap, bonusX, bonusY);

    addScoreTab(*newMap, static_cast<int>(mWindow.getSize().x - sps.getSpriteSize("BonusPanel0")[1]), 0);

    sf::Vector2f posmario(10 * 32, 12 * 32);
    newMap->startpoint.x = posmario.x;
    newMap->startpoint.y = posmario.y;

    Mario::SpritesPatterns spritesPatterns
            {
                    {Player::climbPatternLeft,      sps.getPattern("MarioClimbLeft")},
                    {Player::climbPatternRight,     sps.getOppositePattern("MarioClimbLeft")},
                    {Player::deadPatternLeft,       sps.getPattern("MarioLeftSlide")},
                    {Player::deadPatternRight,      sps.getOppositePattern("MarioLeftSlide")},
                    {Player::fightPatternLeft,      sps.getPattern("MarioMoveLeftArm")},
                    {Player::fightPatternRight,     sps.getOppositePattern("MarioMoveLeftArm")},
                    {Player::moveFightPatternLeft,  sps.getPattern("MarioLeftArm")},
                    {Player::moveFightPatternRight, sps.getOppositePattern("MarioLeftArm")},
                    {Player::movePatternLeft,       sps.getPattern("MarioLeft")},
                    {Player::movePatternRight,      sps.getOppositePattern("MarioLeft")},
                    {Player::jumpPatternLeft,       std::vector<sf::Sprite>(1, sps.getSprite("MarioLeftJump"))},
                    {Player::jumpPatternRight,      std::vector<sf::Sprite>(1, sps.getOppositeSprite("MarioLeftJump"))}
            };


    Barrel::SpritesPatterns spritesPatternsBarrel
            {
                    {Barrel::barrel,           std::vector<sf::Sprite>(1, sps.getSprite("Barrel"))},
                    {Barrel::barrelHorizontalRight, sps.getPattern("BarrelHorizontal")},
                    {Barrel::barrelHorizontalLeft, sps.getOppositePattern("BarrelHorizontal")},
                    {Barrel::barrelVertical,   sps.getPattern("BarrelVertical")}
            };

    DonkeyKong::SpritesPatterns spritesPatternDk
            {
                    {DonkeyKong::donkeyFace, sps.getPattern("DonkeyKongFace")}
            };

    Peach::SpritesPatterns patternsPeach {
            {Peach::peachRight , sps.getPattern("PeachRight")},
            {Peach::peachLeft , sps.getOppositePattern("PeachRight")},
            {Peach::peachHelpRight , sps.getPattern("PeachHelpRight")},
            {Peach::peachHelpLeft , sps.getOppositePattern("PeachHelpRight")}
    };

    sf::Vector2f posbarrel(32 * 15, 32);
    sf::Vector2f posDK(32 * 10, 32 * 5);
    sf::Vector2f posPeach(32 *10 ,32*9);


    std::shared_ptr<Entity> peach = std::make_shared<Peach>(patternsPeach.at(Peach::peachRight)[0], posPeach,
                                                              EntityType::PEACH,patternsPeach );

    EntityManager::entities.push_back(peach);
    newMap->addEntityToMatrix(peach);
    //std::shared_ptr<Entity> barrel = std::make_shared<Barrel>(spritesPatternsBarrel.at(Barrel::barrelHorizontal)[0],
    //                                                          posbarrel,
    //                                                          EntityType::BARREL, spritesPatternsBarrel);
    //EntityManager::entities.push_back(barrel);
    //newMap->addEntityToMatrix(barrel);
    //newMap->moovingObject.push_back(barrel);
    EntityManager::player = std::make_shared<Mario>(spritesPatterns.at(Player::movePatternLeft)[0], posmario,
                                                    EntityType::PLAYER, MARIO_SPEED, spritesPatterns);
    std::shared_ptr<Entity> dk = std::make_shared<DonkeyKong>(spritesPatternDk.at(DonkeyKong::donkeyFace)[0], posDK,
                                                              EntityType::DONKEYKONG, spritesPatternDk,
                                                              spritesPatternsBarrel);
    EntityManager::entities.push_back(dk);

    return newMap;
}

void Game::addBlockLine(Map &map, int number, int posx, int posy)
{
    int block_space = static_cast<int>(sps.getSprite("PlatformRed").getGlobalBounds().width);
    for (int j = 0; j < number; j++)
    {
        sf::Vector2f pos;
        pos.y = posy;
        pos.x = posx + (block_space - 4) * j;
        std::shared_ptr<Entity> plat = std::make_shared<Platform>(sps.getSprite("PlatformRed"), pos,
                                                                  EntityType::PLATFORM);

        EntityManager::entities.push_back(plat);
        map.addEntityToMatrix(plat);
    }
}

void Game::addLadder(Map &map, int height, int posx, int posy)
{
    int block_space = static_cast<int>(sps.getSprite("PlatformRed").getGlobalBounds().height);
    sf::Vector2f pos;
    for (int j = 0; j < height; j++)
    {
        pos.y = posy + block_space * -j;
        pos.x = posx;
        std::shared_ptr<Entity> ladder = std::make_shared<Ladder>(sps.getSprite("Ladder"), pos,
                                                                  EntityType::LADDER);
        EntityManager::entities.push_back(ladder);
        map.addEntityToMatrix(ladder);
    }
}

void Game::addBonus(Map &map, int posx[3], int posy[3])
{
    string bonusTab[3] = {"UmbrellaBonus", "HandbagBonus", "HatBonus"};
    string bonusValue[3] = {"100Bonus", "300Bonus", "500Bonus"};

    for (int cnt = 0; cnt < 3; cnt++)
    {
        sf::Vector2f pos(posx[cnt], posy[cnt]);
        std::shared_ptr<Entity> bonus = std::make_shared<BonusItem>(sps.getSprite(bonusTab[cnt]),
                                                                    pos,
                                                                    EntityType::BONUS_ITEM,
                                                                    cnt * 200 + 100,
                                                                    sps.getSprite(bonusValue[cnt]));

        EntityManager::entities.push_back(bonus);
        map.addEntityToMatrix(bonus);
    }
}

void Game::addScoreTab(Map &map, int posx, int posy)
{
    std::shared_ptr<Entity> scoreTab = std::make_shared<ScoreTab>(sps.getSprite("BonusPanel0"),
                                                                  sf::Vector2f(posx, posy),
                                                                  EntityType::SCORE_TAB);

    EntityManager::entities.push_back(scoreTab);
    map.addEntityToMatrix(scoreTab);
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

void Game::removeFromEntities(std::shared_ptr<Entity> ent) {
    for(auto it = EntityManager::entities.begin(); it!= EntityManager::entities.end();++it){
        if(ent == *it){
            EntityManager::entities.erase(it);
            return ;
        }
    }
}

bool Game::checkIfEntityIsOutOfMap(std::shared_ptr<Entity> ent) {
    if(ent->sprite.getPosition().x < 0-ent->sprite.getGlobalBounds().width || ent->sprite.getPosition().y < 0 - ent->sprite.getGlobalBounds().height ) return true ;
    if(ent->sprite.getPosition().x > EntityManager::map->getEntity3DArray().at(0).size() *32 || ent->sprite.getPosition().y > EntityManager::map->getEntity3DArray().size() *32 ) return true ;
    return false;
}

void Game::mainMenuUpdate(sf::Time elapsedTime) {

}

void Game::gameUpdate(sf::Time elapsedTime) {
    sf::Vector2f movement(0.f, 0.f);
    EntityManager::player->update(elapsedTime);

    if(checkIfEntityIsOutOfMap(EntityManager::player))
    {
        EntityManager::player->kill();
    }

    if(EntityManager::player->life <0){
        //changement de phase
    }

    std::vector<std::shared_ptr<Entity>> willBeErased;
    const sf::Sprite player = EntityManager::player->getSprite();
    for (const auto &entity : EntityManager::entities)
    {
        if(entity->type == BARREL || entity->type == DONKEYKONG ||entity->type == BONUS_ITEM ){

            if(checkIfEntityIsOutOfMap(entity)){
                willBeErased.push_back(entity);
            }else{
                entity->update(elapsedTime);
            }
        }
    }

    for(const auto &entity : willBeErased){
        removeFromEntities(entity);
        EntityManager::map->removeMoovingObject(entity);
    }
    if(!willBeErased.empty())willBeErased.clear();
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
}

void Game::gameOverUpdate(sf::Time elapsedTime) {

}





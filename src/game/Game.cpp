#include <zconf.h>
#include "Game.h"

const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);
const int CASE_PIXEL_VALUE = 32;
Game::Game()
        : mWindow(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close), mTexture(), mPlayer(), mFont(),
          mStatisticsText(), mStatisticsUpdateTime(), mStatisticsNumFrames(0), mIsMovingUp(false), mIsMovingDown(false),
          mIsMovingRight(false), mIsMovingLeft(false) ,debug(false),mJump(false)
{
    mWindow.setFramerateLimit(160);
    sps = SpritesSheet::GetInstance();
    sps.loadSprites(EntityManager::TEXTURES_PATH + "/DonkeyKong_SpritesSheet.png", ZOOM_SPRITE);

//    do
//    {
//        for(auto& sp : sps.getOppositePattern("MarioMoveLeftArm"))
//        {
//            sp.setPosition(100, 100);
//            mWindow.clear(sf::Color::Black);
//            mWindow.draw(sp);
//            mWindow.display();
//            usleep(333333);
//        }
//
//        for(auto& sp : sps.getPattern("MarioMoveLeftArm"))
//        {
//            sp.setPosition(100, 100);
//            mWindow.clear(sf::Color::Black);
//            mWindow.draw(sp);
//            mWindow.display();
//            usleep(333333);
//        }
//    }while (true);


    // Draw blocks

    texturePlatform.loadFromFile(EntityManager::TEXTURES_PATH + "/Block.png");
    sizeBlock = texturePlatform.getSize();





    mTexture.loadFromFile(EntityManager::TEXTURES_PATH + "/Mario_right_profile.png");


    mPlayer.setTexture(mTexture);
    std::string filename = EntityManager::MAP_PATH + "/" + "map_donkeykong";
    map = createMap( std::ifstream (filename.c_str()));
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
            sf::RectangleShape rectangle(sf::Vector2f(entity->getSprite().getTextureRect().width*entity->getSprite().getScale().x,
                                                      entity->getSprite().getTextureRect().height*entity->getSprite().getScale().y));
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

    if(debug){
        sf::RectangleShape rectangle(sf::Vector2f(EntityManager::player->getSprite().getTextureRect().width*EntityManager::player->getSprite().getScale().x,
                                                  EntityManager::player->getSprite().getTextureRect().height*EntityManager::player->getSprite().getScale().y));
        rectangle.setPosition(EntityManager::player->getSprite().getPosition());
        rectangle.setFillColor(sf::Color(100, 250, 50));
        mWindow.draw(rectangle);
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
            if(isPressed)debug = !debug;
           break;
        case sf::Keyboard::Space:
            if(isPressed && EntityManager::player->playerState != JUMP )mJump = true;
            break;

        default: EntityManager::player->move(NONE);
    }

}
Map Game::createMap(std::ifstream  mapFile)
{

    std::string str((std::istreambuf_iterator<char>(mapFile)),
                    std::istreambuf_iterator<char>());
    unsigned int x = str.find('\n');
    auto y = static_cast<unsigned int>(str.begin(),str.end(),'\n');
    Map newMap = Map(x,y) ;
    //map.entity3DArray = Matrix3d(x, std::vector<std::vector<std::shared_ptr<Entity>>>(y));
    std::vector<std::string> list_string;
    std::stringstream ss(str);
    std::string tmp;
    while(std::getline(ss, tmp, '\n'))
    {
        list_string.push_back(tmp);
    }

    for(auto it = list_string.begin(); it != list_string.end(); ++it)
    {
        std::cout << (*it) << std:: endl;
    }

    for(int i =0;i<y-2 ;i++){
        std::cout << (list_string[i].size()) << std:: endl;
        for(int j = 0;j<x-1;j++){

            //printf(list_string[i].size());
            sf::Sprite sprite = sf::Sprite();
            sf::Vector2f pos(j*32, i*32);
            switch(list_string[i][j]){
                case 'O':
                    break;
                case 'P' :
                    {
                    std::shared_ptr<Entity> plat = std::make_shared<Platform>(sps.getSprite("PlatformOrange"),pos,EntityType::PLATFORM);
                    EntityManager::entities.push_back(plat);
                    newMap.addEntityToMatrix(plat);
                    break;
                }
                case 'H':
                {
                    std::shared_ptr<Entity> ladder = std::make_shared<Ladder>(sps.getSprite("Ladder"), pos,
                                                                              EntityType::LADDER);
                    EntityManager::entities.push_back(ladder);
                    newMap.addEntityToMatrix(ladder);
                    break;
                }
                case 'X':{
                    EntityManager::player = std::make_shared<Mario>(sps.getSprite("MarioLeft0"), pos, EntityType::PLAYER, MARIO_SPEED);
                    newMap.startpoint.x=j;
                    newMap.startpoint.y=i;
                }
                default:break;
            }
        }
    }
    return newMap;

}


#include "Game.h"

const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);
const int CASE_PIXEL_VALUE = 32;
Game::Game()
        : mWindow(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close), mTexture(), mPlayer(), mFont(),
          mStatisticsText(), mStatisticsUpdateTime(), mStatisticsNumFrames(0), mIsMovingUp(false), mIsMovingDown(false),
          mIsMovingRight(false), mIsMovingLeft(false) ,debug(false),mJump(false)
{
    SpritesSheet::sprites;

    mWindow.setFramerateLimit(160);

    // Draw blocks

    texturePlatform.loadFromFile(EntityManager::TEXTURES_PATH + "/Block.png");
    sizeBlock = texturePlatform.getSize();
    /*
    for (int i = 0; i < BLOCK_COUNT_X; i++)
    {
        for (int j = 0; j < BLOCK_COUNT_Y; j++)
        {
            std::shared_ptr<Platform> pf = std::make_shared<Platform>(
                    sf::Vector2f(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1))
                    , texturePlatform
                    , EntityType::PLATFORM);
            EntityManager::entities.push_back(pf);
        }
    }*/
    /*
    block[0][0].setTexture(texturePlatform);
    block[0][0].setPosition(100,300);
    std::shared_ptr<Entity> se = std::make_shared<Entity>(block[0][0], EntityType::PLATFORM);
    EntityManager::entities.push_back(se);
    map.addEntityToMatrix(se);
    // Draw Ladder

    textureLadder.loadFromFile(EntityManager::TEXTURES_PATH + "/Ladder.PNG");

    for (int i = 0; i < LADDER_COUNT; i++)
    {
        std::shared_ptr<Ladder> pf = std::make_shared<Ladder>(
                sf::Vector2f(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (i + 1) + sizeBlock.y)
                , textureLadder
                , EntityType::LADDER);
        EntityManager::entities.push_back(pf);
        map.addEntityToMatrix(pf);
    }
*/
    // Draw Mario




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
            switch(list_string[i][j]){
                case 'O':
                    break;
                case 'P' :
                    {
                    sprite.setTexture(texturePlatform);
                    sprite.setPosition(j * 32, i * 32);
                    std::shared_ptr<Entity> plat = std::make_shared<Entity>(sprite, EntityType::PLATFORM);
                    EntityManager::entities.push_back(plat);
                    newMap.addEntityToMatrix(plat);
                    break;
                }
                case 'L':
                    //CREER UNE LADDER ET LE PUSH DANS LA MATRICE 3D
                    break;
                case 'X':{
                    sf::Vector2f posMario(j*32, i*32);
                    EntityManager::player = std::make_shared<Mario>(posMario, mTexture, EntityType::PLAYER, MARIO_SPEED);
                    newMap.startpoint.x=j;
                    newMap.startpoint.y=i;
                }
                default:break;
            }
        }
    }
    return newMap;

}


#include "EntityManager.h"


const std::string EntityManager::MEDIA_PATH = "../Media";
const std::string EntityManager::TEXTURES_PATH = MEDIA_PATH + "/Textures";
const std::string EntityManager::MAP_PATH = MEDIA_PATH + "/Maps";


void EntityManager::removeFromEntities(std::shared_ptr<Entity> entity)
{
    for (size_t cnt = 0; cnt < EntityManager::entities.size(); cnt++)
    {
        auto pos1 = find(EntityManager::entities.begin(), EntityManager::entities.end(), entity);

        if (pos1 != EntityManager::entities.end())
        {
            EntityManager::entities.erase(pos1);
        }
    }
}

std::vector<std::shared_ptr<Entity>> EntityManager::entities;
std::shared_ptr<Player> EntityManager::player;


std::shared_ptr<Entity> EntityManager::createPlatform(const sf::Vector2f& pos, long wight, long height)
{
    if(wight < 0 || height < 0) return std::make_shared<Platform>(
            SpritesSheet::GetInstance().getSprite("PlatformRed"),
            pos,
            EntityType::PLATFORM);
    else
    {
        // for new sized Platform
    }
}

std::shared_ptr<Entity> EntityManager::createLadder(const sf::Vector2f& pos, long wight, long height)
{
    if(wight < 0 || height < 0) return std::make_shared<Ladder>(
                SpritesSheet::GetInstance().getSprite("Ladder"),
                pos,
                EntityType::LADDER);
    else
    {
        // for new sized Ladder
    }
}
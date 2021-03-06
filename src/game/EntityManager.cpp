#include "EntityManager.h"
#include "SpritesSheet.h"

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
std::shared_ptr<Map> EntityManager::map;

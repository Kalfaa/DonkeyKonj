#include "pch.h"
#include "EntityManager.h"


const std::string EntityManager::MEDIA_PATH = "../Media";
const std::string EntityManager::TEXTURES_PATH = "../Media/Textures";

std::vector<std::shared_ptr<Entity>> EntityManager::entities;

/*std::shared_ptr<Entity> EntityManager::getPlayer()
{
    for (auto* entity : EntityManager::entities)
    {
        if (!entity->enabled)
        {
            continue;
        }

        if (entity->type == EntityType::player)
        {
            return entity;
        }
    }

    return nullptr;
}*/

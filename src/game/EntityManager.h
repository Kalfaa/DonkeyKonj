#pragma once

#include "Entity.h"

//#define shared_ptr_entity std::shared_ptr<Entity>

class EntityManager
{
public:
    EntityManager() = default;
    ~EntityManager() = default;

public:
    static std::vector<std::shared_ptr<Entity>> entities;
    //static std::shared_ptr<Entity> getPlayer();

    static const std::string MEDIA_PATH;
    static const std::string TEXTURES_PATH;
};


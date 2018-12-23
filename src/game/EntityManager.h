#pragma once

#include "Entity.h"

class EntityManager
{
public:
    EntityManager() = default;
    ~EntityManager() = default;

public:
    static std::vector<std::shared_ptr<Entity>> entities;
    static std::shared_ptr<Entity> getPlayer();

    static const std::string MEDIA_PATH;
    static const std::string TEXTURES_PATH;
};


#pragma once

#include "Entity.h"
#include "Player.h"

class EntityManager
{
public:
    EntityManager() = default;

    virtual ~EntityManager() = default;

public:
    //static std::unique<Entity> getPlayer();
public:
    static std::vector<std::shared_ptr<Entity>> entities;
    static std::shared_ptr<Player> player;

    static const std::string MEDIA_PATH;
    static const std::string TEXTURES_PATH;
    static const std::string MAP_PATH;
};


#pragma once

#include "pch.h"

#include "Entity.h"
#include "Player.h"
#include "Ladder.h"
#include "Platform.h"


class EntityManager
{
public:
    EntityManager() = default;

    virtual ~EntityManager() = default;

public:
    //static std::unique<Entity> getPlayer();
    static void removeFromEntities(std::shared_ptr<Entity> entity);

    static std::shared_ptr<Entity> createPlatform(const sf::Vector2f &pos, long wight, long height);

    static std::shared_ptr<Entity> createLadder(const sf::Vector2f &pos, long wight, long height);

public:
    static std::vector<std::shared_ptr<Entity>> entities;
    static std::shared_ptr<Player> player;
    //static std::shared_ptr<Player> scorePane;

    static const std::string MEDIA_PATH;
    static const std::string TEXTURES_PATH;
    static const std::string MAP_PATH;
};


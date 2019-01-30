//
// Created by damso on 24/01/19.
//

#ifndef DONKEYKONG_ENTITYGENERATOR_H
#define DONKEYKONG_ENTITYGENERATOR_H

#include "pch.h"

#include "Entity.h"
#include "SpritesSheet.h"
#include "Mario.h"
#include "BonusItem.h"
#include "ScoreTab.h"
#include "Barrel.h"
#include "DonkeyKong.h"


class EntityGenerator
{
public:
    typedef std::function<std::shared_ptr<Entity>(SpritesSheet &, const sf::Vector2f &,
                                                  const sf::Vector2f &)> FunctionPtrCreateEntity;

public:
    static std::shared_ptr<Entity> createPlatform(SpritesSheet &, const sf::Vector2f &pos, const sf::Vector2f &size);

    static std::shared_ptr<Entity> createLadder(SpritesSheet &, const sf::Vector2f &pos, const sf::Vector2f &size);

    static std::shared_ptr<Entity> createMario(SpritesSheet &, const sf::Vector2f &pos, const sf::Vector2f &size);

    static std::shared_ptr<Entity>
    createUmbrellaBonus(SpritesSheet &, const sf::Vector2f &pos, const sf::Vector2f &size);

    static std::shared_ptr<Entity>
    createHandbagBonus(SpritesSheet &, const sf::Vector2f &pos, const sf::Vector2f &size);

    static std::shared_ptr<Entity> createHatBonus(SpritesSheet &, const sf::Vector2f &pos, const sf::Vector2f &size);

    static std::shared_ptr<Entity> createTabScore(SpritesSheet &, const sf::Vector2f &pos, const sf::Vector2f &size);

    static std::shared_ptr<Entity> createBarrel(SpritesSheet &, const sf::Vector2f &pos, const sf::Vector2f &size);

    static std::shared_ptr<Entity> createDonkeyKong(SpritesSheet &, const sf::Vector2f &pos, const sf::Vector2f &size);
};

#endif //DONKEYKONG_ENTITYGENERATOR_H

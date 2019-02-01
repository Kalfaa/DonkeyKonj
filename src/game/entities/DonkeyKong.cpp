//
// Created by Kalfa on 28/01/2019.
//

#include "DonkeyKong.h"
#include "Barrel.h"

DonkeyKong::DonkeyKong(const sf::Sprite &sprite, const sf::Vector2f &posPlayer, EntityType type,
                       const SpritesPatterns &donkeyKong, const Barrel::SpritesPatterns &barrel)
        : Entity(sprite, posPlayer, type),
          patterns(donkeyKong),
          barrelPattern(barrel)
{
    HP = 3;
    state = GRINDING;
    timeAnimation = 0;
    state = NONE;
    timeBarrelLaunch = 0;
    BarrelCount = 0 ;
}

void DonkeyKong::update(sf::Time elapsedTime)
{
    sf::Vector2f grindLadder(0.f, -DK_SPEED * 2); // en attendant de trouver une maniere plus propre
    sf::Vector2f moveJump(0.f, -DK_SPEED);
    sf::Vector2f moveNotJump(0.f, +DK_SPEED);
    sf::Vector2f movement(0.f, 0.f);
    sf::Vector2f moveDown(0.f, DK_SPEED);
    sf::Vector2f moveUp(0.f, -DK_SPEED);
    sf::Vector2f moveRight(DK_SPEED, 0.f);
    sf::Vector2f moveLeft(-DK_SPEED, 0.f);


    timeAnimation += elapsedTime.asMilliseconds();
    timeBarrelLaunch += elapsedTime.asMilliseconds();
    sprite.move(moveDown * elapsedTime.asSeconds());
    if (!EntityManager::map->collide(sprite, EntityType::PLATFORM, DOWN)->collide)
    {
    }
    else
    {
        sprite.move(moveUp * elapsedTime.asSeconds());
    }
    //if(state == NONE) state = RIGHT ;
    if (state == RIGHT)
    {
        sprite.move(moveRight * elapsedTime.asSeconds());
    }
    else if (state == LEFT)
    {
        sprite.move(moveLeft * elapsedTime.asSeconds());

    }
    if (state == LAUNCHBARREL && BarrelCount <4)
    {
        std::random_device randomGenerator;
        int rand = randomGenerator() % 2;
        std::cout<< rand;
        sf::Vector2f posbarrel;
        if(rand ==1){
             posbarrel = {sprite.getPosition().x - 30, sprite.getPosition().y};
        }else{
             posbarrel = {sprite.getPosition().x , sprite.getPosition().y+100};
        }
        changeSprite(updateAnimation(&timeAnimation, 400, patterns.at(donkeyFace)));
        if (timeAnimation == 0)
        {

            createBarrel(*EntityManager::map, posbarrel);
            BarrelCount++;
        }

    }
    else if (timeBarrelLaunch > 5000)
    {
        state = LAUNCHBARREL;
    }

}

void DonkeyKong::createBarrel(Map map, sf::Vector2f pos)
{
    std::shared_ptr<Entity> barrel = std::make_shared<Barrel>(barrelPattern.at(Barrel::barrelHorizontal)[0],
                                                              pos,
                                                              EntityType::BARREL, barrelPattern);
    EntityManager::entities.push_back(barrel);
    //newMap->addEntityToMatrix(barrel);
    EntityManager::map->addMoovingObject(barrel);

}

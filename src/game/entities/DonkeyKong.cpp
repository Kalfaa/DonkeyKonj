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
    BarrelCount = 0;
    barrelFrequency = 0;
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
    if (state == LAUNCHBARREL && BarrelCount < 4)
    {
        barrelFrequency += elapsedTime.asMilliseconds();
        if (barrelFrequency > BARREL_FREQUENCY)
        {

            //std::random_device randomGenerator;
            int rand = std::rand() % 2;

            changeSprite(updateAnimation(&timeAnimation, 200, patterns.at(donkeyFace)));
            if (timeAnimation == 0)
            {
                sf::Vector2f posbarrel;
                if (rand == 1)
                {
                    posbarrel = {sprite.getPosition().x - 30, sprite.getPosition().y};
                }
                else
                {
                    posbarrel = {sprite.getPosition().x, sprite.getPosition().y + 100};
                }
                createBarrel(*EntityManager::map, posbarrel, Barrel::BarrelState::LEFT);

                BarrelCount++;
                barrelFrequency = 0;
            }
        }

    }
    else if (timeBarrelLaunch > BARREL_WAVE_FREQUENCY)
    {
        state = LAUNCHBARREL;
        if (BarrelCount == 4)
        {
            std::cout << "wait";
            state = NONE;
            timeBarrelLaunch = 0;
            BarrelCount = 0;
        }
    }


}

void DonkeyKong::createBarrel(Map map, sf::Vector2f pos, Barrel::BarrelState state)
{
    std::shared_ptr<Barrel> barrel = std::make_shared<Barrel>(barrelPattern.at(Barrel::barrelHorizontalLeft)[0],
                                                              pos,
                                                              EntityType::BARREL, barrelPattern);
    barrel->barrelState = state;
    EntityManager::entities.push_back(barrel);
    //newMap->addEntityToMatrix(barrel);
    EntityManager::map->addMoovingObject(barrel);

}

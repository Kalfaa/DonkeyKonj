//
// Created by theo on 16/01/19.
//

#include "Barrel.h"
#include "Map.h"

Barrel::Barrel(const sf::Sprite &sprite, const sf::Vector2f &posPlayer, EntityType type,
               const SpritesPatterns &barrelSprites)
        : Entity(sprite, posPlayer, type),
          patterns(barrelSprites)
{
    barrelState = NONE;
    countBeforeGrind = 0;
    timeAnimation = 0;

}


void Barrel::update(sf::Time elapsedTime)
{
    sf::Vector2f grindLadder(0.f, -BARREL_SPEED * 2); // en attendant de trouver une maniere plus propre
    sf::Vector2f moveDown(0.f, BARREL_SPEED);
    sf::Vector2f moveUp(0.f, -BARREL_SPEED);
    sf::Vector2f moveRight(BARREL_SPEED, 0.f);
    sf::Vector2f moveLeft(-BARREL_SPEED, 0.f);

    timeAnimation += elapsedTime.asMilliseconds();

    sprite.move(moveDown * elapsedTime.asSeconds());
    if (!EntityManager::map->collide(sprite, EntityType::PLATFORM, DOWN)->collide)
    {
    }
    else
    {
        sprite.move(moveUp * elapsedTime.asSeconds());
        if (barrelState == FALL)
        {
            barrelState = NONE;
        }
    }
    if (barrelState == NONE)
    {
        std::random_device randomGenerator;
        int rand = randomGenerator() % 2;
        if(rand== 1){
            barrelState = LEFT;
        }else{
            barrelState = RIGHT;
        }

    }

    if (EntityManager::map->collide(sprite, LADDER, DOWN, getHitboxLadder())->collide)
    {
        countBeforeGrind++;

        if (countBeforeGrind > 15)
        {
            sprite.move(-grindLadder * elapsedTime.asSeconds());
            changeSprite(updateAnimation(&timeAnimation, 200, patterns.at(barrelVertical)));
            barrelState = GRINDING;
        }
        else
        {
            if (barrelState == LEFT)
            {
                sprite.move(moveLeft * elapsedTime.asSeconds());
                changeSprite(updateAnimation(&timeAnimation, 200, patterns.at(barrelHorizontalLeft)));
            }
            if (barrelState == RIGHT)
            {
                sprite.move(moveRight * elapsedTime.asSeconds());
                changeSprite(updateAnimation(&timeAnimation, 200, patterns.at(barrelHorizontalRight)));
            }
        }
    }
    else
    {
        countBeforeGrind = 0;
        if(barrelState == GRINDING){
            std::random_device randomGenerator;
            int rand = randomGenerator() % 2;
            if(rand== 1){
                barrelState = LEFT;
            }else{
                barrelState = RIGHT;
            }
        }
        if (barrelState == LEFT)
        {

            sprite.move(moveLeft * elapsedTime.asSeconds());
            changeSprite(updateAnimation(&timeAnimation, 200, patterns.at(barrelHorizontalLeft)));
        }
        if (barrelState == RIGHT)
        {
            sprite.move(moveRight * elapsedTime.asSeconds());
            changeSprite(updateAnimation(&timeAnimation, 200, patterns.at(barrelHorizontalRight)));

        }
    }
}

sf::FloatRect Barrel::getHitboxLadder()
{
    sf::RectangleShape rectangle(sf::Vector2f(sprite.getGlobalBounds().width - 20,
                                              sprite.getGlobalBounds().height - 30));
    sf::Vector2f pos = sprite.getPosition();
    pos.y = pos.y + sprite.getGlobalBounds().height + 6;
    pos.x = 3 + pos.x + sprite.getGlobalBounds().width * 0.25;
    rectangle.setPosition(pos);
    return rectangle.getGlobalBounds();
}



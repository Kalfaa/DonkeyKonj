//
// Created by theo on 16/01/19.
//

#include "Barrel.h"
#include "Map.h"

Barrel::Barrel(const sf::Sprite &sprite, const sf::Vector2f &posPlayer, EntityType type,
               const SpritesPatterns &patterns)
        : Entity(sprite, posPlayer, type)
{
    barrelState = NONE;
    countBeforeGrind =0;
}

void Barrel::update(sf::Time elapsedTime,Map map) {
    sf::Vector2f grindLadder(0.f, -BARREL_SPEED*2); // en attendant de trouver une maniere plus propre
    sf::Vector2f moveJump(0.f, -BARREL_SPEED);
    sf::Vector2f moveNotJump(0.f, +BARREL_SPEED);
    sf::Vector2f movement(0.f,0.f);
    sf::Vector2f moveDown(0.f, BARREL_SPEED);
    sf::Vector2f moveUp(0.f, -BARREL_SPEED);
    sf::Vector2f moveRight(BARREL_SPEED, 0.f);
    sf::Vector2f moveLeft(-BARREL_SPEED, 0.f);
    sprite.move(moveDown * elapsedTime.asSeconds());
    if(!map.collide(sprite,EntityType::PLATFORM,DOWN )->collide ||  barrelState == GRINDING){
    }else{
        sprite.move(moveUp * elapsedTime.asSeconds());
        if(barrelState == FALL){
            barrelState=NONE;
        }
    }
    if(barrelState==NONE){
        barrelState=LEFT;
    }
    if(!map.collide(sprite,LADDER,DOWN)->collide && barrelState != GRINDING){
        if(barrelState==LEFT){
            sprite.move(moveLeft * elapsedTime.asSeconds());
        }
        if(barrelState == RIGHT){
            sprite.move(moveRight * elapsedTime.asSeconds());
        }
    }else{

        if(barrelState==RIGHT){
            printf("ECHELLE DROITE");
            barrelState = SOONRIGHT;

             countBeforeGrind =0;
        }
        else if(barrelState==LEFT){
            barrelState = SOONLEFT;
            printf("ECHELLE GAUCHE");
            countBeforeGrind =0;
        }
        if(barrelState==SOONRIGHT) {
            if (countBeforeGrind < 30) {
                sprite.move(moveRight * elapsedTime.asSeconds());
                countBeforeGrind++;
            } else {
                countBeforeGrind = 0;
                barrelState = GRINDING;
                grindingLadder = map.collide(sprite,LADDER,DOWN);
            }
        }else if(barrelState==SOONLEFT){
            if (countBeforeGrind<30){
                sprite.move(moveLeft * elapsedTime.asSeconds());
                countBeforeGrind++;
            }else{
                countBeforeGrind =0;
                barrelState = GRINDING;
                grindingLadder = map.collide(sprite,LADDER,DOWN);
            }
        }
        if(barrelState==GRINDING) {
            countBeforeGrind++;
            if (countBeforeGrind>60){
                countBeforeGrind =0;
                barrelState = FALL;
            }
        }
    }
}

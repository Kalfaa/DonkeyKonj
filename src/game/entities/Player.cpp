//
// Created by user on 25/12/2018.
//

#include "Game.h"
#include "Player.h"
#include "Ladder.h"

Player::Player(const sf::Sprite &sprite, const sf::Vector2f &posPlayer, EntityType type, float playerSpeed,
               const SpritesPatterns &playerSprites)
        : Entity(sprite, posPlayer, type),
          playerSpeed(playerSpeed), spritesPtns(playerSprites)
{
    MARIO_WIDTH = static_cast<int>(sprite.getGlobalBounds().width);
    MARIO_HEIGHT = static_cast<int>(sprite.getGlobalBounds().height);
    TimeAnimation = 0;
    hitboxUseForCollision = sprite;
}

void Player::update(sf::Time elapsedTime, Map map)
{
    sf::Vector2f grindLadder(0.f, -playerSpeed * 2); // en attendant de trouver une maniere plus propre
    sf::Vector2f moveJump(0.f, -MARIO_JUMP_SPEED);
    sf::Vector2f moveNotJump(0.f, +MARIO_JUMP_SPEED);
    sf::Vector2f movement(0.f, 0.f);
    sf::Vector2f moveDown(0.f, playerSpeed);
    sf::Vector2f moveUp(0.f, -playerSpeed);
    sf::Vector2f moveRight(playerSpeed, 0.f);
    sf::Vector2f moveLeft(-playerSpeed, 0.f);
    if (playerState != JUMP && playerState != STARTJUMP && playerState != GRINDING)
    {
        sprite.move(moveDown * elapsedTime.asSeconds());
        if (!collide(map, EntityType::PLATFORM, DOWN))
        {
            playerState = FALLING;
            //printf("gravity");
        }
        else
        {
            sprite.move(moveUp * elapsedTime.asSeconds());
            playerState = IDLE;
        }
    }
    else
    {
        //sprite.move(0.f,-playerSpeed);
        if (playerState == STARTJUMP)
        {
            playerState = JUMP;
            jumpValue = MARIO_JUMP_MAX;
        }
    }

    switch (direction)
    {
        case UP:
            if (collide(map, EntityType::LADDER, DOWN,getUpHitboxLadder()))
            {
                if(playerState==IDLE)TimeAnimation=0;
                sprite.move(moveUp * elapsedTime.asSeconds());
                playerState = GRINDING;
                TimeAnimation+=elapsedTime.asMilliseconds();
            }
            break;
        case DOWN:
            if(playerState==IDLE || playerState ==GRINDING)
            {

                if (collide(map, EntityType::LADDER, DOWN,getHitboxLadder()))
                {
                    sprite.move(moveDown * elapsedTime.asSeconds());
                    if(playerState==IDLE)TimeAnimation=0;
                    playerState = GRINDING;
                    TimeAnimation+=elapsedTime.asMilliseconds();

                }

            }
            break;
        case LEFT:
        {
            if (lastDirection != LEFT) TimeAnimation = 0;
            else TimeAnimation += elapsedTime.asMilliseconds();

            if (playerState != FALLING)
                changeSprite(updateAnimation(&TimeAnimation, 100, spritesPtns.at(movePatternLeft)));
            else changeSprite(spritesPtns.at(movePatternLeft)[0]);

            //printf("%d |",elapsedTime.asMilliseconds());
            sprite.move(moveLeft * elapsedTime.asSeconds());
            if (collide(map, EntityType::PLATFORM, RIGHT))
                sprite.move(moveRight * elapsedTime.asSeconds());

            lastDirection = LEFT;
            break;
        }
        case RIGHT:
            if (lastDirection != RIGHT)
            {
                TimeAnimation = 0;
            }
            else
            {
                TimeAnimation += elapsedTime.asMilliseconds();
            }
            //printf("%d |",elapsedTime.asMilliseconds());
            if (playerState != FALLING)
            {

                changeSprite(updateAnimation(&TimeAnimation, 100, spritesPtns.at(movePatternRight)));
            }
            else
            {
                changeSprite(spritesPtns.at(movePatternRight)[0]);
            }
            sprite.move(moveRight * elapsedTime.asSeconds());
            if (collide(map, EntityType::PLATFORM, RIGHT))
                sprite.move(moveLeft * elapsedTime.asSeconds());
            lastDirection = RIGHT;
            break;
        default:
            if (playerState != JUMP && playerState != STARTJUMP && playerState != FALLING)
            {
                if (lastDirection == LEFT)
                {
                    changeSprite(spritesPtns.at(movePatternLeft)[0]);
                }
                else
                {
                    changeSprite(spritesPtns.at(movePatternRight)[0]);
                }
                //lastDirection = NONE;
            }
    }
    switch (playerState)
    {
        case GRINDING:
            if (!collide(map, EntityType::LADDER, DOWN,getUpHitboxLadder()))
            {
                playerState = IDLE;

            }else{
                std::vector<sf::Sprite> grindAnimation;
                printf("%d",TimeAnimation);
                grindAnimation.push_back(spritesPtns.at(climbPatternRight)[0]);
                grindAnimation.push_back(spritesPtns.at(climbPatternLeft)[0]);
                changeSprite(updateAnimation(&TimeAnimation, 200, grindAnimation));
                printf("grinding");

            }
            break;
        case JUMP:
            sprite.move(moveJump * elapsedTime.asSeconds());
            if (!collide(map, EntityType::PLATFORM, RIGHT))
            {
                if (lastDirection == LEFT) changeSprite(spritesPtns.at(jumpPatternLeft)[0]);
                else changeSprite(spritesPtns.at(jumpPatternRight)[0]);
                jumpValue -= MARIO_JUMP_SPEED;
            }
            else
            {
                sprite.move(moveNotJump * elapsedTime.asSeconds());
                jumpValue = 0;
            }
            if (jumpValue <= 0)
            {
                playerState = IDLE;
            }
            break;
        case FALLING:
            if (lastDirection == LEFT) changeSprite(spritesPtns.at(jumpPatternLeft)[0]);
            else changeSprite(spritesPtns.at(jumpPatternRight)[0]);
            break;
        case IDLE:
            //changeSprite(spritesPtns.at(movePatternLeft)[0]);
        default:;

    }
    direction = NONE;
}


void Player::move(Direction direction)
{
    this->direction = direction;
}

void Player::jump()
{
    if (FALLING != playerState)playerState = STARTJUMP;
}

bool Player::collide(Map map, EntityType entityType, Direction direction)
{
    hitboxUseForCollision.setPosition(sprite.getPosition());
    return map.collide(hitboxUseForCollision,entityType,direction)->collide;

}



sf::FloatRect Player::getRectUnderMario()
{
    sf::RectangleShape rectangle(sf::Vector2f(hitboxUseForCollision.getGlobalBounds().width,
                                              hitboxUseForCollision.getGlobalBounds().height-30));
    sf::Vector2f pos=hitboxUseForCollision.getPosition();
    pos.y = pos.y+hitboxUseForCollision.getGlobalBounds().height;
    rectangle.setPosition(pos);
    return rectangle.getGlobalBounds();;
}

sf::FloatRect Player::getHitboxLadder()
{
    sf::RectangleShape rectangle(sf::Vector2f(hitboxUseForCollision.getGlobalBounds().width-20,
                                              hitboxUseForCollision.getGlobalBounds().height-30));
    sf::Vector2f pos=hitboxUseForCollision.getPosition();
    pos.y = pos.y+hitboxUseForCollision.getGlobalBounds().height+2;
    pos.x = 3+pos.x+hitboxUseForCollision.getGlobalBounds().width*0.25;
    rectangle.setPosition(pos);
    return rectangle.getGlobalBounds();
}



bool Player::collide(Map map, EntityType entityType, Direction direction, sf::FloatRect rect)
{
    hitboxUseForCollision.setPosition(sprite.getPosition());
    return map.collide(hitboxUseForCollision,entityType,direction,rect)->collide;
}

sf::FloatRect Player::getUpHitboxLadder()
{
    sf::RectangleShape rectangle(sf::Vector2f(hitboxUseForCollision.getGlobalBounds().width-20,
                                              hitboxUseForCollision.getGlobalBounds().height-30));
    sf::Vector2f pos=hitboxUseForCollision.getPosition();
    pos.y = pos.y+hitboxUseForCollision.getGlobalBounds().height-11;
    pos.x = 3+pos.x+hitboxUseForCollision.getGlobalBounds().width*0.25;
    rectangle.setPosition(pos);
    return rectangle.getGlobalBounds();
}








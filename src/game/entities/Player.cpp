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
        if (!map.collide(sprite, EntityType::PLATFORM, DOWN)->collide)
        {
            playerState = FALLING;
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
            if (map.collide(sprite, EntityType::LADDER, DOWN)->collide)
            {
                sprite.move(grindLadder * elapsedTime.asSeconds());
                playerState = GRINDING;
            }
            break;
        case DOWN:
            /*if(!collide(map,EntityType::PLATFORM,DOWN))
                movement.y += playerSpeed;*/
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
            if (map.collide(sprite, EntityType::PLATFORM, RIGHT)->collide)
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
            if (map.collide(sprite, EntityType::PLATFORM, RIGHT)->collide)
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
            if (!map.collide(sprite, EntityType::LADDER, DOWN)->collide)
            {
                playerState = IDLE;
            }
        case JUMP:
            sprite.move(moveJump * elapsedTime.asSeconds());
            if (!map.collide(sprite, EntityType::PLATFORM, RIGHT)->collide)
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
        case FALLING:
            if (lastDirection == LEFT) changeSprite(spritesPtns.at(jumpPatternLeft)[0]);
            else changeSprite(spritesPtns.at(jumpPatternRight)[0]);
        case IDLE:
            //changeSprite(spritesPtns.at(movePatternLeft)[0]);
        default:;

    }
    direction = NONE;
}

void Player::changeSprite(sf::Sprite newSprite)
{
    sf::Vector2f tempos = sprite.getPosition();
    sprite = std::move(newSprite);
    sprite.setPosition(tempos);

}

void Player::move(Direction direction)
{
    this->direction = direction;
}

void Player::jump()
{
    if (FALLING != playerState)playerState = STARTJUMP;
}

sf::Sprite Player::updateAnimation(int *now, int frequency, std::vector<sf::Sprite> animation)
{
    if (*now / frequency >= animation.size()) *now = 0;
    return animation[*now / frequency];
}








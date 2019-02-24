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
    life = 3;
}

void Player::update(sf::Time elapsedTime)
{
    sf::Vector2f moveJump(0.f, -MARIO_JUMP_SPEED);
    sf::Vector2f moveNotJump(0.f, +MARIO_JUMP_SPEED);
    if (playerState == DYING)
    {
        TimeAnimation += elapsedTime.asMilliseconds();
        changeSprite(updateAnimation(&TimeAnimation, 300, spritesPtns.at(deadPatternRight)));
        if (TimeAnimation == 0)
        {
            kill();
        }
        return;
    }
    if (collide(*EntityManager::map, EntityType::BARREL, DOWN) && playerState != DYING)
    {
        playerState = DYING;
        TimeAnimation = 0;
        return;
    }

    if (playerState != JUMP && playerState != STARTJUMP && playerState != GRINDING)
    {
        applyGravity(elapsedTime);
    }

    if (playerState == STARTJUMP)
    {
        playerState = JUMP;
        jumpValue = MARIO_JUMP_MAX;
    }

    move(elapsedTime);
    switch (playerState)
    {
        case GRINDING:
            if (!collide(*EntityManager::map, EntityType::LADDER, DOWN, getUpHitboxLadder()))
            {
                playerState = IDLE;
            }
            else
            {
                std::vector<sf::Sprite> grindAnimation;
                grindAnimation.push_back(spritesPtns.at(climbPatternRight)[0]);
                grindAnimation.push_back(spritesPtns.at(climbPatternLeft)[0]);
                changeSprite(updateAnimation(&TimeAnimation, 200, grindAnimation));
            }
            break;
        case JUMP:
            sprite.move(moveJump * elapsedTime.asSeconds());
            if (!collide(*EntityManager::map, EntityType::PLATFORM, RIGHT))
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
    if (FALLING != playerState && playerState != DYING)playerState = STARTJUMP;
}

bool Player::collide(Map map, EntityType entityType, Direction direction)
{
    hitboxUseForCollision.setPosition(sprite.getPosition());
    return map.collide(hitboxUseForCollision, entityType, direction)->collide;

}


sf::FloatRect Player::getRectUnderMario()
{
    sf::RectangleShape rectangle(sf::Vector2f(hitboxUseForCollision.getGlobalBounds().width,
                                              hitboxUseForCollision.getGlobalBounds().height - 30));
    sf::Vector2f pos = hitboxUseForCollision.getPosition();
    pos.y = pos.y + hitboxUseForCollision.getGlobalBounds().height;
    rectangle.setPosition(pos);
    return rectangle.getGlobalBounds();;
}

sf::FloatRect Player::getHitboxLadder()
{
    sf::RectangleShape rectangle(sf::Vector2f(hitboxUseForCollision.getGlobalBounds().width - 20,
                                              hitboxUseForCollision.getGlobalBounds().height - 30));
    sf::Vector2f pos = hitboxUseForCollision.getPosition();
    pos.y = pos.y + hitboxUseForCollision.getGlobalBounds().height + 2;
    pos.x = 3 + pos.x + hitboxUseForCollision.getGlobalBounds().width * 0.25;
    rectangle.setPosition(pos);
    return rectangle.getGlobalBounds();
}


bool Player::collide(Map map, EntityType entityType, Direction direction, sf::FloatRect rect)
{
    hitboxUseForCollision.setPosition(sprite.getPosition());
    return map.collide(hitboxUseForCollision, entityType, direction, rect)->collide;
}

sf::FloatRect Player::getUpHitboxLadder()
{
    sf::RectangleShape rectangle(sf::Vector2f(hitboxUseForCollision.getGlobalBounds().width - 20,
                                              hitboxUseForCollision.getGlobalBounds().height - 30));
    sf::Vector2f pos = hitboxUseForCollision.getPosition();
    pos.y = pos.y + hitboxUseForCollision.getGlobalBounds().height - 11;
    pos.x = 3 + pos.x + hitboxUseForCollision.getGlobalBounds().width * 0.25;
    rectangle.setPosition(pos);
    return rectangle.getGlobalBounds();
}

void Player::applyGravity(sf::Time elapsedTime)
{
    sprite.move(moveDown() * elapsedTime.asSeconds());
    if (!collide(*EntityManager::map, EntityType::PLATFORM, DOWN))
    {
        playerState = FALLING;
        //printf("gravity");
    }
    else
    {
        sprite.move(moveUp() * elapsedTime.asSeconds());
        playerState = IDLE;
    }
}

sf::Vector2f Player::moveUp()
{
    sf::Vector2f vec(0.f, -playerSpeed);
    return vec;
}

sf::Vector2f Player::moveDown()
{
    sf::Vector2f vec(0.f, playerSpeed);
    return vec;
}

sf::Vector2f Player::moveLeft()
{
    sf::Vector2f vec(-playerSpeed, 0.f);
    return vec;
}

sf::Vector2f Player::moveRight()
{
    sf::Vector2f vec(playerSpeed, 0.f);
    return vec;
}

void Player::move(sf::Time elapsedTime)
{

    switch (direction)
    {
        case UP:
            if (collide(*EntityManager::map, EntityType::LADDER, DOWN, getUpHitboxLadder()))
            {
                if (playerState == IDLE)TimeAnimation = 0;
                sprite.move(moveUp() * elapsedTime.asSeconds());
                playerState = GRINDING;
                TimeAnimation += elapsedTime.asMilliseconds();
            }
            break;
        case DOWN:
            if (playerState == IDLE || playerState == GRINDING)
            {

                if (collide(*EntityManager::map, EntityType::LADDER, DOWN, getHitboxLadder()))
                {
                    sprite.move(moveDown() * elapsedTime.asSeconds());
                    if (playerState == IDLE)TimeAnimation = 0;
                    playerState = GRINDING;
                    TimeAnimation += elapsedTime.asMilliseconds();

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
            sprite.move(moveLeft() * elapsedTime.asSeconds());
            if (collide(*EntityManager::map, EntityType::PLATFORM, RIGHT))
                sprite.move(moveRight() * elapsedTime.asSeconds());

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
            sprite.move(moveRight() * elapsedTime.asSeconds());
            if (collide(*EntityManager::map, EntityType::PLATFORM, RIGHT))
                sprite.move(moveLeft() * elapsedTime.asSeconds());
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


}

void Player::kill()
{
    sprite.setPosition(EntityManager::map->startpoint);
    playerState = IDLE;
    life--;
}








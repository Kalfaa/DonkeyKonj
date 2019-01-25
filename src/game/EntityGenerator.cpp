//
// Created by damso on 24/01/19.
//

#include "EntityGenerator.h"
#include "Map.h"

using namespace std;


std::shared_ptr<Entity> EntityGenerator::createPlatform(SpritesSheet& spritesSheet, const sf::Vector2f& pos, const sf::Vector2f& size)
{
    std::shared_ptr<Entity> platform;

    if(size.x < 0 && size.y < 0)
    {
        platform = std::make_shared<Platform>(spritesSheet.getSprite("PlatformRed"), pos, EntityType::PLATFORM);
    }
    else
    {
        sf::Sprite sp = spritesSheet.getSprite("PlatformRed");

        int sizeX = static_cast<int>((size.x < 0) ? sp.getTextureRect().width : size.x / sp.getScale().x);
        int sizeY = static_cast<int>((size.y < 0) ? sp.getTextureRect().height : size.y / sp.getScale().y);

        sp.setTextureRect(sf::IntRect(0, 0, sizeX, sizeY));
        platform = std::make_shared<Platform>(sp, pos, EntityType::PLATFORM);
    }


    EntityManager::entities.push_back(platform);
    return platform;
}

std::shared_ptr<Entity> EntityGenerator::createLadder(SpritesSheet& spritesSheet, const sf::Vector2f& pos, const sf::Vector2f& size)
{
    std::shared_ptr<Entity> ladder;

    if(size.x < 0 && size.y < 0)
    {
        ladder = std::make_shared<Ladder>(spritesSheet.getSprite("Ladder"), pos, EntityType::LADDER);
    }
    else
    {
        sf::Sprite sp = spritesSheet.getSprite("Ladder");

        int sizeX = static_cast<int>((size.x < 0) ? sp.getTextureRect().width : size.x / sp.getScale().x);
        int sizeY = static_cast<int>((size.y < 0) ? sp.getTextureRect().height : size.x / sp.getScale().x);

        sp.setTextureRect(sf::IntRect(0, 0, sizeX, sizeY));
        ladder = std::make_shared<Ladder>(sp, pos, EntityType::LADDER);
    }

    EntityManager::entities.push_back(ladder);
    return ladder;
}

std::shared_ptr<Entity> EntityGenerator::createMario(SpritesSheet& spritesSheet, const sf::Vector2f& pos, const sf::Vector2f& size)
{
    std::shared_ptr<Player> mario;

    Mario::SpritesPatterns spritesPatterns
            {
                    {Player::climbPatternLeft,      spritesSheet.getPattern("MarioClimbLeft")},
                    {Player::climbPatternRight,     spritesSheet.getOppositePattern("MarioClimbLeft")},
                    {Player::deadPatternLeft,       spritesSheet.getPattern("MarioLeftSlide")},
                    {Player::deadPatternRight,      spritesSheet.getOppositePattern("MarioLeftSlide")},
                    {Player::fightPatternLeft,      spritesSheet.getPattern("MarioMoveLeftArm")},
                    {Player::fightPatternRight,     spritesSheet.getOppositePattern("MarioMoveLeftArm")},
                    {Player::moveFightPatternLeft,  spritesSheet.getPattern("MarioLeftArm")},
                    {Player::moveFightPatternRight, spritesSheet.getOppositePattern("MarioLeftArm")},
                    {Player::movePatternLeft,       spritesSheet.getPattern("MarioLeft")},
                    {Player::movePatternRight,      spritesSheet.getOppositePattern("MarioLeft")},
                    {Player::jumpPatternLeft,       std::vector<sf::Sprite>(1, spritesSheet.getSprite("MarioLeftJump"))},
                    {Player::jumpPatternRight,      std::vector<sf::Sprite>(1, spritesSheet.getOppositeSprite("MarioLeftJump"))}
            };

    mario = std::make_shared<Mario>(spritesPatterns.at(Player::movePatternLeft)[0], pos,
                                    EntityType::PLAYER, 100.f, spritesPatterns);


    EntityManager::player = mario;
    return mario;

}
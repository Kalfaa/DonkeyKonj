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

        int sizeX = static_cast<int>((size.x < 0) ? sp.getTextureRect().width : size.x);
        int sizeY = static_cast<int>((size.y < 0) ? sp.getTextureRect().height : size.y);

        cerr << " YO " << sp.getTextureRect().width << "  " << sp.getTextureRect().height << endl;

        sp.setTextureRect(sf::IntRect(0, 0, sizeX, sizeY));
        sp.setScale(2.5f, 2.5f);
        cerr << sp.getGlobalBounds().height << "  " << sp.getGlobalBounds().width << endl;
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
        int sizeY = static_cast<int>((size.y < 0) ? sp.getTextureRect().height : size.y / sp.getScale().y);

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

std::shared_ptr<Entity>
EntityGenerator::createUmbrellaBonus(SpritesSheet & sps, const sf::Vector2f &pos, const sf::Vector2f &size)
{
    std::shared_ptr<BonusItem> bonus = std::make_shared<BonusItem>(sps.getSprite("UmbrellaBonus"),
                                                                   pos,
                                                                   EntityType::BONUS_ITEM,
                                                                   100,
                                                                   sps.getSprite("100Bonus"));
    EntityManager::entities.push_back(bonus);
    return bonus;
}

std::shared_ptr<Entity>
EntityGenerator::createHandbagBonus(SpritesSheet & sps, const sf::Vector2f &pos, const sf::Vector2f &size)
{
    std::shared_ptr<BonusItem> bonus = std::make_shared<BonusItem>(sps.getSprite("HandbagBonus"),
                                pos,
                                EntityType::BONUS_ITEM,
                                300,
                                sps.getSprite("300Bonus"));
    EntityManager::entities.push_back(bonus);
    return bonus;
}

std::shared_ptr<Entity>
EntityGenerator::createHatBonus(SpritesSheet & sps, const sf::Vector2f &pos, const sf::Vector2f &size)
{
    std::shared_ptr<BonusItem> bonus = std::make_shared<BonusItem>(sps.getSprite("HatBonus"),
                                                                   pos,
                                                                   EntityType::BONUS_ITEM,
                                                                   500,
                                                                   sps.getSprite("500Bonus"));
    EntityManager::entities.push_back(bonus);
    return bonus;
}

std::shared_ptr<Entity>
EntityGenerator::createTabScore(SpritesSheet& sps, const sf::Vector2f& pos, const sf::Vector2f& size)
{
    std::shared_ptr<Entity> scoreTab = std::make_shared<ScoreTab>(sps.getSprite("BonusPanel0"),
                                                                  pos,
                                                                  EntityType::SCORE_TAB);

    EntityManager::entities.push_back(scoreTab);
    return scoreTab;
}

std::shared_ptr<Entity>
EntityGenerator::createBarrel(SpritesSheet &, const sf::Vector2f &pos, const sf::Vector2f &size)
{
    return shared_ptr<Entity>();
}

std::shared_ptr<Entity>
EntityGenerator::createDonkeyKong(SpritesSheet &, const sf::Vector2f &pos, const sf::Vector2f &size)
{
    return shared_ptr<Entity>();
}
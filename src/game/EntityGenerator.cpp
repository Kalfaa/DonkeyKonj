//
// Created by damso on 24/01/19.
//

#include "EntityGenerator.h"
#include "Map.h"

using namespace std;


std::shared_ptr<Entity>
EntityGenerator::createPlatform(SpritesSheet &spritesSheet, const sf::Vector2f &pos, const sf::Vector2f &size)
{
    std::shared_ptr<Entity> platform;

    if (size.x < 0 && size.y < 0)
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

std::shared_ptr<Entity>
EntityGenerator::createLadder(SpritesSheet &spritesSheet, const sf::Vector2f &pos, const sf::Vector2f &size)
{
    std::shared_ptr<Entity> ladder;

    if (size.x < 0 && size.y < 0)
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

std::shared_ptr<Entity>
EntityGenerator::createMario(SpritesSheet &spritesSheet, const sf::Vector2f &pos, const sf::Vector2f &size)
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
                    {Player::jumpPatternLeft,       std::vector<sf::Sprite>(1,
                                                                            spritesSheet.getSprite("MarioLeftJump"))},
                    {Player::jumpPatternRight,      std::vector<sf::Sprite>(1, spritesSheet.getOppositeSprite(
                            "MarioLeftJump"))}
            };

    mario = std::make_shared<Mario>(spritesPatterns.at(Player::movePatternLeft)[0], pos,
                                    EntityType::PLAYER, 100.f, spritesPatterns);


    EntityManager::player = mario;

    /// If the entity must be store in the matrix, else return UNKNOWN
    return std::shared_ptr<Entity>();
}

std::shared_ptr<Entity>
EntityGenerator::createUmbrellaBonus(SpritesSheet &sps, const sf::Vector2f &pos, const sf::Vector2f &size)
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
EntityGenerator::createHandbagBonus(SpritesSheet &sps, const sf::Vector2f &pos, const sf::Vector2f &size)
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
EntityGenerator::createHatBonus(SpritesSheet &sps, const sf::Vector2f &pos, const sf::Vector2f &size)
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
EntityGenerator::createTabScore(SpritesSheet &sps, const sf::Vector2f &pos, const sf::Vector2f &size)
{
    std::shared_ptr<Entity> scoreTab = std::make_shared<ScoreTab>(sps.getSprite("BonusPanel0"),
                                                                  pos,
                                                                  EntityType::SCORE_TAB);

    EntityManager::entities.push_back(scoreTab);
    return scoreTab;
}

std::shared_ptr<Entity>
EntityGenerator::createBarrel(SpritesSheet &sps, const sf::Vector2f &pos, const sf::Vector2f &size)
{
//    Barrel::SpritesPatterns spritesPatternsBarrel
//    {
//        {Barrel::barrel, std::vector<sf::Sprite>(1, sps.getSprite("Barrel"))},
//        {Barrel::barrelHorizontal, sps.getPattern("BarrelHorizontal")},
//        {Barrel::barrelVertical, sps.getPattern("BarrelVertical")}
//    };
//
//    std::shared_ptr<Entity> barrel =
//
//    EntityManager::entities.push_back(scoreTab);
    return shared_ptr<Entity>();
}

std::shared_ptr<Entity>
EntityGenerator::createDonkeyKong(SpritesSheet &sps, const sf::Vector2f &pos, const sf::Vector2f &size)
{
    Barrel::SpritesPatterns spritesPatternsBarrel
            {
                    {Barrel::barrel,           std::vector<sf::Sprite>(1, sps.getSprite("Barrel"))},
                    {Barrel::barrelHorizontalLeft, sps.getOppositePattern("BarrelHorizontal")},
                    {Barrel::barrelHorizontalRight, sps.getPattern("BarrelHorizontal")},
                    {Barrel::barrelVertical,   sps.getPattern("BarrelVertical")}
            };

    DonkeyKong::SpritesPatterns spritesPatternDk
            {
                    {DonkeyKong::donkeyFace, sps.getPattern("DonkeyKongFace")}
            };

    std::shared_ptr<Entity> dk = std::make_shared<DonkeyKong>(spritesPatternDk.at(DonkeyKong::donkeyFace)[0],
                                                              pos,
                                                              EntityType::DONKEYKONG,
                                                              spritesPatternDk,
                                                              spritesPatternsBarrel);
    EntityManager::entities.push_back(dk);

    /// If the entity must be store in the matrix, else return UNKNOWN
    return std::shared_ptr<Entity>();
}

std::shared_ptr<Entity> EntityGenerator::createPeach(SpritesSheet & sps, const sf::Vector2f &pos, const sf::Vector2f &size)
{
    Peach::SpritesPatterns patternsPeach
    {
            {Peach::peachRight , sps.getPattern("PeachRight")},
            {Peach::peachLeft , sps.getOppositePattern("PeachRight")},
            {Peach::peachHelpRight , sps.getPattern("PeachHelpRight")},
            {Peach::peachHelpLeft , sps.getOppositePattern("PeachHelpRight")}
    };
    std::shared_ptr<Entity> peach = std::make_shared<Peach>(patternsPeach.at(Peach::peachLeft)[0], pos,
                                                            EntityType::PEACH,patternsPeach );

    EntityManager::entities.push_back(peach);

    return peach;
}

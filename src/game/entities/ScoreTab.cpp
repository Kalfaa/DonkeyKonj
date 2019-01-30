//
// Created by damso on 23/01/19.
//

#include "ScoreTab.h"
#include "Map.h"

ScoreTab::ScoreTab(const sf::Sprite &sprite, const sf::Vector2f &position, EntityType type)
        : StaticEntity(sprite,
                       position,
                       type)
{
}

void ScoreTab::update(sf::Time time1, std::shared_ptr<Map> map)
{
    StaticEntity::update(time1, map);
}

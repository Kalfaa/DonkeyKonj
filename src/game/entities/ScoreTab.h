//
// Created by damso on 23/01/19.
//

#ifndef DONKEYKONG_SCORETAB_H
#define DONKEYKONG_SCORETAB_H

#include "StaticEntity.h"

class ScoreTab : public StaticEntity
{
public:
    ScoreTab(const sf::Sprite &sprite, const sf::Vector2f &pos, EntityType type);

    ~ScoreTab() override = default;

public:

    void update(sf::Time time1, Map map) override;

public:
    unsigned long scoreValue = 0;

};


#endif //DONKEYKONG_SCORETAB_H

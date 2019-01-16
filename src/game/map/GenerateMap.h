//
// Created by user on 25/12/2018.
//

#ifndef DONKEYKONG_GENERATEMAP_H
#define DONKEYKONG_GENERATEMAP_H

#include "pch.h"
#include "Map.h"
#include "EntityManager.h"

class GenerateMap
{
public:
    GenerateMap(const std::map<char, StaticEntity> &staticObjects);

    virtual ~GenerateMap() = default;

public:
    std::shared_ptr<Map> createMap(std::string mapFile);

private:
    std::map<char, StaticEntity> staticObjects;
};


#endif //DONKEYKONG_GENERATEMAP_H

//
// Created by user on 25/12/2018.
//

#ifndef DONKEYKONG_GENERATEMAP_H
#define DONKEYKONG_GENERATEMAP_H

#include "pch.h"
#include "Map.h"
#include "EntityManager.h"

class Entity;

class GenerateMap
{
public:
    explicit GenerateMap(const std::map<std::string, EntityManager::FunctionPtrCreateEntity> & mapEntity);

    virtual ~GenerateMap() = default;

public:
    std::shared_ptr<Map> createMap(unsigned int sizeX, unsigned int sizeY, std::string mapFile);
    void addElementToMap(const std::string& posElementFile, Map&);
    void addElementToMap(const std::vector<std::shared_ptr<Entity>>& entityList, Map&);

private:
    void addSprite(unsigned int posX, unsigned int posY, EntityManager::FunctionPtrCreateEntity generateEntity, std::shared_ptr<Map>&);
    void addResizedSprite(unsigned int pos[4], EntityManager::FunctionPtrCreateEntity generateEntity, std::shared_ptr<Map>&);

private:
    std::map<std::string, EntityManager::FunctionPtrCreateEntity> mapEntity;
};


#endif //DONKEYKONG_GENERATEMAP_H

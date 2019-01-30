//
// Created by user on 25/12/2018.
//

#ifndef DONKEYKONG_GENERATEMAP_H
#define DONKEYKONG_GENERATEMAP_H

#include "pch.h"
#include "Map.h"
#include "EntityGenerator.h"

class Entity;

class GenerateMap
{
public:
    explicit GenerateMap(const SpritesSheet &,
                         const std::map<std::string, EntityGenerator::FunctionPtrCreateEntity> &mapEntity);

    virtual ~GenerateMap() = default;

public:
    std::shared_ptr<Map> createMap(unsigned int sizeX, unsigned int sizeY, std::string mapFile);

    void addElementToMap(const std::string &posElementFile, Map &);

    void addElementToMap(const std::vector<std::shared_ptr<Entity>> &entityList, Map &);

private:
    void addSprite(unsigned int posX, unsigned int posY, EntityGenerator::FunctionPtrCreateEntity generateEntity,
                   std::shared_ptr<Map> &);

    void addResizedSprite(long pos[4], EntityGenerator::FunctionPtrCreateEntity generateEntity, std::shared_ptr<Map> &);

private:
    std::map<std::string, EntityGenerator::FunctionPtrCreateEntity> mapEntity;
    SpritesSheet spritesSheet;
};


#endif //DONKEYKONG_GENERATEMAP_H

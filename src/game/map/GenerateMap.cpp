//
// Created by user on 25/12/2018.
//

#include "GenerateMap.h"
#include "Entity.h"

using namespace std;

GenerateMap::GenerateMap(const std::map<string, EntityManager::FunctionPtrCreateEntity> &mapEntity)
        : mapEntity(mapEntity)
{
}

shared_ptr<Map> GenerateMap::createMap(unsigned int sizeX, unsigned int sizeY, std::string mapFile)
{
    string fileName = EntityManager::MAP_PATH + "/" + mapFile;
    ifstream mapF(fileName.c_str());
    if (!mapF) throw std::runtime_error("Could not open file");

    shared_ptr<Map> map = make_shared<Map>();

    string entityName;
    //Entity entity;
    string bracket;
    while (!mapF.eof())
    {
        mapF >> entityName;

        if(entityName.empty()) break;
        if(mapEntity.find(entityName) == mapEntity.end())
            throw std::runtime_error("Generation of Map fail : \"" + entityName + "\" is not a valid key");

        mapF >> bracket;

        unsigned int tabPos[4] = {'\0', '\0', '\0', '\0'};

        while(bracket != "}")
        {
            fpos<mbstate_t> pos;
            unsigned int cnt;
            string next;

            for(cnt = 0; cnt < 4; cnt++)
            {
                pos = mapF.tellg();
                mapF >> next;

                if(next == ";") break;

                mapF.seekg(pos);
                mapF >> tabPos[cnt];
            }
            if(cnt == 2) addSprite(tabPos[0], tabPos[1], mapEntity[entityName],  map);
            else
            {
                addResizedSprite(tabPos, mapEntity[entityName], map);
                mapF >> next;            /// To pass the ';' forgive
            }

            pos = mapF.tellg();
            mapF >> bracket;
            mapF.seekg(pos);
        }
        mapF >> bracket;
    }

    return map;
}

void GenerateMap::addElementToMap(const std::string &posElementFile, Map &map)
{

}

void GenerateMap::addElementToMap(const std::vector<std::shared_ptr<Entity>> &entityList, Map &map)
{

}

void GenerateMap::addSprite(unsigned int posX, unsigned int posY, EntityManager::FunctionPtrCreateEntity generateEntity, shared_ptr<Map>& map)
{
//    entity.position.x = posX;
//    entity.position.y = posY;
//    entity.sprite.setPosition(entity.position);
//
//    shared_ptr<Entity> entityPtr = make_shared<Entity>(entity);
//    EntityManager::entities.push_back(entityPtr);
//    map->addEntityToMatrix(entityPtr);
}

void GenerateMap::addResizedSprite(unsigned int pos[4], EntityManager::FunctionPtrCreateEntity generateEntity, shared_ptr<Map>& map)
{
//    entity.position.x = pos[0];
//    entity.position.y = pos[1];
//    entity.sprite.setPosition(entity.position);
//
//    auto sizeX = static_cast<unsigned int>(std::abs(static_cast<double>(pos[2]) - static_cast<double>(pos[0])));
//    auto sizeY = static_cast<unsigned int>(std::abs(static_cast<double>(pos[3]) - static_cast<double>(pos[1])));
//    entity.sprite.setTextureRect(sf::IntRect(pos[0], pos[1], sizeX, sizeY));
//
//    shared_ptr<Entity> entityPtr = make_shared<Entity>(entity);
//    EntityManager::entities.push_back(entityPtr);
//    map->addEntityToMatrix(entityPtr);
}





//
// Created by user on 25/12/2018.
//

#include "GenerateMap.h"
#include "Entity.h"

using namespace std;

GenerateMap::GenerateMap(const std::map<string, Entity> &mapEntity)
        : mapEntity(mapEntity)
{
}

shared_ptr<Map> GenerateMap::createMap(unsigned int sizeX, unsigned int sizeY, std::string mapFile)
{
    cerr << "GenerateMap::createMap BEG" << endl;

    string fileName = EntityManager::MAP_PATH + "/" + mapFile;
    ifstream mapF(fileName.c_str());
    if (!mapF) throw std::runtime_error("Could not open file");

    shared_ptr<Map> map = make_shared<Map>();

    string entityName;
    Entity entity;
    string bracket;
    while (!mapF.eof())
    {
        mapF >> entityName;
        cerr << entityName << endl;

        if(entityName.empty()) break;
        if(mapEntity.find(entityName) == mapEntity.end())
            throw std::runtime_error("Generation of Map fail : \"" + entityName + "\" is not a valid key");

        mapF >> bracket;
        cerr << bracket << endl;

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
                cerr << "next:" << next << endl;

                if(next == ";") break;

                mapF.seekg(pos);
                mapF >> tabPos[cnt];
                cerr << tabPos[cnt] << endl;
            }
            if(cnt == 2) addSprite(tabPos[0], tabPos[1]);
            else
            {
                addResizedSprite(tabPos);
                mapF >> next;            /// To pass the ';' forgive
                cerr << next << endl;
            }

            pos = mapF.tellg();
            mapF >> bracket;
            cerr << bracket << endl;

            mapF.seekg(pos);
        }

        mapF >> bracket;
        cerr << bracket << endl;

        //return map;
    }

    cerr << "GenerateMap::createMap END" << endl;

    return map;
}

void GenerateMap::addElementToMap(const std::string &posElementFile, Map &map)
{

}

void GenerateMap::addElementToMap(const std::vector<std::shared_ptr<Entity>> &entityList, Map &map)
{

}

void GenerateMap::addSprite(unsigned int posX, unsigned int posY)
{

}

void GenerateMap::addResizedSprite(unsigned int *pos)
{

}

// TODO : Exception CharNotFound
// TODO : Size of StaticEntity generated ?

//while (!flux.eof())
//{
//string spriteName;
//flux >> spriteName;
//// flux.eof() doesn't work... :(
//if (spriteName.empty()) break;
//
//array<int, 4> tab{};
//for_each(tab.begin(), tab.end(), [&flux](int &n)
//{
//flux >> n;
//});
//
//mapSettings.insert(pair<string, array<int, 4>>(spriteName, tab));
//}
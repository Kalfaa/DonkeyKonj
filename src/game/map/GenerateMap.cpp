//
// Created by user on 25/12/2018.
//

#include "GenerateMap.h"

using namespace std;

GenerateMap::GenerateMap(const std::map<char, StaticEntity>& staticObjects)
    : staticObjects(staticObjects) {}

shared_ptr<Map> GenerateMap::createMap(std::string mapFile)
{
    string fileName = EntityManager::MAP_PATH + "/" + mapFile;
    ifstream mapF(fileName.c_str());
    if(!mapF) throw std::runtime_error("Could not open file");

    shared_ptr<Map> map = make_shared<Map>();
    string line;

    while (std::getline(mapF, line))
    {
        for(char c : line)
        {

        }
    }
    return map;
}

// TODO : Exception CharNotFound
// TODO : Size of StaticEntity generated ?

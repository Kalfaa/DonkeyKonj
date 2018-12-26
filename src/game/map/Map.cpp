#include <utility>

//
// Created by user on 25/12/2018.
//

#include "Map.h"


Map::Map(){
    entity2DArray = std::vector<std::vector<std::shared_ptr<Entity>>>(100,std::vector<std::shared_ptr<Entity>>(100));
}

Map::Map(int x , int y){
    entity2DArray = std::vector<std::vector<std::shared_ptr<Entity>>>(x,std::vector<std::shared_ptr<Entity>>(y));
}
Map::~Map()
{

}

void Map::print(const sf::RenderWindow& window)
{
    //window.draw()
}

Map::Map(std::vector<std::vector<std::shared_ptr<Entity>>> array2D)
{
    entity2DArray = std::move(array2D);
    width = entity2DArray.size();
    length = entity2DArray[0].size();
}

const std::vector<std::vector<std::shared_ptr<Entity>>> &Map::getEntity2DArray() const
{
    return entity2DArray;
}

void Map::setEntity2DArray(const std::vector<std::vector<std::shared_ptr<Entity>>> &entity2DArray)
{
    Map::entity2DArray = entity2DArray;
}

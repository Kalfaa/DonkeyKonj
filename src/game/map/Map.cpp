#include <utility>

//
// Created by user on 25/12/2018.
//

#include "Map.h"


Map::Map(){
    entity2DArray = std::vector<std::vector<std::shared_ptr<Entity>>>(100,std::vector<std::shared_ptr<Entity>>(100));
}

Map::Map(unsigned int x , unsigned int y){
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

void Map::addEntityToMatrix(std::shared_ptr<Entity> entity)
{
     sf::Sprite sprite = entity->sprite;
    int x = static_cast<int>(sprite.getPosition().x);
    int y = static_cast<int>(sprite.getPosition().y);
    int s_width = sprite.getTextureRect().width;
    int s_height =sprite.getTextureRect().height;

    for(int i = 0 ;i<s_width/32;i++){
        entity2DArray.at(static_cast<unsigned int>((x+32*i) / 32)).at(static_cast<unsigned int>(y / 32)) = entity;
        for(int j =0; j<s_height/32;j++){
            entity2DArray.at(static_cast<unsigned int>((x+32*i) / 32)).at(static_cast<unsigned int>((y*j*32) / 32)) = entity;
        }
    }

    entity2DArray.at(static_cast<unsigned int>( (x + s_width) / 32)).at(static_cast<unsigned int>(y / 32)) = entity;
    entity2DArray.at(static_cast<unsigned int>(x / 32)).at(static_cast<unsigned int>((y + s_height) / 32)) =entity;
    entity2DArray.at(static_cast<unsigned int>((x+s_width) / 32)).at(static_cast<unsigned int>((y + s_height) / 32)) =entity;
}

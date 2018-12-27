#include <utility>

//
// Created by user on 25/12/2018.
//

#include "Map.h"


Map::Map(){
    entity3DArray = Matrix3d(100, std::vector<std::vector<std::shared_ptr<Entity>>>(100));
}

Map::Map(unsigned int x , unsigned int y){
    //entity2DArray = std::vector<std::vector<std::shared_ptr<Entity>>>(x,std::vector<std::shared_ptr<Entity>>(y));
    entity3DArray = Matrix3d(x, std::vector<std::vector<std::shared_ptr<Entity>>>(y));
}
Map::~Map()
{

}

void Map::print(const sf::RenderWindow& window)
{
    //window.draw()
}

Map::Map(Matrix3d array3D)
{
    entity3DArray = std::move(array3D);
    width = entity3DArray.size();
    length = entity3DArray[0].size();
}

const Matrix3d& Map::getEntity3DArray()  const
{
    return entity3DArray;
}

void Map::setEntity3DArray(const Matrix3d& entity3DArray)
{
    Map::entity3DArray = entity3DArray;
}

void Map::addEntityToMatrix(std::shared_ptr<Entity> entity)
{
     sf::Sprite sprite = entity->sprite;
    int x = static_cast<int>(sprite.getPosition().x);
    int y = static_cast<int>(sprite.getPosition().y);
    int s_width = sprite.getTextureRect().width;
    int s_height =sprite.getTextureRect().height;

    for(int i = 0 ;i<s_width/32;i++){
        entity3DArray.at(static_cast<unsigned int>((x+32*i) / 32)).at(static_cast<unsigned int>(y / 32)).push_back(entity);
        for(int j =0; j<s_height/32;j++){
            entity3DArray.at(static_cast<unsigned int>((x+32*i) / 32)).at(static_cast<unsigned int>((y*j*32) / 32)).push_back(entity);
        }
    }
}

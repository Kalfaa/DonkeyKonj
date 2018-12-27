//
// Created by user on 25/12/2018.
//

#ifndef DONKEYKONG_MAP_H
#define DONKEYKONG_MAP_H

#include "pch.h"
#include "StaticEntity.h"

class Map
{
public:
    Map();
    Map(unsigned int x , unsigned int y);
    Map(std::vector<std::vector<std::shared_ptr<Entity>>> array2D);
    virtual ~Map();
    //std::array<std::array<Entity,255>,255> entity2DArray ;
    std::vector<std::vector<std::shared_ptr<Entity>>> entity2DArray;

    const std::vector<std::vector<std::shared_ptr<Entity>>> &getEntity2DArray() const;

    void setEntity2DArray(const std::vector<std::vector<std::shared_ptr<Entity>>>&entity2DArray);

    int width;
    int length;
public:
    void addEntityToMatrix(std::shared_ptr<Entity> entity);
    void print(const sf::RenderWindow&);


};


#endif //DONKEYKONG_MAP_H


//
// Created by user on 25/12/2018.
//

#ifndef DONKEYKONG_MAP_H
#define DONKEYKONG_MAP_H

#include "pch.h"
#include "StaticEntity.h"

typedef std::vector<std::vector<std::shared_ptr<Entity>>> Matrix2d;
typedef std::vector<Matrix2d> Matrix3d;

class Map
{
public:
    Map();
    Map(unsigned int x , unsigned int y);
    Map(Matrix3d array3D);
    Map(std::ifstream file);
    virtual ~Map();
    //std::array<std::array<Entity,255>,255> entity2DArray ;
    Matrix3d entity3DArray;

    const Matrix3d &getEntity3DArray() const;

    void setEntity3DArray(const Matrix3d& entity3DArray);

    int width;
    int length;
    sf::Vector2f startpoint;
public:
    void addEntityToMatrix(std::shared_ptr<Entity> entity);
    void print(const sf::RenderWindow&);
    void printElement();
    bool collide(sf::Sprite sprite,EntityType entityType,Direction direction);
};


#endif //DONKEYKONG_MAP_H


//
// Created by user on 25/12/2018.
//

#ifndef DONKEYKONG_MAP_H
#define DONKEYKONG_MAP_H

#include "pch.h"
#include "EntityManager.h"

#include "StaticEntity.h"

class Entity;

#define LADDER_COUNT 4
#define BLOCK_COUNT_X 20//8
#define BLOCK_COUNT_Y 5
#define BLOCK_SPACE 110.f
#define CASE_AREA 32
#define SCALE_SPRITES 2.5f

struct CollideRes
{
    CollideRes(bool collide, std::shared_ptr<Entity> entity);
    bool collide;
    std::shared_ptr<Entity> entity;
};

class Map
{
public:
    typedef std::vector<std::vector<std::shared_ptr<Entity>>> Matrix2d;
    typedef std::vector<Matrix2d> Matrix3d;

public:
    Map();

    Map(unsigned int x, unsigned int y);

    Map(Matrix3d array3D);

    Map(std::ifstream file);

    virtual ~Map();

    //std::array<std::array<Entity,255>,255> entity2DArray ;
    Matrix3d entity3DArray;

    const Matrix3d &getEntity3DArray() const;

    void setEntity3DArray(const Matrix3d &entity3DArray);

    void countElement();

    void addEntityToMatrix(std::shared_ptr<Entity>);

    void removeEntityToMatrix(const std::shared_ptr<Entity> &);
    void removeEntityToMatrix(Entity*);

    void print(const sf::RenderWindow &);
    void printElement();
    std::shared_ptr<CollideRes> collide(sf::Sprite sprite,EntityType entityType,Direction direction);
    std::shared_ptr<CollideRes> collide(sf::Sprite sprite,EntityType entityType,Direction direction,std::shared_ptr<Entity> entity);
    std::shared_ptr<CollideRes> collide(sf::Sprite sprite,EntityType entityType,Direction direction,sf::FloatRect rect);


public:
    int width;
    int length;
    sf::Vector2f startpoint;
};


#endif //DONKEYKONG_MAP_H


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
    virtual ~Map();

public:

    void print(const sf::RenderWindow&);


};


#endif //DONKEYKONG_MAP_H


#include <utility>
#include <Game.h>

//
// Created by user on 25/12/2018.
//

#include "Map.h"


Map::Map(){
    entity3DArray = Matrix3d(100, std::vector<std::vector<std::shared_ptr<Entity>>>(100));
}

Map::Map(unsigned int x , unsigned int y){
    entity3DArray = Matrix3d(y, std::vector<std::vector<std::shared_ptr<Entity>>>(x));
}
Map::~Map()
{

}
Map::Map(std::ifstream file)
{
    std::string str((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
    unsigned int x = str.find('\n');
    auto y = static_cast<unsigned int>(str.begin(),str.end(),'\n');
    entity3DArray = Matrix3d(x, std::vector<std::vector<std::shared_ptr<Entity>>>(y));
    std::vector<std::string> list_string;
    std::stringstream ss(str);
    std::string tmp;
    while(std::getline(ss, tmp, '\n'))
    {
        list_string.push_back(tmp);
    }

    for(auto it = list_string.begin(); it != list_string.end(); ++it)
    {
        std::cout << (*it) << std:: endl;
    }

    for(int i =0;i<x ;i++){
        for(int j = 0;j<y;j++){
            switch(list_string[i][j]){
                case 'O':
                    break;
                case 'P':
                    break;
                case 'L':
                    //CREER UNE LADDER ET LE PUSH DANS LA MATRICE 3D
                    break;
                case 'X':
                    startpoint.x=j;
                    startpoint.y=i;
                default:break;
            }
        }
    }

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
    //@todo REFACTOR CETTE ALGO PETER QUI CREER DES DUPPLICAT DOBJET DANS LA MATRICE
    for(int i = 0 ;i<=(s_width/CASE_AREA)+1; i++){
        auto mposx = static_cast<unsigned int>((x+CASE_AREA*i) / CASE_AREA);
        auto mposy = static_cast<unsigned int>(y / CASE_AREA);
        entity3DArray.at(mposy).at(mposx).push_back(entity);
        for(int j =0; j<=s_height/CASE_AREA+1;j++){
            mposy = static_cast<unsigned int>((y+j*CASE_AREA) / CASE_AREA);
            entity3DArray.at(mposy).at(mposx).push_back(entity);
        }
    }
}

void Map::printElement()
{
 for(int i =0 ;i<entity3DArray.size()-1;i++){
     for(int j = 0; j<entity3DArray[i].size()-1;j++){
         for(int k =0;k<entity3DArray[i][j].size();k++){
             std::shared_ptr<Entity> entity = entity3DArray[i][j].at(k);
             std::string type  ;
             if(entity->type ==LADDER){
                 type = "ladder";
             }else if(entity->type ==PLATFORM){
                 type = "platform";
             }
             printf("%s  en x : %d en y %d \n" ,type.c_str() ,j,i);
         }
     }
 }
}



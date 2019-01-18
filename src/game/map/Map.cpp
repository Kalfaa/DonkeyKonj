#include <utility>
#include <Game.h>

//
// Created by user on 25/12/2018.
//

#include "Map.h"


Map::Map()
{
    entity3DArray = Matrix3d(100, std::vector<std::vector<std::shared_ptr<Entity>>>(100));
}

Map::Map(unsigned int x, unsigned int y)
{
    entity3DArray = Matrix3d(y, std::vector<std::vector<std::shared_ptr<Entity>>>(x));
}

Map::~Map()
= default;

Map::Map(std::ifstream file)
{
    std::string str((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
    auto x = static_cast<unsigned int>(str.find('\n'));
    auto y = static_cast<unsigned int>(str.begin(), str.end(), '\n');
    entity3DArray = Matrix3d(x, std::vector<std::vector<std::shared_ptr<Entity>>>(y));
    std::vector<std::string> list_string;
    std::stringstream ss(str);
    std::string tmp;
    while (std::getline(ss, tmp, '\n'))
    {
        list_string.push_back(tmp);
    }

    for (const auto &it : list_string)
    {
        std::cout << it << std::endl;
    }

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            switch (list_string[i][j])
            {
                case 'O':
                    break;
                case 'P':
                    break;
                case 'L':
                    //CREER UNE LADDER ET LE PUSH DANS LA MATRICE 3D
                    break;
                case 'X':
                    startpoint.x = j;
                    startpoint.y = i;
                default:
                    break;
            }
        }
    }

}

//void Map::print(const sf::RenderWindow &window)
//{
//    //window.draw()
//}

Map::Map(Matrix3d array3D)
{
    entity3DArray = std::move(array3D);
    width = entity3DArray.size();
    length = entity3DArray[0].size();
}

const Map::Matrix3d &Map::getEntity3DArray() const
{
    return entity3DArray;
}

void Map::setEntity3DArray(const Matrix3d &entity3DArray)
{
    Map::entity3DArray = entity3DArray;
}

void Map::addEntityToMatrix(std::shared_ptr<Entity> entity)
{
    sf::Sprite sprite = entity->sprite;
    int x = static_cast<int>(sprite.getPosition().x);
    int y = static_cast<int>(sprite.getPosition().y);
    int s_width = sprite.getTextureRect().width;
    int s_height = sprite.getTextureRect().height;
    //@todo REFACTOR CETTE ALGO PETER QUI CREER DES DUPPLICAT DOBJET DANS LA MATRICE
    for (int i = 0; i <= (s_width / CASE_AREA) + 1; i++)
    {
        auto mposx = static_cast<unsigned int>((x + CASE_AREA * i) / CASE_AREA);
        auto mposy = static_cast<unsigned int>(y / CASE_AREA);
        entity3DArray.at(mposy).at(mposx).push_back(entity);
        for (int j = 0; j <= s_height / CASE_AREA + 1; j++)
        {
            mposy = static_cast<unsigned int>((y + j * CASE_AREA) / CASE_AREA);
            entity3DArray.at(mposy).at(mposx).push_back(entity);
        }
    }
}

void Map::removeEntityToMatrix(const std::shared_ptr<Entity> &entity)
{
    sf::Sprite sprite = entity->sprite;
    int x = static_cast<int>(sprite.getPosition().x);
    int y = static_cast<int>(sprite.getPosition().y);
    int s_width = sprite.getTextureRect().width;
    int s_height = sprite.getTextureRect().height;
    //@todo REFACTOR CETTE ALGO PETER QUI CREER DES DUPPLICAT DOBJET DANS LA MATRICE
    for (int i = 0; i <= (s_width / CASE_AREA) + 1; i++)
    {
        auto mposx = static_cast<unsigned int>((x + CASE_AREA * i) / CASE_AREA);
        auto mposy = static_cast<unsigned int>(y / CASE_AREA);
        std::vector<std::shared_ptr<Entity>> vec = entity3DArray.at(mposy).at(mposx);
        for(size_t cnt = 0; cnt < vec.size(); cnt++)
        {
            if(vec[cnt]->type == entity->type)
            {
                std::cout << "erase" << std::endl;
                vec.erase(vec.begin() + cnt);
            }
        }

        for (int j = 0; j <= s_height / CASE_AREA + 1; j++)
        {
            mposy = static_cast<unsigned int>((y + j * CASE_AREA) / CASE_AREA);
            vec = entity3DArray.at(mposy).at(mposx);
            for(size_t cnt = 0; cnt < vec.size(); cnt++)
            {
                if(vec[cnt]->type == entity->type)
                {
                    std::cout << "erase1" << std::endl;
                    vec.erase(vec.begin() + cnt);
                }
            }
        }
    }
}

void Map::printElement()
{
    for (int i = 0; i < entity3DArray.size() - 1; i++)
    {
        for (int j = 0; j < entity3DArray[i].size() - 1; j++)
        {
            for (int k = 0; k < entity3DArray[i][j].size(); k++)
            {
                std::shared_ptr<Entity> entity = entity3DArray[i][j].at(k);
                std::string type;
                if (entity->type == LADDER)
                {
                    type = "ladder";
                } else if (entity->type == PLATFORM)
                {
                    type = "platform";
                }
                printf("%s  en x : %d en y %d \n", type.c_str(), j, i);
            }
        }
    }
}

void Map::countElement()
{
    int countLadder = 0;
    int countPlatform = 0;
    int countBonus = 0;
    for (int i = 0; i < entity3DArray.size() - 1; i++)
    {
        for (int j = 0; j < entity3DArray[i].size() - 1; j++)
        {
            for (int k = 0; k < entity3DArray[i][j].size(); k++)
            {
                std::shared_ptr<Entity> entity = entity3DArray[i][j].at(k);
                std::string type;
                if (entity->type == LADDER)
                {
                    countLadder++;
                } else if (entity->type == PLATFORM)
                {
                    countPlatform++;
                }else if(entity->type == BONUS_ITEM){
                    countBonus++;
                }
            }
        }
    }
    printf("Nombre d'echelle : %d \n Nombre de Platforme %d \n Nombre de Bonus ITEM %d", countLadder, countPlatform, countBonus);
}


std::shared_ptr<CollideRes> Map::collide(sf::Sprite sprite, EntityType entityType, Direction direction)
{
    std::vector<std::shared_ptr<Entity>> list_entity;
    auto left = static_cast<unsigned int>(sprite.getPosition().x / CASE_AREA) ;
    auto right =  static_cast<unsigned int>((sprite.getPosition().x + sprite.getGlobalBounds().width ) / CASE_AREA );
    auto bottom = static_cast<unsigned int>((sprite.getPosition().y + sprite.getGlobalBounds().height) / CASE_AREA);
    auto top = static_cast<unsigned int>(sprite.getPosition().y / CASE_AREA);
    unsigned y1;
    unsigned x1;
    unsigned y2;
    unsigned x2;
    switch (direction)
    {
        case UP:
            y1 = top;
            x1 =left ;
            y2 =top ;
            x2 = right ;
            break;
        case DOWN:
            y1 = bottom;
            x1 = left ;
            y2 = bottom ;
            x2 = right ;
            break;
        case LEFT:
            y1 = top;
            x1 = left ;
            y2 = bottom ;
            x2 = left ;
            break;
        case RIGHT:
            y1 =top ;
            x1 = right ;
            y2 = bottom ;
            x2 = right ;
            break;
        default: ;
    }
    for (const auto &i : entity3DArray.at(y1).at(x1))
    {
        if(i->type == entityType)list_entity.push_back(i) ;
    }

    for (const auto &i : entity3DArray.at(y2).at(x2))
    {
        if (i->type == entityType)list_entity.push_back(i);
    }

    for (const auto &i : entity3DArray.at(y2-1).at(x2))
    {
        if (i->type == entityType)list_entity.push_back(i);
    }
    for(auto &entity : list_entity){
        if(entity->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())){
            return std::make_shared<CollideRes>(true, *entity);
        }
    }
    return std::make_shared<CollideRes>(false , Entity());
}

CollideRes::CollideRes(bool colide, Entity entity)
        : collide(colide), entity(entity)
{}
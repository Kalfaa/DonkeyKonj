// 
// Created by user on 26/12/2018.
//

#include "SpritesSheet.h"

using namespace std;

bool SpritesSheet::loadSprites(string file)
{
    std::map<std::string, std::array<int, 4>> map = loadSpriteSetting(file.substr(0, file.find_last_of('.') - 1));

    sf::Event event;
    sf::Texture mainTexture;

    mainTexture.loadFromFile(file);

    for(const auto& tab : map)
    {
        //sprites.insert(make_pair(tab.first, sf::Sprite(mainTexture, sf::IntRect(0,0,300,400))));
    }

    return true;
}

std::map<std::string, std::array<int, 4>> SpritesSheet::loadSpriteSetting(std::string file)
{
    ifstream flux(file);
    map<string, array<int, 4>> mapSettings;

    while(!flux.eof())
    {
        string spriteName;
        flux >> spriteName;
        array<int, 4> tab{};

        for_each(tab.begin(), tab.end(), [&flux](int &n){
            flux >> n;
        });
        mapSettings.insert(pair<string, array<int, 4>>(spriteName, tab));
    }
    return map<string, array<int, 4>>();
}
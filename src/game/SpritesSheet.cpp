// 
// Created by user on 26/12/2018.
//

#include "SpritesSheet.h"

using namespace std;

std::map<const std::string, sf::IntRect> SpritesSheet::sprites;
std::map<const std::string, std::vector<sf::IntRect>> SpritesSheet::spritesPaterns;

bool SpritesSheet::loadSprites(string file)
{
    std::map<std::string, std::array<int, 4>> map = loadSpriteSetting(file.substr(0, file.find_last_of('.') - 1));

    sf::Event event;
    sf::Texture mainTexture;

    mainTexture.loadFromFile(file);

    for(const auto &tab : map)
    {
        //sf::IntRect rect(tab.second[0], tab.second[1], tab.second[2], tab.second[3]);
        //sprites.insert(pair<const string, sf::IntRect&>(tab.first, rect));
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
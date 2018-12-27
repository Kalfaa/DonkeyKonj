// 
// Created by user on 26/12/2018.
//

#include "SpritesSheet.h"

using namespace std;

std::map<const std::string, sf::IntRect> SpritesSheet::sprites;
std::map<const std::string, std::vector<sf::IntRect>> SpritesSheet::spritesPatterns;

int SpritesSheet::lastNumSprite = -1;

bool SpritesSheet::loadSprites(string file)
{
    std::map<std::string, std::array<int, 4>> map = loadSpriteSetting(file.substr(0, file.find_last_of('.') - 1));

    sf::Texture mainTexture;
    mainTexture.loadFromFile(file);

    string lastSpriteName;
    for(const auto& tab : map)
    {
        sf::IntRect rect(tab.second[0], tab.second[1], tab.second[2], tab.second[3]);
        sprites.insert(make_pair(tab.first, rect));

        size_t pos = isPattern(tab.first, lastSpriteName);
        if(pos)
        {
            if(spritesPatterns.find(tab.first.substr(0, pos)) != spritesPatterns.end())
            {
                spritesPatterns.at(tab.first.substr(0, pos)).push_back(rect);
            }
            else
            {
                vector<sf::IntRect> vec;
                vec.push_back(rect);
                spritesPatterns.insert(make_pair(tab.first.substr(0, pos), vec));
            }
        }

        lastSpriteName = tab.first;
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

size_t SpritesSheet::isPattern(const string currentSprite, const string lastSprite)
{
    int numSprite = lastNumSprite + 1;

    // Test if sprite name end with lastNumSprite + 1
    size_t testEndWithNum = currentSprite.find_last_of(to_string(numSprite));
    if(testEndWithNum == string::npos)
    {
        lastNumSprite = -1;
        return 0;
    }

    // Test if sprite name is equal to the last sprite name (without last num) and if there is one last
    if(lastNumSprite > -1 && !lastSprite.empty())
    {
        string spriteNameWithoutNum = lastSprite.substr(0, lastSprite.find_last_of(to_string(numSprite - 1)));

        if(spriteNameWithoutNum != currentSprite.substr(0, testEndWithNum))
        {
            lastNumSprite = -1;
            return 0;
        }
    }

    lastNumSprite++;

    return testEndWithNum;
}

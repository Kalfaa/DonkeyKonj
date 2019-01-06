#include <utility>

//
// Created by user on 26/12/2018.
//

#include "SpritesSheet.h"

using namespace std;

sf::Image SpritesSheet::mainImage;

std::map<const std::string, sf::IntRect> SpritesSheet::posTexture;
std::map<const std::string, std::vector<sf::IntRect>> SpritesSheet::posTexturePatterns;

//int SpritesSheet::lastNumTex = -1;

ostream &operator<<(ostream &os, const sf::IntRect &sheet)
{
    return os << "rect{" << sheet.top << ", " << sheet.left << ", " << sheet.height << ", " << sheet.width << "}";
}

ostream &operator<<(ostream &os, const SpritesSheet &sheet)
{
    os << "# SpriteSheet #" << endl;
    for(const auto& ite : SpritesSheet::posTexture)
    {
        os << "Sprite name: " << ite.first << " with " << ite.second << endl;
    }

    for(const auto& ite : SpritesSheet::posTexturePatterns)
    {
        os << "Pattern \"" << ite.first << "\"" << endl << "{" << endl;
        for(const auto& iteV : ite.second)
        {
            os << "\t" << iteV << "," << endl;
        }
        os << "}" << endl;
    }

    return os;
}

bool SpritesSheet::loadSprites(string file)
{
    std::map<std::string, std::array<int, 4>> map = loadSpriteSetting(file.substr(0, file.find_last_of('.')));
    mainImage.loadFromFile(file);

    string lastSpriteName;
    for(const auto& tab : map)
    {
        sf::IntRect rect(tab.second[0], tab.second[1], tab.second[2], tab.second[3]);
        posTexture.insert(make_pair(tab.first, rect));

        size_t pos = isPattern(tab.first, lastSpriteName);
        if(pos)
        {
            if(posTexturePatterns.find(tab.first.substr(0, pos)) != posTexturePatterns.end())
            {
                posTexturePatterns.at(tab.first.substr(0, pos)).push_back(rect);
            }
            else
            {
                vector<sf::IntRect> vec;
                vec.push_back(rect);
                posTexturePatterns.insert(make_pair(tab.first.substr(0, pos), vec));
            }
        }

        lastSpriteName = tab.first;
    }

    return true;
}

std::map<std::string, std::array<int, 4>> SpritesSheet::loadSpriteSetting(std::string file)
{
    ifstream flux(file);
    if(!flux) assert(false);
    map<string, array<int, 4>> mapSettings;

    while(!flux.eof())
    {
        string spriteName;
        flux >> spriteName;
        // flux.eof() doesn't work... :(
        if(spriteName.empty()) break;

        array<int, 4> tab{};
        for_each(tab.begin(), tab.end(), [&flux](int &n){
            flux >> n;
        });

        mapSettings.insert(pair<string, array<int, 4>>(spriteName, tab));
    }

    return mapSettings;
}

size_t SpritesSheet::isPattern(const string currentSprite, const string lastSprite)
{
    int numSprite = lastNumTex + 1;

    // Test if sprite name end with lastNumTex + 1
    size_t testEndWithNum = currentSprite.find_last_of(to_string(numSprite));
    if(testEndWithNum == string::npos)
    {
        lastNumTex = -1;
        if(currentSprite.at(currentSprite.size() - 1) != '0') return 0;
        else testEndWithNum = currentSprite.find_last_of(to_string(0));
    }

    // Test if sprite name is equal to the last sprite name (without last num) and if there is one last
    if(lastNumTex > -1 && !lastSprite.empty())
    {
        string spriteNameWithoutNum = lastSprite.substr(0, lastSprite.find_last_of(to_string(numSprite - 1)));
        if(spriteNameWithoutNum != currentSprite.substr(0, testEndWithNum))
        {
            lastNumTex = -1;
            return 0;
        }
    }

    lastNumTex++;
    return testEndWithNum;
}

sf::Texture SpritesSheet::getTexture(const std::string& name)
{
    sf::Texture texture;
    texture.loadFromImage(mainImage, posTexture.at(name));
    return texture;
}

/*sf::Texture SpritesSheet::getOppositeTexture(const string &name)
{
    sf::Texture tx = getTexture(name);
    tx.scale(-1.f,1.f);
    return tx;
}*/

std::vector<sf::Texture> SpritesSheet::getPattern(const std::string& name)
{
    vector<sf::IntRect> patternPos = posTexturePatterns.at(name);
    vector<sf::Texture> patternTx;

    for(const auto& ite : patternPos)
    {
        sf::Texture texture;
        texture.loadFromImage(mainImage, posTexture.at(name));
        patternTx.emplace_back(texture);
    }

    return patternTx;
}

/*std::vector<sf::Texture> SpritesSheet::getOppositePattern(const std::string& name)
{
    std::vector<sf::Sprite> vecSp = getPattern(std::move(name));
    for(auto& ite : vecSp)
    {
        ite.scale(-1.f,1.f);
    }

    return vecSp;
}*/


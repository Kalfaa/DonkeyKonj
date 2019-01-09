#include <utility>

//
// Created by user on 26/12/2018.
//

#include "SpritesSheet.h"

using namespace std;

SpritesSheet SpritesSheet::INSTANCE = SpritesSheet();
sf::Image SpritesSheet::mainImage;

std::map<const std::string, sf::IntRect> SpritesSheet::posSprites;
std::map<const std::string, std::vector<sf::IntRect>> SpritesSheet::posPatterns;

int SpritesSheet::lastNumTex = -1;

ostream &operator<<(ostream &os, const sf::IntRect &sheet)
{
    return os << "rect{" << sheet.top << ", " << sheet.left << ", " << sheet.height << ", " << sheet.width << "}";
}

ostream &operator<<(ostream &os, const SpritesSheet &sheet)
{
    os << "# SpriteSheet #" << endl;
    for(const auto& ite : SpritesSheet::posSprites)
    {
        os << "Sprite name: " << ite.first << " with " << ite.second << endl;
    }

    for(const auto& ite : SpritesSheet::posPatterns)
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
        posSprites.insert(make_pair(tab.first, rect));

        size_t pos = isPattern(tab.first, lastSpriteName);
        if(pos)
        {
            if(posPatterns.find(tab.first.substr(0, pos)) != posPatterns.end())
            {
                posPatterns.at(tab.first.substr(0, pos)).push_back(rect);
            }
            else
            {
                vector<sf::IntRect> vec;
                vec.push_back(rect);
                posPatterns.insert(make_pair(tab.first.substr(0, pos), vec));
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

sf::Sprite SpritesSheet::getSprite(const std::string &name)
{
    //shared_ptr<sf::Texture> texture = make_shared<sf::Texture>();
    auto* texture = new sf::Texture();
    texture->loadFromImage(mainImage, posSprites.at(name));

    sf::Sprite sp;
    sp.setTexture(*texture, true);
    sp.scale(3.0f, 3.0f);

    return sp;
}

/*sf::Sprite SpritesSheet::getOppositeSprite(const string &name)
{
    sf::Texture tx = getSprite(name);
    tx.scale(-1.f,1.f);
    return tx;
}*/

/*std::vector<sf::Sprite> SpritesSheet::getPattern(const std::string& name)
{
    vector<sf::IntRect> patternPos = posPatterns.at(name);
    vector<sf::Texture> patternTx;

    for(const auto& ite : patternPos)
    {
        sf::Texture texture;
        texture.loadFromImage(mainImage, posSprites.at(name));
        patternTx.emplace_back(texture);
    }

    return patternTx;
}*/

/*std::vector<sf::Sprite> SpritesSheet::getOppositePattern(const std::string& name)
{
    std::vector<sf::Sprite> vecSp = getPattern(std::move(name));
    for(auto& ite : vecSp)
    {
        ite.scale(-1.f,1.f);
    }

    return vecSp;
}*/


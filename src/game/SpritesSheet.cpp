#include <utility>

#include <utility>

//
// Created by user on 26/12/2018.
//

#include "SpritesSheet.h"

using namespace std;


SpritesSheet SpritesSheet::INSTANCE = SpritesSheet();


ostream &operator<<(ostream &os, const sf::IntRect &sheet)
{
    return os << "rect{" << sheet.top << ", " << sheet.left << ", " << sheet.height << ", " << sheet.width << "}";
}

ostream &operator<<(ostream &os, const SpritesSheet &sheet)
{
    os << "# SpriteSheet #" << endl;
    for(const auto& ite : sheet.posSprites)
    {
        os << "Sprite name: " << ite.first << " with " << ite.second << endl;
    }

    for(const auto& ite : sheet.posPatterns)
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

bool SpritesSheet::loadSprites(std::string file, float extendRatio)
{
    this->loadSprites(file);
    this->extendRatio = extendRatio;
    return false;
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

        int lastNumSp = -1;
        size_t pos = isPattern(tab.first, lastSpriteName, lastNumSp);

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

size_t SpritesSheet::isPattern(const string currentSprite, const string lastSprite, int& lastNumSp)
{
    int numSprite = lastNumSp + 1;

    // Test if sprite name end with lastNumSp + 1
    size_t testEndWithNum = currentSprite.find_last_of(to_string(numSprite));
    if(testEndWithNum == string::npos)
    {
        lastNumSp = -1;
        if(currentSprite.at(currentSprite.size() - 1) != '0') return 0;
        else testEndWithNum = currentSprite.find_last_of(to_string(0));
    }

    // Test if sprite name is equal to the last sprite name (without last num) and if there is one last
    if(lastNumSp > -1 && !lastSprite.empty())
    {
        string spriteNameWithoutNum = lastSprite.substr(0, lastSprite.find_last_of(to_string(numSprite - 1)));
        if(spriteNameWithoutNum != currentSprite.substr(0, testEndWithNum))
        {
            lastNumSp = -1;
            return 0;
        }
    }

    lastNumSp++;
    return testEndWithNum;
}

sf::Sprite SpritesSheet::getSprite(const std::string &name)
{
//    unique_ptr<sf::Texture> texture = make_unique<sf::Texture>();
//    texture->loadFromImage(mainImage, posSprites.at(name));
//
//    shared_ptr<sf::Sprite> sp = make_shared<sf::Sprite>();
//    sp->setTexture(*texture, true);
//
//    if(extendRatio > 0.f) sp->scale(extendRatio, extendRatio);

    //shared_ptr<sf::Texture> texture = make_shared<sf::Texture>();
    auto* texture = new sf::Texture();
    texture->loadFromImage(mainImage, posSprites.at(name));

    sf::Sprite sp;
    sp.setTexture(*texture, true);

    if(extendRatio > 0.f) sp.scale(extendRatio, extendRatio);

    return sp;
}

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

/*sf::Sprite SpritesSheet::getOppositeSprite(const string &name)
{
    sf::Texture tx = getSprite(name);
    tx.scale(-1.f,1.f);
    return tx;
}*/


#include <utility>

#include <utility>

//
// Created by user on 26/12/2018.
//

#include "SpritesSheet.h"

using namespace std;

std::shared_ptr<sf::Texture> SpriteLoader::getTexture(const sf::Image& spriteSheet)
{
    return texture;
}

SpriteLoader::SpriteLoader(const sf::Image& spriteSheet, const sf::IntRect &pos)
{
    texture = make_shared<sf::Texture>();
    texture->loadFromImage(spriteSheet, pos);
}

SpriteLoader::~SpriteLoader()
= default;

SpritesSheet SpritesSheet::INSTANCE = SpritesSheet();

ostream &operator<<(ostream &os, const sf::IntRect &sheet)
{
    return os << "rect{" << sheet.top << ", " << sheet.left << ", " << sheet.height << ", " << sheet.width << "}";
}

//ostream &operator<<(ostream &os, const SpritesSheet &sheet)
//{
//    os << "# SpriteSheet #" << endl;
//    for(const auto& ite : sheet.posSprites)
//    {
//        os << "Sprite name: " << ite.first << " with " << ite.second << endl;
//    }
//
//    for(const auto& ite : sheet.posPatterns)
//    {
//        os << "Pattern \"" << ite.first << "\"" << endl << "{" << endl;
//        for(const auto& iteV : ite.second)
//        {
//            os << "\t" << iteV << "," << endl;
//        }
//        os << "}" << endl;
//    }
//
//    return os;
//}

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
    int lastNumSp = -1;
    for(auto tab : map)
    {
        sf::IntRect rect(tab.second[0], tab.second[1], tab.second[2], tab.second[3]);
        //unique_ptr<SpriteLoader> spl =
        posSprites[tab.first] = make_shared<SpriteLoader>(mainImage, rect);
        //posSprites.insert(make_pair(tab.first, spl));

        size_t pos = isPattern(tab.first, lastSpriteName, lastNumSp);

        if(pos)
        {
            if(posPatterns.find(tab.first.substr(0, pos)) != posPatterns.end())
            {
                posPatterns.at(tab.first.substr(0, pos)).push_back(make_shared<SpriteLoader>(mainImage, rect));
                cout << "vectPush " << tab.first << endl;
            }
            else
            {
                vector<std::shared_ptr<SpriteLoader>> vec;
                vec.push_back(make_shared<SpriteLoader>(mainImage, rect));
                posPatterns.insert(make_pair(tab.first.substr(0, pos), vec));
                cout << "Init vectPush " << tab.first << " with name : " << tab.first.substr(0, pos) << endl;
            }
        }

        lastSpriteName = tab.first;
    }

    return true;
}

std::map<std::string, std::array<int, 4>> SpritesSheet::loadSpriteSetting(std::string file)
{
    ifstream flux(file);
    if(!flux)
    {
        cerr << "Error when opening " << file << endl;
        assert(false);
    }
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
    sf::Sprite sp(*(posSprites.at(name)->getTexture(mainImage)));
    //sp.setTexture(*(posSprites.at(name)->getTexture(mainImage)), true);

    if(extendRatio > 0.f) sp.scale(extendRatio, extendRatio);

    return sp;
}

sf::Sprite SpritesSheet::getOppositeSprite(const string &name)
{
    sf::Sprite sp = getSprite(name);
    sp.scale(-1.f,1.f);
    sp.setPosition(0.f, 0.f);
    return sp;
}

std::vector<sf::Sprite> SpritesSheet::getPattern(const std::string& name)
{
    vector<std::shared_ptr<SpriteLoader>> patternPos = posPatterns.at(name);
    vector<sf::Sprite> patternSp;

    for(const auto& ite : patternPos)
    {
        sf::Sprite sp = sf::Sprite(*(ite->getTexture(mainImage)));
        if(extendRatio > 0.f) sp.scale(extendRatio, extendRatio);

        patternSp.emplace_back(sp);
    }

    return patternSp;
}

std::vector<sf::Sprite> SpritesSheet::getOppositePattern(const std::string& name)
{
    std::vector<sf::Sprite> vecSp = getPattern(name);
    for(auto& ite : vecSp)
    {
        ite.setTextureRect(sf::IntRect(ite.getTextureRect().width, 0, -ite.getTextureRect().width, ite.getTextureRect().height));
    }
    return vecSp;
}

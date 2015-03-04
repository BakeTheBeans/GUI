#ifndef UTILITY_H
#define UTILITY_H

#include <memory>
#include <string>
#include <map>
//#include <utility>
#include "CMarkup/Markup.h"
#include <vector>

#include "define.h"

#define RED sf::Color::Red
#define BLUE sf::Color::Blue


#if(DEBUG)
#include <cctype>
#include <string>
#include <iostream>
#endif

#if(DEBUG)
#include <SFML/Graphics/Font.hpp>


#endif
namespace sf
{
class Texture;
class Font;
}



namespace GUI
{


#if(TEXTURE_2)
enum ComponentType
{
    none,
    normalButton,
    radioButton,
    buttonIcons
    ,FileButtonPressed,
    FileButtonReleased



};
#endif


struct ResourceNode
{
    //Might want to add component type like button, menu, cursor etc;
    bool isLoaded;
    std::string filename;
    std::string description;
    std::unique_ptr<sf::Texture> texture;

public:
    ResourceNode();

};

typedef ResourceNode * ResourcePtr;



class xmlParser
{
public:
    std::string key;

private:
    CMarkup xml;
    const char * filename;
    //std::stringstream ss;
    //std::ctring current;

    bool EnterElement()
    {
        bool foo =  xml.IntoElem();
        return foo;
    }

    bool ExitElement()
    {
        return xml.OutOfElem();
    }

    bool FindElement(const char * Tag)
    {
        bool foo= xml.FindElem(Tag);
        return foo;
    }

private:
    xmlParser() {}
public:
    xmlParser(const char * _filename) : key(), filename(_filename) {}
    void OpenDocument();
    void Enter(const char * node);
    ResourceNode * getNext();

};

class ResourceManager
{
public:
    typedef std::string Tag;
    static const char * ResourceFileName;
    static const char * ResourcePath;
private:
    static std::map<Tag,ResourcePtr> ResourceMap;
    ResourceManager() {}
public:
    static void RegisterResources();
    static sf::Texture * getTexture(const char * name);
    static void DisposeTexture(const char * name);
};


struct internal
{

    static std::map<std::string,ResourcePtr> CreateResourceMap()
    {
        std::map<std::string,ResourcePtr> Map;
        return Map;
    }
};


#if(TEXTURE_2)
//Texture Manager needs to be fixed. If Component types share the
//the texture the texture map does not ensure a single copy of texture
//The whole point of using unique pointer is lost. Don't have time to
//fix this right now.
class TextureManager
{

    static const char * ImagePath;

public:

    typedef std::unique_ptr<sf::Texture>  TexturePtr;

private:

    TextureManager() {}

protected:
    static std::map<ComponentType,TexturePtr> _textureMap;


    static std::string ImageFilePath(const char * fileName);


public:
    static void RegisterGuiComponent(ComponentType _btype, const char * fileName);

    static sf::Texture * getTexture(ComponentType _btype);

};



struct internal
{

static std::map<ComponentType,TextureManager::TexturePtr> CreateMap()
{    

    std::map<ComponentType,TextureManager::TexturePtr> Map;
    return Map;
}

};

#endif

#if(TEXTURE_1)

class TextureManager
{
    static const char * ImagePath;
    typedef std::unique_ptr<sf::Texture>  TexturePtr;

private:
    TextureManager(const TextureManager & obj) {}
    TextureManager & operator=(const TextureManager & obj) {return *this;}

    TextureManager() {}
protected:
    std::map<ComponentType,TexturePtr> _textureMap;
    sf::Sprite _button;

    std::string ImageFilePath(const char * fileName);

public:
    static TextureManager & getTextureManager()
    {
        static TextureManager _manager;
        return _manager;
    }

    void RegisterGuiComponent(ComponentType _btype, const char * fileName);

    sf::Texture & getTexture(ComponentType _btype);

};

#endif


EON
#endif // UTILITY_H

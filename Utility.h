#ifndef UTILITY_H
#define UTILITY_H
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include "CMarkup/Markup.h"
#include <vector>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "define.h"


namespace sf
{
class Texture;
class Font;
}


namespace GUI {

namespace internal {

enum GUI_Type
{
    Button,
    Menu

};

EON
EON



namespace GUI
{
//template<typename T> struct GUITrait;


struct XmlNode
{
    //Might want to add component type like button, menu, cursor etc;
    std::string name;
    std::string filename;
    std::string description;
    void Reset()
    {
        name.clear();
        filename.clear();
        description.clear();
    }
    void Print()
    {
    std::cout << name << "   " << filename << "   " << description << std::endl;
    }
};



struct IResource
{

    bool isLoaded;
    std::string filename;
    std::string description;
    virtual ~IResource() {}
    void Print()
    {
        std::cout << "isLoaded :" << isLoaded  << "    filename :" << filename << "    description :" << description << std::endl;

    }
};


struct Texture : public IResource
{
    typedef sf::Texture* ReturnType;
    typedef sf::Texture StorageType;
    std::unique_ptr<sf::Texture> res;
public:
    ReturnType getResource() { return res.get();}
    void Store(StorageType * p) { res.reset(p); }
};

struct Font : public IResource
{
    typedef sf::Font* ReturnType;
    typedef sf::Font StorageType;
    std::unique_ptr<sf::Font> res;
public:
    ReturnType getResource() { return res.get(); }
    void Store(StorageType * p) { res.reset(p); }
};


typedef IResource * ResourcePtr;
class xmlParser;

class ResourceManager
{
public:
    typedef std::string Tag;
    static const char * ResourceFileName;
    static const char * ResourcePath;
private:
    static std::map<Tag,ResourcePtr> ResourceMap;


    ResourceManager() {}
    template<typename T>
    static ResourcePtr getNext(const XmlNode & node)
    {
        std::string file;
        ResourcePtr p = new T();
        p->isLoaded = false;
        file.append(ResourcePath).append("/").append(node.filename);
        p->filename = file;
        p->description = node.description;

        return p;
    }

    static void Register(xmlParser & ResourceDoc, std::string MainNode);
public:
    static void RegisterResources();
    //static void DisposeTexture(const char * name);

    template<typename T>
    static typename T::ReturnType getResource(const char * name)
    {
        auto it = ResourceMap.find(name);
        if ( it == ResourceMap.end() ){
            std::string exp;
            exp.append("No resource with name ").append(name).append(" is registered. Check the resource file");
            throw exp.c_str();
        }

        //ResourcePtr foo = it->second;
        T* foo = static_cast<T*>(it->second);
        if ( foo->isLoaded )
        {
            return foo->getResource();
        }
        else
        {

            typedef typename T::StorageType S;
            S * resource = new S();
            resource->loadFromFile(foo->filename);
            foo->Store(resource);
            //res.reset(resource);
            foo->isLoaded = true;
            return resource;
        }

    }

    static void Print()
    {

        for(auto it= ResourceMap.begin(); it != ResourceMap.end(); it++)
        {
            std::cout << it->first;
            it->second->Print();
        }
    }

    static void Dispose();


};



class xmlParser
{
public:
    //std::string key;


private:
    CMarkup xml;
    const char * filename;
    XmlNode node;

    bool EnterElement()
    {        
        bool foo =  xml.IntoElem();
        return foo;
    }


    bool FindElement(const char * Tag)
    {
        bool foo= xml.FindElem(Tag);
        return foo;
    }

public:
    bool ExitElement()
    {
        return xml.OutOfElem();
    }

private:
    xmlParser() {}
public:
    xmlParser(const char * _filename) : xml(), filename(_filename), node() {}
    void OpenDocument();
    void Enter(const char * node);
    bool Next();
    XmlNode & getXmlNode() { return node; }

};


//struct internal
namespace internal
{

    static std::map<std::string,ResourcePtr> CreateResourceMap()
    {
        std::map<std::string,ResourcePtr> Map;
        return Map;
    }



};

namespace internal {

enum TextAlignment
{
    None = 0,
    Left = 1,
    Center = 2,
    Right = 3
};

}



EON
#endif // UTILITY_H

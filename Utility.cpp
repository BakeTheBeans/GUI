#include "Utility.h"
#include "define.h"
//#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include<utility>
namespace GUI
{


std::map<ResourceManager::Tag,ResourcePtr> ResourceManager::ResourceMap = internal::CreateResourceMap();
const char *  ResourceManager::ResourceFileName = "Resource.xml";
const char * ResourceManager::ResourcePath = "/home/rohit/Projects/Draw/Resources";

ResourceNode :: ResourceNode() : isLoaded(false), filename(), description(), texture(nullptr) {}

/*
 * Enter main node like Button
 */
void xmlParser :: Enter(const char * node)
{
    bool exists = FindElement(node) ? EnterElement() : false;
    if ( !exists )
    {
        std::string mess;
        throw mess.append("Could not find Resource node ").append(node).append("in the xml file ").c_str();

    }

}


void xmlParser :: OpenDocument()
{
    if ( filename == 0 ) throw " No resource filename provided";
    if ( !xml.Load(filename) ) throw "Could not find resource file";
    FindElement(0);
    EnterElement();
    //if (xml.GetData().compare("Resources") != 0 )throw "Did you change the resorces file. The head node should be \"Resources\" ";
}


/*
 * Returns pointer to 0 if nothing exists.
 * Use this only for main objects like buttons etc.
 * Access name  using key.
 */
ResourceNode * xmlParser :: getNext()
{
    key.clear();
    ResourceNode * node = 0;
    bool exists = FindElement("Node") ? EnterElement() : false;

    if ( exists && FindElement("Name") )
    {                
        std::string file;
        file.append(ResourceManager::ResourcePath).append("/");
        key = xml.GetData().c_str();
        node = new ResourceNode();
        if ( FindElement("FileName") ) node->filename = file.append(xml.GetData().c_str());
        if ( FindElement("Description")) node->description = xml.GetData().c_str();

        ExitElement();
    }
    return node;

}

void ResourceManager :: RegisterResources()
{
    std::string file;
    file.append(ResourcePath).append("/").append(ResourceFileName);
    xmlParser ResourceDoc(file.c_str());
    ResourceDoc.OpenDocument();
    auto Load = [&] (const char * Component)->void
    {
        ResourceDoc.Enter(Component);
        ResourcePtr p;
        while( (p = ResourceDoc.getNext() ) )
        {
            ResourceMap.insert(  std::make_pair(std::string(ResourceDoc.key), p) );
        }
    };

    Load("Button");
}


sf::Texture * ResourceManager :: getTexture(const char * name)
{
     auto it = ResourceMap.find(name);
     if ( it == ResourceMap.end() ){
         std::string exp;
         exp.append("No rsource with name ").append(name).append(" is registered. Check the resource file");
         throw exp.c_str();
     }

     ResourcePtr foo = it->second;
     if ( foo->isLoaded ) return foo->texture.get();
     else
     {
         sf::Texture * bar = new sf::Texture();
         bar->loadFromFile(foo->filename);
         foo->texture.reset(bar);
         foo->isLoaded = true;
         return bar;
     }
}


void ResourceManager ::  DisposeTexture(const char * name)
{
    auto it = ResourceMap.find(name);
    if ( it->second != 0 )
    {
        ResourcePtr foo = it->second;
        foo->texture.release();
        foo->texture.reset(0);
        foo->isLoaded = false;
    }
}

//#endif


#if(TEXTURE_2)
const char * TextureManager::ImagePath = "/home/rohit/Projects/Draw/Texture/";


std::map<ComponentType,TextureManager::TexturePtr> TextureManager::_textureMap = internal::CreateMap();


void TextureManager :: RegisterGuiComponent(ComponentType _btype,const char * fileName)
{
    if ( _textureMap.find(_btype) == _textureMap.end() )
    {
        sf::Texture * p = new sf::Texture();
        p->loadFromFile(ImageFilePath(fileName));
        _textureMap.insert(std::make_pair(_btype,TexturePtr(p)));
        p = nullptr;
    }

}


sf::Texture * TextureManager :: getTexture(ComponentType _btype)
{
    std::map<ComponentType,TexturePtr> :: iterator texIt;
    if ( (texIt = _textureMap.find(_btype) ) == _textureMap.end() ) throw "Button not registered. First register and then load";

    //return *(texIt->second);
    return (texIt->second).get();
}


std::string TextureManager :: ImageFilePath(const char * fileName)
{
    if ( !fileName ) throw "No filename provided to load image from";
    std::string path(ImagePath);
    path.append(fileName);
    return path;
}


#endif


//***********************OLD****************************************
#if(TEXTURE_1)
void TextureManager :: RegisterGuiComponent(ComponentType _btype,const char * fileName)
{
    if ( _textureMap.find(_btype) == _textureMap.end() )
    {
        sf::Texture * p = new sf::Texture();
        p->loadFromFile(ImageFilePath(fileName));
        _textureMap.insert(std::make_pair(_btype,TexturePtr(p)));
        p = nullptr;
    }

}


sf::Texture & TextureManager :: getTexture(ComponentType _btype)
{
    std::map<ComponentType,TexturePtr> :: iterator texIt;
    if ( (texIt = _textureMap.find(_btype) ) == _textureMap.end() ) throw "Button not registered. First register and then load";

    return *(texIt->second);
}

std::string TextureManager :: ImageFilePath(const char * fileName)
{
    if ( !fileName ) throw "No filename provided to load image from";
    std::string path(ImagePath);
    path.append(fileName);
    return path;
}
#endif

EON

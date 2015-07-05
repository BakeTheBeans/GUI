#include "Utility.h"
#include "define.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <utility>
namespace GUI
{



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

    if ( !xml.Load(filename) ) throw "Could not find resource file or the XML file is Illformed";
    FindElement(0);
    EnterElement();
    //if (xml.GetData().compare("Resources") != 0 )throw "Did you change the resorces file. The head node should be \"Resources\" ";
}


/*
 * Use this only for main objects like Texture etc.
 * Access name  using key.
 */
bool xmlParser :: Next()
{

    node.Reset();
    //bool exists = FindElement("Node") ? EnterElement() : false;
    //bool exists = FindElement("Node");
/*
    if ( exists && FindElement("Name") )
    {
        std::string file;

        node.name = xml.GetData();
        if ( FindElement("FileName") ) node.filename = xml.GetData();
        if ( FindElement("Description")) node.description = xml.GetData();
        ExitElement();
        return true;
    }
*/
    if ( FindElement("Node") )
    {
        node.name = xml.GetAttrib("Name");
        node.filename = xml.GetAttrib("FileName");
        node.description = xml.GetAttrib("Description");
        //std::cout << xml.GetTagName() << std::endl;
        //std::cout << xml.GetAttribName(0) << " " << xml.GetAttribName(1) << "  " << xml.GetAttribName(2) << std::endl;
        //std::cout << "FOUND " << std::endl;

        std::cout << xml.GetAttrib("Name") << "   " << xml.GetAttrib("FileName") << xml.GetAttrib("Description") << std::endl;
        //ExitElement();
        return true;
    }

    else return false;

}


const char * ResourceManager::ResourcePath = "/home/rohit/Projects/Draw/Resources";
const char *  ResourceManager::ResourceFileName = "Resources.xml";
std::map<ResourceManager::Tag,ResourcePtr> ResourceManager::ResourceMap = internal::CreateResourceMap();


void ResourceManager :: Register(xmlParser & ResourceXmlDoc, std::string MainNode)
{
    ResourceXmlDoc.Enter(MainNode.c_str());
    ResourcePtr p = 0;

    while( ResourceXmlDoc.Next() )
    {
        if ( MainNode.compare("Texture") == 0 )
        {
            p = ResourceManager::getNext<Texture>(ResourceXmlDoc.getXmlNode());
        }
        else if ( MainNode.compare("Font") == 0 )
        {
            p = ResourceManager::getNext<Font>(ResourceXmlDoc.getXmlNode());
        }
        else throw "Unrecognizable Main Node";
        std::string key = ResourceXmlDoc.getXmlNode().name;
        ResourceMap.insert(std::make_pair( key, p));

    }


}

void ResourceManager :: RegisterResources()
{
    std::string file;
    file.append(ResourcePath).append("/").append(ResourceFileName);
    xmlParser ResourceXmlDoc(file.c_str());
    ResourceXmlDoc.OpenDocument();
/*
    typedef ResourcePtr (* ResourceManager::FuncPtr)();
    FuncPtr CallBack =
    {
        &ResourceManager::getResource<Texture>,
        &ResourceManager::getResource<Font>
    };

*/

    Register(ResourceXmlDoc,std::string("Texture"));
    ResourceXmlDoc.ExitElement();
    Register(ResourceXmlDoc,std::string("Font"));
}

void ResourceManager :: Dispose()
{
    for(auto it = ResourceMap.begin(); it != ResourceMap.end(); it++)
        delete it->second;
}


EON

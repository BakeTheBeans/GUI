#ifndef COMPLEXOBJECT_H
#define COMPLEXOBJECT_H
#include <map>
#include <string>
#include <memory>
#include <utility>
//#include "CMarkup/Markup.h"
#include "GuiAttributeBuilder.h"
//class CMarkup;
#include "interfaces.h"

namespace GUI  {

namespace internal {

/*
template<typename T, bool U = IsDerivedFromEnclosingBox<T>::value >
class ConfigurableObject<T>
{
    void operator()(T & obj)
    {
        obj.Configure();
    }
};

template<typename T>
class ConfigurableObject<T,false>
{
    void operator()(T & obj) {}
};
*/



struct INode
{
    virtual ~INode() {}
    virtual void Build(CMarkup & xml) {}
    virtual const std::pair<float,float> & getOffsetPosition() {}
    virtual void setPosition(float posX, float posY) {}
};


template<typename T>
class Node : public INode
{
    T & obj;
    std::pair<float,float> offset_position;
    Node() {}
public:
    Node(T & _obj) : obj(_obj) {}
    void Build(CMarkup & xml)
    {
        offset_position = internal::AttributeBuilder::Build<T>(xml,obj);
  //      ConfigurableObject<T>()(obj);
    }

    void setPosition(float posX, float posY)
    {
        obj.setPosition(posX, posY);
    }

    virtual const std::pair<float,float> & getOffsetPosition() { return offset_position; }

};



class ComplexObject : public EnclosingBox
{
std::string xmlNodeName;
//typedef std::unique_ptr<INode> NodePtr;
typedef INode * NodePtr;
typedef std::string XmlString;
std::map<XmlString, NodePtr> ObjectMap;


protected:
virtual void ConfigureSubElements() = 0;

virtual std::string getXmlTagName() = 0;

template<typename T>
void Register(const char * _xmlTag, T & obj)
{

    auto it = ObjectMap.find(std::string(_xmlTag));
    if ( it != ObjectMap.end() ) throw "Cannot register objects with same name";
    else
    {
        //ObjectMap[xmlAttributename] = std::unique_ptr<INode>(new Node<T>(obj));
        ObjectMap[std::string(_xmlTag)] = new Node<T>(obj);
    }

}


public:
ComplexObject() : xmlNodeName(), ObjectMap() {}


void SetPosition()
{

    sf::Vector2f pos = getInternalPosition();

    for(std::map<XmlString, NodePtr>::value_type & obj : ObjectMap )
    {
        if ( obj.first == "EnclosingBox" ) continue;

        else
        {
            auto & offset = obj.second->getOffsetPosition();
            obj.second->setPosition( pos.x + offset.first, pos.y + offset.second );
        }

    }
}


void SetUpDisplay() {}

void SetUpFromXml()
{

    CMarkup xml;
    if ( !xml.Load("Gui.xml")) throw "Could not find Gui.xml";
    if(!xml.IsWellFormed()) throw "Xml file is ill formed";

    if (xml.FindElem("Object") ) xml.IntoElem();

    //if ( xml.FindElem( getXmlTagName().c_str() ) ? ( xml.GetAttrib("Type") == "Open" ) : false ) xml.IntoElem();

    if ( xml.FindElem( getXmlTagName().c_str() ) ) xml.IntoElem();

    else throw "Unrecognized format for loading directory Menu";

    //for(std::pair<std::string,NodePtr> & node : ObjectMap)

    for(std::map<XmlString, NodePtr>::value_type & node : ObjectMap)
    {
        std::cout << node.first << std::endl;
        if ( xml.FindElem(node.first) )
        {
            node.second->Build(xml);
            xml.ResetMainPos();
        }
    }

    ConfigureSubElements();

}

};




}//EON

}//EON
#endif // COMPLEXOBJECT_H

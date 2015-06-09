#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H
#include <map>
#include <string>
#include <memory>
#include <vector>
#include "drawableshapes.h"

namespace Draw {


class ShapeFactory
{

    friend class boost::serialization::access;

    typedef std::unique_ptr<IDrawableShapes> ShapePtr;
    typedef std::pair<std::string, ShapePtr> TagObjectPair;
    std::map<std::string, ShapePtr> objectMap;
    std::vector<TagObjectPair> shapeColl;
private:
    ShapeFactory() : objectMap(), shapeColl() {}
    ShapeFactory(const ShapeFactory & obj);
    ShapeFactory & operator=(const ShapeFactory & obj);

private:
    static ShapeFactory factory;


    template<typename T>
    IDrawableShapes * CreateShape()
    {
        return new T();
    }

public:
    static ShapeFactory & getShapeFactory()
    {
        static ShapeFactory obj;
        return obj;
    }


     template<typename T>
    void RegisterShape()
    {
        std::string tag = T::getSerializationTag();
        auto it = objectMap.find(tag);
        if ( it == objectMap.end() )
        {
            //objectMap[tag] = &ShapeFactory::CreateShape<T>;
            objectMap[tag] = ShapePtr(new T());
        }
    }

    template<typename T>
    IDrawableShapes * CreateInstance()
    {
        std::string tag = T::getSerializationTag();
        auto it = objectMap.find(tag);
        if ( it == objectMap.end() ) return 0;
        else
        {
            //IDrawableShapes * p = (*it.second)();
            IDrawableShapes * p  = it->second->clone();
            shapeColl.push_back(std::move(ShapePtr(p)));
            return p;
        }
    }

    IDrawableShapes * CreateInstance(std::string serializationTag)
    {

        auto it = objectMap.find(tag);
        if ( it == objectMap.end() ) return 0;
        else
        {
            //IDrawableShapes * p = (*it.second)();
            IDrawableShapes * p  = it->second->clone();
            shapeColl.push_back(std::make_pair(tag,td::move(ShapePtr(p))));
            return p;
        }
    }

/*
    void Save(std::string filename)
    {
        for(ShapePtr p : shapeColl)
        {
            p->Serialize(filename);
        }
    }


    IDrawableShapes * Load(std::string filename)
    {
       //IDrawableShapes * CreateInstance(filename);
       //p->Deserialize();
       //return p;

    }
*/

    void serialize(boost::archive::text_oarchive & ar, const unsigned int version)
    {
        for( TagObjectPair obj : shapeColl)
        {
            ar << obj.first;
            ar << *(obj.second);
        }

    }

    void serialize(boost::archive::text_oarchive & ar, const unsigned int version)

};


}//EON
#endif // SHAPEFACTORY_H

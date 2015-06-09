#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H
#include <map>
#include <string>
#include <memory>
#include <vector>
#include "drawableshapes.h"
#include <fstream>
#include <boost/serialization/string.hpp>
#include <boost/serialization/utility.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/serialization/vector.hpp>

namespace Draw {

class ShapeRegisteration
{

public:
    template<typename Archive>
    static void RegisterShapes(Archive & ar)
    {
        ar.template register_type<Line>();
        ar.template register_type<Triangle>();
        ar.template register_type<Quad>();
        ar.template register_type<BlockTriangle>();
        ar.template register_type<BlockQuad>();
        ar.template register_type<EquilateralTriangle>();
        ar.template register_type<Rhombus>();
        ar.template register_type<Pentagon>();
        ar.template register_type<Hexagon>();
        ar.template register_type<Octagon>();
        ar.template register_type<Circle>();
        ar.template register_type<BlockEquilateralTriangle>();
        ar.template register_type<BlockRhombus>();
        ar.template register_type<BlockPentagon>();
        ar.template register_type<BlockHexagon>();
        ar.template register_type<BlockOctagon>();
        ar.template register_type<BlockCircle>();
    }

};


class ShapeFactory
{

    friend class boost::serialization::access;

    //typedef std::unique_ptr<IDrawableShapes> ShapePtr;
    typedef IDrawableShapes * ShapePtr;
    typedef std::pair<std::string, ShapePtr> TagObjectPair;


    std::map<std::string, ShapePtr> objectMap;
    std::vector<ShapePtr> shapeColl;


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
    IDrawableShapes * CreateShapeInstance()
    {
            IDrawableShapes * p = new T();
            return p;
    }

    void Save(std::string filename)
    {
        std::ofstream file(filename.c_str());
        boost::archive::text_oarchive oarch(file);
        oarch.register_type<Triangle>();
        oarch.register_type<Pentagon>();
        oarch << shapeColl;

    }


    IDrawableShapes * Load(std::string filename)
    {

        std::ifstream file(filename.c_str());
        boost::archive::text_iarchive iarch(file);

        iarch.register_type<Triangle>();
        iarch.register_type<Pentagon>();
        iarch >> shapeColl;
        std::cout << "Size of SapeColl : " << shapeColl.size();
        return shapeColl[0];

    }


    void serialize(boost::archive::text_oarchive & ar, const unsigned int version)
    {
/*
        for( TagObjectPair & obj : shapeColl )
        {
            ar << obj.first;
            ar << *(obj.second.get());
        }
*/
        for(IDrawableShapes *p : shapeColl ) ar << *p;
        //ar << shapeColl;
    }

    /*
    void serialize(boost::archive::text_iarchive & ar, const unsigned int version)
    {
        std::string tag;
        while(true)
        {
            TagObjectPair obj;
            std::string tag ="";
            ar >> tag;
            if ( tag.empty() ) break;
            obj.first = tag;

            auto it = objectMap.find(obj.first);            
            if ( it == objectMap.end() ) throw "Unrecognized Serialization Tag";
            IDrawableShapes * p = CreateInstance(obj.first);
            //ar >> *p;
            ar >> obj.second;

            
        }
        
    }
    */

};


}//EON
#endif // SHAPEFACTORY_H

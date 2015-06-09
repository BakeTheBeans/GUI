#ifndef SERIALIZESHAPE_H
#define SERIALIZESHAPE_H
#include <vector>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>
#include "define.h"

class SerializeShape
{
public:
    SerializeShape();
};

#endif // SERIALIZESHAPE_H


struct VertexArraySkeleton
{
    friend class boost::serialization::access;    
    float posX;
    float posY;
    //int color;
    std::string color;
    void serialize(boost::archive::text_oarchive & ar, const unsigned int version)
    {

        ar << posX;
        ar << posY;
        ar << color;
    }

    void serialize(boost::archive::text_iarchive & ar, const unsigned int version)
    {
        ar >> posX;
        ar >> posY;
        ar >> color;
    }

};


struct VertexShapeSkeleton
{
    friend class boost::serialization::access;

    //int color;
    std::string color;
    std::vector<VertexArraySkeleton> shape;
    int numOfVertices;

    void serialize(boost::archive::text_oarchive & ar, const unsigned int version)
    {        
        DEBUG_MESSAGE
        ar << color;
        ar << shape;
        ar << numOfVertices;
        std::cout << "Number of vertices  :  "<< numOfVertices << std::endl;
    }

    void serialize(boost::archive::text_iarchive & ar, const unsigned int version)
    {
        ar  >> color;
        ar >> shape;
        ar >> numOfVertices;
        std::cout << " Vertex Array size: " << shape.size() << std::endl;
        std::cout << " number of verices : " << numOfVertices << std::endl;
    }
};



#ifndef SERIALIZESHAPE_H
#define SERIALIZESHAPE_H
#include <vector>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>

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
    int color;
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

    int color;
    std::vector<VertexArraySkeleton> shape;
    int numOfVertices;

    void serialize(boost::archive::text_oarchive & ar, const unsigned int version)
    {        
        ar << color;
        ar << shape;
        ar << numOfVertices;
    }

    void serialize(boost::archive::text_iarchive & ar, const unsigned int version)
    {
        ar  >> color;
        ar >> shape;
        ar >> numOfVertices;
    }
};



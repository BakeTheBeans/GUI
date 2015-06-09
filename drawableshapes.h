#ifndef DRAWABLESHAPES_H
#define DRAWABLESHAPES_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <utility>
#include <vector>
#include "define.h"
//#include "shapefactory.h"
#include <sstream>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>

namespace sf {
    class Window;
    class Event;
}

/*
 * drag
 * extrude
 * line projections
 * save
 * change color
 * select edge - hightlight edges
 * rotate
 *
 */




namespace Draw {

class IDrawableShapes : public sf::Drawable
{

    friend class boost::serialization::access;
protected:
    static const sf::Color DefaultColor;

private:
    bool _select;    

protected:
    //Initial Mouse position when an object is selected
    sf::Vector2i mousePos;
    bool stopped;

public:
    IDrawableShapes() : sf::Drawable(), _select(false), mousePos(), stopped(false) {}
    virtual ~IDrawableShapes() {}

    //virtual IDrawableShapes * clone()=0;
    virtual void select();
    void deselect() { _select = false; }
    bool isSelected() const { return _select; }


    virtual bool StartDraw(const sf::Window & window){}
    virtual bool isMouseInside() { return false;}
    virtual void scale(float xscale, float yscale) {}
    virtual void BringToFocus(const sf::Window & window) {}
    virtual void drag() {}
    virtual const sf::Color & getFillColor() {}
    virtual void setColor(const sf::Color & color) {}
    virtual void rotate() {}
    virtual void rotateByAngle(float angleInDegrees) {}

    void serialize(boost::archive::text_iarchive & ar, const unsigned int version) {}
    void serialize(boost::archive::text_oarchive & ar, const unsigned int version) {}

    virtual void MoveShapeUp(int step)=0;
    virtual void MoveShapeDown(int step)=0;
    virtual void MoveShapeRight(int step)=0;
    virtual void MoveShapeLeft(int step)=0;

    virtual sf::Vector2f getCentroid() { throw "get Centroid not Implemented"; }

    virtual std::pair<sf::Vector2f, sf::Vector2f>  getBounds()=0;
    virtual void StopDraw() {}
    //virtual void Serialize(std::string filename)=0;
    //virtual void DeSerialize(std::string filename)=0;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const=0;
};

typedef IDrawableShapes BS;


class VertexShapes : public IDrawableShapes
{

    friend class boost::serialization::access;

protected:
    sf::Color color;
    sf::VertexArray shape;
    int numOfVertices;
private:
    sf::VertexArray dashedlines;
    std::vector<sf::Vector2f> broken;
    bool edgeSelected;
    int selectEdgeIndex;
private:
    std::vector<sf::Vector2f> & densify(sf::Vector2f & pos1, sf::Vector2f & pos2);
    bool drawDashedLines();
protected:
    /*
     * Order of pos1 and po2 is important. Theta is calculted as  the angle between the
     * line joining pos2 to pos1 with pos1 as the pivot point. This is crucial while
     * determining the quadrant.
     */
    float CalculateTheta(const sf::Vector2f & pos1,const sf::Vector2f & pos2);
    void ResetVertices();

public:
    VertexShapes(int _numOfVertices ) : IDrawableShapes(), color(BS::DefaultColor), shape(), numOfVertices(_numOfVertices), dashedlines(), broken(), edgeSelected(false), selectEdgeIndex(-1)
    {  
        dashedlines = sf::VertexArray(sf::LinesStrip);
    }
    virtual ~VertexShapes() {}

    void select();
    virtual bool isMouseInside();
    virtual void scale(float xscale, float yscale);
    virtual void BringToFocus(const sf::Window & window);
    virtual void drag();
    virtual void rotate();
    virtual void rotateByAngle(float angleInDegrees);
    const sf::Color & getFillColor();
    void setColor(const sf::Color & _color);

    virtual bool highlightEdge(sf::Window & window);
    virtual void selectEdge();
    void setEdgeColor(const sf::Color & color);
    const sf::Color & getEdgeColor() const;
    bool isAnyEdgeSelected() const { return edgeSelected; }
    void deselectEdge();

    void MoveShapeUp(int step);
    void MoveShapeDown(int step);
    void MoveShapeRight(int step);
    void MoveShapeLeft(int step);

    sf::Vector2f getCentroid();
    std::pair<sf::Vector2f, sf::Vector2f>  getBounds();

    //void Serialize(std::string filename);
    //void DeSerialize(std::string filename);
    void serialize(boost::archive::text_iarchive & ar, const unsigned int version);
    void serialize(boost::archive::text_oarchive & ar, const unsigned int version);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


class ContinuousLine : public VertexShapes
{
public:
    ContinuousLine();    
    virtual bool StartDraw(const sf::Window & window);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    //virtual IDrawableShapes * clone() { return new ContinuousLine(*this); }
    static std::string getSerializationTag();
};




class BaseShape : public VertexShapes
{
friend class boost::serialization::access;
protected:
    int clicks;
public:

    BaseShape(int _numofVertices);
    virtual ~BaseShape() {}
    void StopDraw();

    virtual bool StartDraw(const sf::Window & window);
    void serialize(boost::archive::text_iarchive & ar, const unsigned int version)
    {
         ar >> boost::serialization::base_object<VertexShapes>(*this);
    }

    void serialize(boost::archive::text_oarchive & ar, const unsigned int version)
    {        
         ar << boost::serialization::base_object<VertexShapes>(*this);
    }
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};


class Rectangle : public BaseShape
{

    static const int NUMBER_OF_VERTICES = 4;
    std::pair<sf::Vector2i,sf::Vector2i> pos;


public:
   Rectangle() : BaseShape(4)
   {

   }

   bool StartDraw(const sf::Window & window);   
   void StopDraw();
   static std::string getSerializationTag();

   void serialize(boost::archive::text_iarchive & ar, const unsigned int version)
   {
        ar >> boost::serialization::base_object<BaseShape>(*this);
   }

   void serialize(boost::archive::text_oarchive & ar, const unsigned int version)
   {
        ar << boost::serialization::base_object<BaseShape>(*this);
   }

};



template<int N>
class Polygon : public BaseShape
{
friend class boost::serialization::access;

public:    
    Polygon() : BaseShape(N) {}
    //virtual IDrawableShapes * clone() { return new Polygon<N>(*this); }
    ~Polygon() {}

   static std::string getSerializationTag();
   void serialize(boost::archive::text_iarchive & ar, const unsigned int version)
   {
       ar >> boost::serialization::base_object<BaseShape>(*this);

   }

   void serialize(boost::archive::text_oarchive & ar, const unsigned int version)
   {
       DEBUG_MESSAGE
       std::cout << "Number of vertices  :  "<< numOfVertices << std::endl;
        ar << boost::serialization::base_object<BaseShape>(*this);
   }

};


class RegularShape : public VertexShapes
{

private:
    std::pair<sf::Vector2i,sf::Vector2i> pos;
    int clicks;

public:
   RegularShape(int _numOfVertices);
   virtual ~RegularShape() {}
   bool StartDraw(const sf::Window & window);

   void StopDraw();
   void serialize(boost::archive::text_iarchive & ar, const unsigned int version)
   {
        ar >> boost::serialization::base_object<VertexShapes>(*this);
   }

   void serialize(boost::archive::text_oarchive & ar, const unsigned int version)
   {
        ar << boost::serialization::base_object<VertexShapes>(*this);
   }

   void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

template<int N>
class RegularPolygon : public RegularShape
{
protected:
    int getNumberOfVertices() { return N; }
public:
   RegularPolygon() : RegularShape(N) {}
   //virtual IDrawableShapes * clone() { return new RegularPolygon<N>(*this); }
   static std::string getSerializationTag();

   void serialize(boost::archive::text_iarchive & ar, const unsigned int version)
   {
        ar >> boost::serialization::base_object<RegularShape>(*this);
   }

   void serialize(boost::archive::text_oarchive & ar, const unsigned int version)
   {
        ar << boost::serialization::base_object<RegularShape>(*this);
   }


};



class BlockRectangle : public Rectangle
{
public:   
    BlockRectangle()
    {
        shape  = sf::VertexArray(sf::TrianglesFan, 5 );
        for(int i = 0; i < 5; i++) shape[i].color = BS::DefaultColor;
    }
    //virtual IDrawableShapes * clone() { return new BlockRectangle(*this); }
    static std::string getSerializationTag();



};


template<int N>
class RegularBlockPolygon : public RegularShape
{
public:    
    RegularBlockPolygon() : RegularShape(N)
    {
        shape  = sf::VertexArray(sf::TrianglesFan, N+1 );
        for(int i = 0; i < N + 1; i++) shape[i].color = BS::DefaultColor;
    }

    //virtual IDrawableShapes * clone() { return new RegularBlockPolygon<N>(*this); }
    static std::string getSerializationTag();

    void serialize(boost::archive::text_iarchive & ar, const unsigned int version)
    {
         ar >> boost::serialization::base_object<RegularShape>(*this);
    }

    void serialize(boost::archive::text_oarchive & ar, const unsigned int version)
    {
         ar << boost::serialization::base_object<RegularShape>(*this);
    }

};


template<int N>
class BlockPolygon : public BaseShape
{

public:    
    BlockPolygon() : BaseShape(N)
    {
        shape = sf::VertexArray(sf::TrianglesFan, N + 1 );
        for(int i = 0; i < N + 1; i++) shape[i].color = BS::DefaultColor;
    }

    //virtual IDrawableShapes * clone() { return new BlockPolygon<N>(*this); }
    static std::string getSerializationTag();

    void serialize(boost::archive::text_iarchive & ar, const unsigned int version)
    {
         ar >> boost::serialization::base_object<BaseShape>(*this);
    }

    void serialize(boost::archive::text_oarchive & ar, const unsigned int version)
    {
         ar << boost::serialization::base_object<BaseShape>(*this);
    }

};


using Line = Polygon<2>;
using Triangle = Polygon<3>;
using Quad = Polygon<4>;

using BlockTriangle = BlockPolygon<3>;
using BlockQuad = BlockPolygon<4>;

using EquilateralTriangle = RegularPolygon<3>;
using Rhombus =  RegularPolygon<4>;
using Pentagon = RegularPolygon<5>;
using Hexagon = RegularPolygon<6>;
using Octagon = RegularPolygon<8>;
using Circle = RegularPolygon<100>;

using BlockEquilateralTriangle = RegularBlockPolygon<3>;
using BlockRhombus =  RegularBlockPolygon<4>;
using BlockPentagon = RegularBlockPolygon<5>;
using BlockHexagon = RegularBlockPolygon<6>;
using BlockOctagon = RegularBlockPolygon<8>;
using BlockCircle = RegularBlockPolygon<100>;


}//EON



#endif // DRAWABLESHAPES_H

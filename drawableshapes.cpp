#include "drawableshapes.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "define.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include "serializeshape.h"
#include <fstream>
#include <limits>

#define PI 3.14159265358979323846

#define ANGLE(arg) arg*180/PI

namespace  Draw {



const sf::Color IDrawableShapes :: DefaultColor = sf::Color ::Blue;

void IDrawableShapes ::  select()
{
    mousePos = sf::Mouse::getPosition();
    _select = true;
}


void VertexShapes :: scale(float xscale, float yscale)
{

    for( int i = 0; i < numOfVertices + 1; i++ )
    {
        shape[i].position.x *= xscale;
        shape[i].position.y *= yscale;
    }

}


float VertexShapes :: CalculateTheta(const sf::Vector2f & pos1, const sf::Vector2f & pos2)
{
    float slope = (pos2.y - pos1.y)/(pos2.x - pos1.x);
    float theta = atan(-slope);

    if ( (pos2.x >= pos1.x) && (pos1.y >= pos2.y) )
    {
        theta = theta;
    }

    //Second Quadrnt
    else if ( (pos2.x < pos1.x) && (pos1.y >= pos2.y) )
    {
        theta = theta  + PI;
    }

    //Third Quadrnt
    else if ( (pos2.x < pos1.x) && (pos1.y < pos2.y) )
    {
        theta = std::abs(theta) + PI;
    }

    //Fourth Quadrnt
    else
    {
        theta = theta + 2*PI;
    }

    return theta;

}


void VertexShapes :: BringToFocus(const sf::Window & window)
{
    auto sz = window.getSize();
    auto pos = shape[0].position;

    for( int i = 0; i < numOfVertices + 1; i++ )
    {
        shape[i].position.x -= (pos.x - sz.x/3);
        shape[i].position.y -= (pos.y - sz.y/3);
    }
}


bool VertexShapes :: isMouseInside()
{
    sf::Vector2i mPos = sf::Mouse::getPosition();
    return shape.getBounds().contains(mPos.x, mPos.y);
}


std::vector<sf::Vector2f> & VertexShapes :: densify(sf::Vector2f & pos1, sf::Vector2f & pos2)
{

    float R = pow( ( pow( (pos1.y - pos2.y),2 ) + pow( (pos1.x - pos2.x),2 ) ), 0.5 );
    //std::cout << " Line Length : " << R << std::endl;

    float theta = CalculateTheta( pos1,pos2 );
    //std::cout << "Theta : " << ANGLE(theta) << std::endl;

    broken.clear();
    float r = 0;

    while( r < R )
    {
        broken.push_back(sf::Vector2f( r*cos(theta) + pos1.x, -r*sin(theta) + pos1.y ));
        r += 10;
    }

    //std::cout << pos1.x << "  " << pos2.x << "  " << pos1.y << "  " << pos2.y << std::endl;
/*
    for( auto it = broken.begin(); it != broken.end(); it++)
    {
        std::cout << it->x << "   " << it->y << std::endl;
    }

*/
    return broken;
}



bool VertexShapes :: drawDashedLines()
{

    if ( shape.getVertexCount() < 1) return false;
    dashedlines.clear();
    bool col = false;
    for(int i = 0; i < shape.getVertexCount() - 1; i++)
    {
        for(sf::Vector2f & pos : densify( shape[i].position, shape[i+1].position ) )
        {
            if( col ) dashedlines.append(sf::Vertex(pos, sf::Color::White));
            else dashedlines.append(sf::Vertex(pos, sf::Color::Black));
            col = !col;
        }

    }

    //std::cout << "size of dashed Lines " << dashedlines.getVertexCount() << std::endl;

}



void VertexShapes :: select()
{
    if ( edgeSelected ) return;
    this->IDrawableShapes::select();
    drawDashedLines();
    mousePos = sf::Mouse::getPosition();
}


void VertexShapes :: drag()
{

    if ( isSelected() )
    {
       auto curPos =  sf::Mouse::getPosition();
       int offX = curPos.x - mousePos.x;
       int offY = curPos.y - mousePos.y;
       mousePos = curPos;

       for(int i = 0; i< numOfVertices + 1; i++)
       {
           shape[i].position.x += offX;
           shape[i].position.y += offY;
       }

       for(int i = 0 ; i < dashedlines.getVertexCount(); i++)
       {
           dashedlines[i].position.x += offX;
           dashedlines[i].position.y += offY;
       }

    }

}


const sf::Color & VertexShapes :: getFillColor()
{
    //if ( shape.getVertexCount() > 0 ) return shape[0].color;
    return color;
}

void VertexShapes :: setColor(const sf::Color & _color)
{
    color = _color;
    for(int i = 0; i < shape.getVertexCount(); i++ ) shape[i].color = color;
}

void VertexShapes :: rotate()
{
    sf::Vector2f centroid;

    for(int i = 0; i< numOfVertices; i++ )
    {
        centroid.x += shape[i].position.x;
        centroid.y += shape[i].position.y;
    }

    centroid.x = centroid.x/numOfVertices;
    centroid.y = centroid.y/numOfVertices;
    float oldTheta = CalculateTheta(centroid, sf::Vector2f(mousePos.x,mousePos.y) );
    mousePos = sf::Mouse::getPosition();
    float newTheta = CalculateTheta(centroid, sf::Vector2f(mousePos.x,mousePos.y) );
    float delta = newTheta - oldTheta;

    for(int i = 0; i< numOfVertices; i++)
    {

        auto & vertex = shape[i].position;
        float R = pow( (pow( ( centroid.x - vertex.x ),2 ) + pow( ( centroid.y - vertex.y ),2 ) ),0.5 );
        float theta = CalculateTheta( centroid, shape[i].position );
        float angle = theta + delta > 2*PI ? (theta + delta - 2*PI ) : theta + delta;
        vertex.x = centroid.x + R*cos(angle);
        vertex.y = centroid.y - R*sin(angle);
    }

    shape[numOfVertices].position = shape[0].position;

}

void VertexShapes :: rotateByAngle(float angleInDegrees)
{
    sf::Vector2f centroid;
    for(int i = 0; i< numOfVertices; i++ )
    {
        centroid.x += shape[i].position.x;
        centroid.y += shape[i].position.y;
    }

    centroid.x = centroid.x/numOfVertices;
    centroid.y = centroid.y/numOfVertices;

    float delta = angleInDegrees*PI/180;
    std::cout << "Delta : " << delta << std::endl;


    for(int i = 0; i< numOfVertices; i++)
    {

        auto & vertex = shape[i].position;
        float R = pow( (pow( ( centroid.x - vertex.x ),2 ) + pow( ( centroid.y - vertex.y ),2 ) ),0.5 );
        float theta = CalculateTheta( centroid, shape[i].position );
        float angle = (theta + delta) > 2*PI ? (theta + delta - 2*PI ) : theta + delta;
        vertex.x = centroid.x + R*cos(angle );
        vertex.y = centroid.y - R*sin(angle);
    }


    shape[numOfVertices].position = shape[0].position;

    std::cout << "After : " << shape[numOfVertices].position.x << "  " << shape[numOfVertices].position.y << std::endl;

}

bool VertexShapes :: highlightEdge(sf::Window & window)
{
    if ( edgeSelected ) return true;
    selectEdgeIndex = -1;
    float tolerance = 10;
    for(int i = 0; i < numOfVertices; i++)
    {
        sf::Vector2f & ver1 = shape[i].position;
        sf::Vector2f & ver2 = shape[i+1].position;
        float slope = (ver2.y - ver1.y)/(ver2.x - ver1.x);
        float c = ver1.y - slope*ver1.x;
        auto mPos = sf::Mouse::getPosition(window);
        if ( std::abs(mPos.y - slope*mPos.x - c) < tolerance  )
        {
            dashedlines.clear();
            bool col = true;
            for( sf::Vector2f pos : densify(ver1,ver2 ) )
            {
                if ( col )dashedlines.append(sf::Vertex(pos,sf::Color::White));
                else dashedlines.append(sf::Vertex(pos,sf::Color::Black));
                col = !col;
            }

            selectEdgeIndex = i;
            return true;
        }
    }

    return false;
}

void VertexShapes :: selectEdge()
{
    if ( selectEdgeIndex >= 0 )
    {
        if ( isSelected() ) deselect();
        edgeSelected = true;
    }
}

void VertexShapes :: deselectEdge()
{
    selectEdgeIndex = -1;
    edgeSelected = false;
    //dashedlines.clear();
}

void VertexShapes :: setEdgeColor(const sf::Color & color)
{
    if( edgeSelected )
    {
        shape[selectEdgeIndex].color = color;
        shape[selectEdgeIndex + 1].color = color;
    }
}

const sf::Color & VertexShapes :: getEdgeColor() const
{
    return shape[selectEdgeIndex].color;
}

void VertexShapes :: MoveShapeUp(int step)
{
   for(int i = 0; i < shape.getVertexCount(); i++)
   {
       shape[i].position.y -= step;
   }

}

void VertexShapes :: MoveShapeDown(int step)
{
   for(int i = 0; i < shape.getVertexCount(); i++)
   {
       shape[i].position.y += step;
   }

}

void VertexShapes :: MoveShapeRight(int step)
{
    for(int i = 0; i < shape.getVertexCount(); i++)
    {
        shape[i].position.x += step;
    }
}

void VertexShapes :: MoveShapeLeft(int step)
{
    for(int i = 0; i < shape.getVertexCount(); i++)
    {
        shape[i].position.x -= step;
    }

}

sf::Vector2f VertexShapes :: getCentroid()
{
    float Xcen = 0,Ycen = 0;
    int n = shape.getVertexCount() - 1;
    int Vertices =  ( (shape[0].position.x == shape[n].position.x) && (shape[0].position.y == shape[n].position.y) ) ? n : n + 1;


    for(int i = 0; i < Vertices; i++)
    {
        Xcen += shape[i].position.x;
        Ycen += shape[i].position.y;
    }

    return sf::Vector2f(Xcen/Vertices, Ycen/Vertices );
}


void VertexShapes :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{
     if ( isSelected() ) target.draw(dashedlines);
    if ( selectEdgeIndex >=0  ) target.draw(dashedlines);
}



void VertexShapes :: serialize(boost::archive::text_oarchive & ar, const unsigned int version)
{
    ar << boost::serialization::base_object<IDrawableShapes>(*this);

    VertexShapeSkeleton obj;

    auto ColorConverter = [&](sf::Color & color, std::string & colorCode)
    {
        std::stringstream ss;
        ss << int(color.r) << ":" << int(color.g) << ":"<< int(color.b) << ":" << int(color.a);
        colorCode = ss.str();
    };

    ColorConverter(color,obj.color);

    for(int i = 0; i < numOfVertices + 1; i++)
    {
        sf::Vertex & ver = shape[i];
        VertexArraySkeleton va;
        ColorConverter( ver.color, va.color );
        va.posX = ver.position.x;
        va.posY = ver.position.y;
        obj.shape.push_back(va);
    }

    obj.numOfVertices = numOfVertices;
    ar << obj;

}


void VertexShapes :: serialize(boost::archive::text_iarchive & ar, const unsigned int version)
{
    ar >> boost::serialization::base_object<IDrawableShapes>(*this);
    VertexShapeSkeleton obj;
    ar >> obj;

    auto ColorConverter = [] (sf::Color & color, std::string & colorCode)
    {
      std::string temp;
      std::stringstream ss(colorCode);
      int rgba[4],i=0;

      while( std::getline(ss,temp,':') )
      {
          std::stringstream foo(temp);
          foo >> rgba[i++];
      }

      color.r = static_cast<sf::Uint8>(rgba[0]);
      color.g = static_cast<sf::Uint8>(rgba[1]);
      color.b = static_cast<sf::Uint8>(rgba[2]);
      color.a = static_cast<sf::Uint8>(rgba[3]);
    };

    ColorConverter(color, obj.color);    
    numOfVertices = obj.numOfVertices;

    for(int i = 0; i < numOfVertices + 1; i++)
    {
        shape[i].position.x = obj.shape[i].posX;
        shape[i].position.y = obj.shape[i].posY;
        ColorConverter(shape[i].color, obj.shape[i].color);
    }

}

inline void VertexShapes :: ResetVertices()
{
    for( int i = 0 ; i < numOfVertices + 1; i++ ) shape[i].position = sf::Vector2f(0,0);
}



std::pair<sf::Vector2f, sf::Vector2f> VertexShapes :: getBounds()
{
    std::pair<sf::Vector2f, sf::Vector2f> bound;
    bound.first = sf::Vector2f(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    bound.second = sf::Vector2f(std::numeric_limits<float>::min(), std::numeric_limits<float>::min() );

    for( int i = 0 ; i < numOfVertices + 1; i++ )
    {
        bound.first.x = std::min( bound.first.x, shape[i].position.x );
        bound.first.y = std::min( bound.first.y, shape[i].position.y );
        bound.second.x = std::max( bound.second.x, shape[i].position.x );
        bound.second.y = std::max( bound.second.y, shape[i].position.y );
    }

    return bound;
}

ContinuousLine :: ContinuousLine() : VertexShapes(0)
{
    shape = sf::VertexArray(sf::LinesStrip,0);
}

bool ContinuousLine :: StartDraw(const sf::Window & window)
{

    sf::Vector2i pos = sf::Mouse::getPosition(window);

    if ( shape.getVertexCount() == numOfVertices )
    {
        shape.append(sf::Vertex(sf::Vector2f(pos.x,pos.y), color) );
    }
    else
    {
        shape[numOfVertices].position.x = pos.x;
        shape[numOfVertices].position.y = pos.y;
    }

    if( sf::Mouse::isButtonPressed(sf::Mouse::Left)  )
    {
        numOfVertices++;
    }

    if ( sf::Mouse::isButtonPressed(sf::Mouse::Right) )
    {
        shape.resize(numOfVertices);
        return true;
    }
    else return false;

}


void ContinuousLine :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(!stopped)
    {
        target.draw(shape);
        this->VertexShapes::draw(target, states);
    }
}


BaseShape :: BaseShape(int _numOfVertices) : VertexShapes(_numOfVertices), clicks(0)
{
    shape = sf::VertexArray(sf::LinesStrip,numOfVertices+1);
    for(int i = 0; i< numOfVertices + 1; i++) shape[i].color = color;
}


bool BaseShape :: StartDraw(const sf::Window & window)
{

    stopped = false;
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    shape[clicks].position.x = pos.x;
    shape[clicks].position.y = pos.y;

    if ( clicks == 1 )
    {
        shape[numOfVertices].position = shape[0].position;

    }

    if( sf::Mouse::isButtonPressed(sf::Mouse::Left)  )
    {
        clicks++;
    }


    if( clicks == numOfVertices )
    {
        return true;
    }
    else return false;

}

void BaseShape :: StopDraw()
{
    clicks = 0;
    stopped = true;
    ResetVertices();
}

void BaseShape :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(!stopped)
    {
        target.draw(shape);
        this->VertexShapes::draw(target, states);
    }
}

void Rectangle :: StopDraw()
{
    pos.first = sf::Vector2i(0,0);
    pos.second = sf::Vector2i(0,0);
    BaseShape::StopDraw();
}

bool Rectangle :: StartDraw(const sf::Window & window)
{
    stopped = false;
    if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
    {
        clicks++;
    }

    sf::Vector2i & curPos = clicks == 0 ? pos.first : pos.second;

    sf::Vector2i mPos = sf::Mouse::getPosition(window);
    curPos.x = mPos.x;
    curPos.y = mPos.y;


    if ( clicks == 1) shape[4].position = shape[0].position;

    shape[0].position.x = std::min( pos.first.x, pos.second.x );
    shape[0].position.y = std::min( pos.first.y, pos.second.y );

    shape[1].position.x = std::max( pos.first.x, pos.second.x );
    shape[1].position.y = std::min( pos.first.y, pos.second.y );

    shape[2].position.x = std::max( pos.first.x, pos.second.x );
    shape[2].position.y = std::max( pos.first.y, pos.second.y );

    shape[3].position.x = std::min( pos.first.x, pos.second.x );
    shape[3].position.y = std::max( pos.first.y, pos.second.y );

    return ( clicks == 2 );

}




RegularShape :: RegularShape(int _numOfVertices) : VertexShapes(_numOfVertices), pos(), clicks(0)
{
    shape = sf::VertexArray( sf::LinesStrip,numOfVertices + 1 );
    for(int i = 0; i< numOfVertices + 1; i++) shape[i].color = color;
}


//bool RegularShape :: StartDraw(const sf::Window & window, sf::Event & event)
bool RegularShape :: StartDraw(const sf::Window & window)
{
    stopped = false;
    //if ( event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left )
    if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
    {
        if ( clicks == 0  ) pos.first = sf::Mouse::getPosition(window);
        if ( clicks == 1 ) pos.second = sf::Mouse::getPosition(window);
        clicks++;
    }


    if ( clicks == 1 )
    {
        pos.second = sf::Mouse::getPosition();

        float R = pow( pow( (pos.second.x - pos.first.x),2 ) + pow( (pos.second.y - pos.first.y),2  ), 0.5  );


        float theta = CalculateTheta( sf::Vector2f(pos.first.x, pos.first.y), sf::Vector2f(pos.second.x, pos.second.y) );

        shape[0].position.x = pos.second.x;
        shape[0].position.y = pos.second.y;
        shape[ numOfVertices].position = shape[0].position;

        for(int i = 1; i <  numOfVertices; i++ )
        {
            float phi = theta + i*2*PI/numOfVertices;
            phi = phi >= 2*PI ? phi - 2*PI : phi;
            shape[i].position.x = R*cos(phi) + pos.first.x;
            shape[i].position.y  = -R*sin(phi) + pos.first.y;
        }

    }

    if ( clicks == 2)
    {
        return true;
    }

    return false;

}



inline void RegularShape :: StopDraw()
{
    clicks = 0;
    stopped = true;
    ResetVertices();
}

void RegularShape :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(!stopped)
    {
        target.draw(shape);
        this->VertexShapes::draw(target, states);
    }
}


template<int N>
std::string Polygon<N> :: getSerializationTag()
{
    std::stringstream ss;
    ss << "Polygon_" << N;
    return ss.str();
}

template<int N>
std::string BlockPolygon<N> :: getSerializationTag()
{
    std::stringstream ss;
    ss << "BlockPolygon_" << N;
    return ss.str();
}

template<int N>
inline std::string RegularPolygon<N> :: getSerializationTag()
{
    std::stringstream ss;
    ss << "RegularPolygon_" << N;
    return ss.str();
}

template<int N>
inline std::string RegularBlockPolygon<N> :: getSerializationTag()
{

    std::stringstream ss;
    ss << "RegularBlockPolygon_" << N;
    return ss.str();
}


inline std::string Rectangle :: getSerializationTag()
{
    return "Rectangle";
}


inline  std::string BlockRectangle :: getSerializationTag()
{
    return "BlockRectangle";
}

inline std::string ContinuousLine :: getSerializationTag()
{
    return "ContinuousLine";
}


template class Polygon<2>;
template class Polygon<3>;
template class Polygon<4>;


template class BlockPolygon<3>;
template class BlockPolygon<4>;


template class RegularPolygon<3>;
template class RegularPolygon<4>;
template class RegularPolygon<5>;
template class RegularPolygon<6>;
template class RegularPolygon<8>;
template class RegularPolygon<100>;

template class RegularBlockPolygon<3>;
template class RegularBlockPolygon<4>;
template class RegularBlockPolygon<5>;
template class RegularBlockPolygon<6>;
template class RegularBlockPolygon<8>;
template class RegularBlockPolygon<100>;



}//EON


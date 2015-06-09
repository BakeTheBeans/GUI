#include "drawingpage.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "define.h"
#include <boost/serialization/string.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/tuple/tuple.hpp>

#define SELECT sf::Mouse::isButtonPressed(sf::Mouse::Left
#define DESELECT sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)

namespace Draw {


void DrawingPage :: Save(std::string filename)
{
    std::ofstream file(filename.c_str());
    boost::archive::text_oarchive oarch(file);
    ShapeRegisteration::RegisterShapes<boost::archive::text_oarchive>(oarch);
    oarch << shapeColl;

}


void DrawingPage :: Load(std::string filename)
{
    std::ifstream file(filename.c_str());
    boost::archive::text_iarchive iarch(file);
    ShapeRegisteration::RegisterShapes<boost::archive::text_iarchive>(iarch);
    iarch >> shapeColl;
}

void DrawingPage :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for( ShapePtr shape : shapeColl ) target.draw(*shape);
    if (currentShape) target.draw(*currentShape);
}

void DrawingPage :: EnablePageLoop()
{
    if ( !pageLoop ) return;

    if(DESELECT)
    {
        if ( selectedShape ) selectedShape->deselect();
    }

    for(ShapePtr shape : shapeColl )
    {
        if ( shape->isMouseInside() && sf::Mouse::isButtonPressed(sf::Mouse::Left) )
        {
            if( selectedShape )
            {
                if ( selectedShape != shape && selectedShape->isSelected() ) selectedShape->deselect();
            }
            selectedShape = shape;
            selectedShape->select();
        }

    }
}


void DrawingPage :: SetSize()
{

}


void DrawingPage :: SetUpDisplay()
{
    //pageSize.second = getInternalHeight();
    //displaySize.second = getInternalHeight();
    //pageScrollPos.second = getInternalHeight();
    pageSize = std::make_pair( getInternalWidth(), getInternalHeight());
    displaySize = std::make_pair( getInternalWidth(), getInternalHeight());
    pageScrollPos = std::make_pair( getInternalWidth(), getInternalHeight() );

    setVerticalPageSize(getInternalHeight());
    setVerticalDisplaySize(getInternalHeight());
    setHorizontalDisplaySize(getInternalWidth());
    setHorizontalDisplaySize(getInternalWidth());
}

void DrawingPage :: SetUpWindowDisplay()
{
    SetUpDisplay();
    ConfigureWindow();
}

void DrawingPage :: changeVerticalPageSpace(int step)
{
    pageSize.second += step;
}

void DrawingPage :: changeHorizontalPageSpace(int step)
{
    pageSize.first += step;
}



void DrawingPage :: scrollDown(int offset)
{
//    if ( offset  > 5 ) std::cout << "Drawing Page Warning : " << " offset : " << offset << std::endl;


    if ( pageScrollPos.second >= getVerticalPageSize() ) return;

    int len = ( offset > ( getVerticalPageSize() - pageScrollPos.second ) ) ? ( getVerticalPageSize() - pageScrollPos.second ) : offset;

    //std::cout << " length :  " << len  << "offset   " << offset << std::endl;
    pageScrollPos.second += len;

    std::cout <<"DRAWING PAGE Page Size " <<  pageSize.second << "      Drawing Page :  DisplaySize  " <<  displaySize.first << "  " <<  "  Scroll position " << "  " << pageScrollPos.second << std::endl;



    for( ShapePtr shape : shapeColl )
    {
        shape->MoveShapeUp(len);
    }
}

void DrawingPage :: scrollUp(int offset)
{

    if ( pageScrollPos.second <= displaySize.second ) return;

    //Bug
    //int len = ( offset > (pageScrollPos.second - displaySize.second ) ) ? ( pageSize.second - pageScrollPos.second ) : offset;

    int len = ( offset > (pageScrollPos.second - displaySize.second ) ) ? pageScrollPos.second - displaySize.second : offset;

    pageScrollPos.second -= len;

    std::cout << "Window Page Size " <<  pageSize.second << "   DisplaySize  " <<  displaySize.second << "  " <<  "  Scroll position " << "  " << pageScrollPos.second << std::endl;

    if ( (offset > 5) || (len > 5) )
    {
        std::cout << "WARNING : offset is  : " << offset << "   Length : " << len << std::endl;
    }

    for( ShapePtr shape : shapeColl )
    {
        shape->MoveShapeDown(len);
    }
}


void DrawingPage :: scrollRight(int offset)
{

    if ( pageScrollPos.first >= getHorizontalPageSize() ) return;

    int len = ( offset > ( getHorizontalPageSize() - pageScrollPos.first ) ) ? ( getHorizontalPageSize() - pageScrollPos.first ) : offset;

    pageScrollPos.first += len;

    for( ShapePtr shape : shapeColl )
    {
        shape->MoveShapeLeft(len);
    }
}

void DrawingPage :: scrollLeft(int offset)
{

    if ( pageScrollPos.first <= displaySize.first ) return;

    //BUG
     //int len = ( offset > (pageScrollPos.first - displaySize.first ) ) ? ( pageSize.first - pageScrollPos.first ) : offset;

    int len = ( offset > (pageScrollPos.first - displaySize.first ) ) ? ( pageScrollPos.first - displaySize.first ) : offset;

    pageScrollPos.first -= len;

    for( ShapePtr shape : shapeColl )
    {
        shape->MoveShapeRight(len);
    }

}



void DrawingPage :: zoom(float scale)
{

    int minX = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int minY = std::numeric_limits<int>::max();
    int maxY = std::numeric_limits<int>::min();

    int  count = 0;
    sf::Vector2f prevCentroid;
    for( ShapePtr shape : shapeColl )
    {
        auto shapeBound_1 = shape->getBounds();
        //auto cen_1 = shape->getCentroid();
        shape->scale(scale,scale);
        auto shapeBound_2 = shape->getBounds();


        //int xdiff = shapeBound_1.first.x - shapeBound_2.first.x;
        //int ydiff = shapeBound_1.first.y - shapeBound_2.first.y;

        if ( count > 0 )
        {
            auto cen = shape->getCentroid();
            float xdiff = scale*(cen.x - prevCentroid.x);
            float ydiff = scale*(cen.y - prevCentroid.y);

            ( xdiff < 0 ) ? shape->MoveShapeLeft( std::abs(xdiff) ) : shape->MoveShapeRight( std::abs(xdiff) );

            ( ydiff < 0 ) ? shape->MoveShapeUp( std::abs(ydiff) ) : shape->MoveShapeDown( std::abs(xdiff) );

        }


        prevCentroid = shape->getCentroid();
        //( xdiff < 0 ) ? shape->MoveShapeLeft( std::abs(xdiff) ) : shape->MoveShapeRight( std::abs(xdiff) );

        //( ydiff < 0 ) ? shape->MoveShapeUp( std::abs(ydiff) ) : shape->MoveShapeDown( std::abs(xdiff) );

        auto bounds = shape->getBounds();
        minX = std::min( minX, (int)bounds.first.x );
        minY = std::min( minY, (int)bounds.first.y );
        maxX = std::max( maxX, (int)bounds.second.x );
        maxY = std::max( maxY, (int)bounds.second.y );
        std::cout << "maxX = " << maxX << "   maxY   : " << maxY << std::endl;

    }



    std::cout << " Vertical Page Size before zoom " <<pageSize.second << std::endl;

    if ( scale > 1 )
    {
        pageSize.first = std::max( pageSize.first, maxX );
        pageSize.second = std::max( pageSize.second, maxY);
    }

    else
    {
        pageSize.first = std::max( std::min(pageSize.first, maxX ), displaySize.first );
        pageSize.second = std::max( std::min(pageSize.second, maxY), displaySize.second );

    }

    std::cout << " Vertical Page Size after zoom " << pageSize.second << std::endl;

}



}//EON

#include "mouseprojector.h"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/Window.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

namespace  Draw {


MouseProjector :: MouseProjector()
{
    flag = false;
    xProjection = sf::VertexArray(sf::LinesStrip);
    yProjection = sf::VertexArray(sf::LinesStrip);
}

MouseProjector & MouseProjector :: getMouseProjector()
{
    static MouseProjector  proj;// = new MouseProjector();
    return proj;
}


void MouseProjector :: Project(sf::Window & window)
{

    if ( flag )
    {
        xProjection.clear();
        yProjection.clear();
        auto winSz = window.getSize();
        auto mousePos = sf::Mouse::getPosition(window);
        int start = 0;
        bool col = true;
        while( start < winSz.x )
        {
            if(col) xProjection.append(sf::Vertex(sf::Vector2f(start, mousePos.y), sf::Color::White) );
            else xProjection.append(sf::Vertex(sf::Vector2f(start, mousePos.y), sf::Color::Black) );
            col = !col;
            start += 5;
        }

        start = 0;
        while( start < winSz.y )
        {
            if(col) yProjection.append(sf::Vertex(sf::Vector2f(mousePos.x,start), sf::Color::White) );
            else yProjection.append(sf::Vertex(sf::Vector2f(mousePos.x,start), sf::Color::Black) );
            col = !col;
            start += 5;
        }
    }

}


void MouseProjector :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(xProjection);
    target.draw(yProjection);
}


}

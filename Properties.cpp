#include "Properties.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define MousePositionRelativeToWindow sf::Vector2i( (sf::Mouse::getPosition().x - window->getPosition().x), (sf::Mouse::getPosition().y - window->getPosition().y) )


namespace GUI {


void IHover :: SetUpHover(sf::Texture * _origTexture, sf::Texture * _hover)
{
    if ( !_hover )  throw "Hover : Texture cannot be null";
    hoverTexture  = _hover;
    originalTexture = _origTexture;
    if ( !originalTexture ) throw "Hover : Setup failed, could not get original texure of the object";
}


//void IHover :: Hover(float window_x, float window_y)
void IHover :: Hover(sf::Window * window)
{

    if ( mode )
    {
        bool isinside = false;
        sf::Vector2i mousePos = sf::Mouse::getPosition();

        if ( ( isinside = ObjectContainsMouseCursor(self,mousePos) ) )
        {

            if ( isHoverTextureSet ) return;
            else
            {
                self.setTexture(*hoverTexture);
                isHoverTextureSet = true;
            }

        }
        else
        {
            if ( isHoverTextureSet ) self.setTexture(*originalTexture);
            isHoverTextureSet = false;
        }
    }
}


IDrag::CouplingState IDrag :: CheckMouseCoupling()
{
    if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) ) return IDrag::Capture;
    else return IDrag::Release;

}

void IDrag :: RecordMousePosition(sf::Window * window)
{

    static int count = 0;
    if ( ++count < DELAY ) return;
    else
    {
        count = 0;
        sf::Vector2i pos = MousePositionRelativeToWindow;
        prevMousePosition.first = pos.x;
        prevMousePosition.second = pos.y;
    }
}


void IDrag :: Drag(sf::Window * window)
{

    if ( dragmode )
    {
        RecordMousePosition(window);
        sf::Vector2i mousePos = sf::Mouse::getPosition();

        if ( ObjectContainsMouseCursor(self,mousePos) && (CheckMouseCoupling() == IDrag::Capture ) )
        {
            sf::Vector2i currentPos = MousePositionRelativeToWindow;
            int xdiff = currentPos.x - prevMousePosition.first;
            int ydiff = currentPos.y - prevMousePosition.second;

            if(( std::abs(xdiff) + std::abs(ydiff) ) > PIXELS_MOVED)
            {

                sf::Vector2f pos = self.getPosition();
                self.move(xdiff,ydiff);
            }

        }
    }
}


EON

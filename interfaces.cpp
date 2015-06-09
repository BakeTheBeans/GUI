#include "interfaces.h"
#include "define.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

namespace GUI {



IScrollable :: IScrollable() : verticalDisplaySize(), verticalPageSize(), horizontalDisplaySize(), horizontalPageSize(), window(0), windowFlag(false)
{}


void IScrollable :: ConfigureWindow()
{
    if ( window)
    {
        window->ConfigureVerticalScrollBar();
        window->ConfigureHorizontalScrollBar();
        window->ResizeWindow();
    }
}

void IScrollable :: resetVerticalScrollBar()
{
  if(window) window->ResetVerticalScrollBar();
}

void IScrollable :: WindowDisplay()
{
    if ( windowFlag ) SetUpWindowDisplay();
}


bool IKeyBoardInteraction :: InteractWithKeyBoard(sf::Event & event)
{
    if ( event.type == sf::Event::KeyPressed )
    {
        if ( event.key.code == sf::Keyboard::Return )
            ActionOnPressingReturn();

        if( event.key.code == sf::Keyboard::Up )
            ActionOnPressingUpArrow();

        if ( event.key.code == sf::Keyboard::Down )
            ActionOnPressingDownArrow();
    }
}


const float EnclosingBox :: DefaultBorderSize = 3;
const sf::Color EnclosingBox :: DefaultBorderColor = COL_GRAY_5;
const float EnclosingBox :: DefaultMarginSize = 1;
const sf::Color EnclosingBox :: DefaultFillColor = COL_GRAY_12;


EnclosingBox :: EnclosingBox() : box(), width(), height(),  borderSize(DefaultBorderSize), marginSize(DefaultMarginSize)
{
    box.setOutlineThickness(borderSize);
    box.setOutlineColor(DefaultBorderColor);
    box.setFillColor(DefaultFillColor);
    setUp = false;
}

EnclosingBox :: EnclosingBox(float _width, float _height, float _borderSize, float _marginSize) : box(), width(_width), height(_height), borderSize(_borderSize), marginSize(_marginSize)
{
    box.setSize(sf::Vector2f(width, height));
    box.setOutlineThickness(borderSize);
    box.setOutlineColor(DefaultBorderColor);
    box.setFillColor(DefaultFillColor);
}

sf::Vector2f EnclosingBox :: getInternalPosition() const
{
    const sf::Vector2f & pos = box.getPosition();
 return sf::Vector2f((pos.x + marginSize),(pos.y + marginSize) );
}

const sf::Vector2f EnclosingBox ::  getPosition() const
{
    return sf::Vector2f( box.getPosition().x - borderSize, box.getPosition().y - borderSize );
}

void EnclosingBox :: setInternalWidth(float _width)
{
    width = _width;
    box.setSize(sf::Vector2f(width,height));
}

void EnclosingBox :: setInternalHeight(float _height)
{
    height = _height;
    box.setSize(sf::Vector2f(width, height));
}


void EnclosingBox :: setBorderSize(float _borderSize)
{
    borderSize = _borderSize;
    box.setOutlineThickness(borderSize);
    setUp = false;
}

void  EnclosingBox :: setMarginSize(float _marginSize)
{    
    marginSize = _marginSize;
    setUp = false;
    //SetSize();
}

void EnclosingBox :: setSize(float _width, float _height )
{    
    width = _width;
    height = _height;
    box.setSize(sf::Vector2f(width, height));
    SetSize();
    setUp = false;

}

void  EnclosingBox ::  setPosition(float posX, float posY)
{
    box.setPosition(posX + borderSize, posY + borderSize);
    //box.setPosition(posX,posY);
    SetPosition();
    //setUp = false;
}

bool  EnclosingBox :: ContainsMouseInside(sf::Window * window)
{
    const sf::Vector2i & Mpos = sf::Mouse::getPosition();
    return box.getGlobalBounds().contains( Mpos.x - window->getPosition().x, Mpos.y - window->getPosition().y  );
}


void EnclosingBox :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{
        if ( ! isConfigured() ) throw "SetUpDisplay for the object, before rendering. This ensures that all changes to the configuration are committed";
    target.draw(box);
}

EON

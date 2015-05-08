#include "menu.h"
#include "Utility.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define DefualtPosition 200,100


namespace GUI {


MenuBar :: MenuBar(const char * _name, internal::AlignmentType _alignment,float _slabWidth, float _slabHeight,float _borderSize) : IButton(), menuShape(), xScale(1), yScale(1), slabHeight(_slabHeight), slabWidth(_slabWidth),borderSize(_borderSize), End(),alignment(_alignment), isCollapsed(false), name(_name), buttonList(),  init(false), count()
{
    menuShape.reset(new sf::RectangleShape());
    menuShape->setOutlineColor(COL_GRAY);
    menuShape->setOutlineThickness(borderSize);
    menuShape->setPosition(DefualtPosition);
    End = buttonList.end();
}


void MenuBar :: setName(const char * _name)
{
    name = std::string(_name);
}

float MenuBar :: setBorderSize(float _border)
{
    borderSize = _border;
    menuShape->setOutlineThickness(borderSize);
}

const int MenuBar :: xFactor() const
{
     return (alignment == internal::Horizontal) ? count : 1;
}

const int MenuBar :: yFactor() const
{
     return (alignment == internal::Horizontal) ? 1 : count;
}

const sf::Vector2f MenuBar :: getFrameDimensions() const
{
    return sf::Vector2f(xScale*slabWidth*xFactor(),yScale* slabHeight*yFactor());

}

const sf::Vector2f MenuBar :: getSlabDimensions() const
{
    return sf::Vector2f(xScale*slabWidth, yScale*slabHeight);
}

const sf::Vector2f MenuBar :: getMenuItemPositionAt(int buttonIndex) const
{
    int size = buttonIndex;
    return alignment == internal::Horizontal ? sf::Vector2f( menuShape->getPosition().x + size*slabWidth*xScale, menuShape->getPosition().y ) : sf::Vector2f(menuShape->getPosition().x, menuShape->getPosition().y + size*slabHeight*yScale);

}


MenuBar & MenuBar :: AddMenuItem(ButtonPtr _button)
{

    if (!_button) return *this;
    count++;
    if ( count > 0) init = true;

    if ( _button->getGUIType() == internal::Button )
    {
        auto bb = _button->getGlobalBounds();
        float scaleX = slabWidth/ bb.width;
        float scaleY = slabHeight/bb.height;
        _button->scale(scaleX,scaleY);
    }


    if ( _button->getGUIType() == internal::Menu )
    {
        MenuBar * p = static_cast<MenuBar*>(_button);
        if ( (p->xScale != xScale) || (p->yScale != yScale) )
        {
            p->scale(xScale,yScale);
        }
    }

    menuShape->setSize(getFrameDimensions());
    _button->setPosition(getMenuItemPositionAt(buttonList.size()));
    buttonList.push_back(_button);
    End = buttonList.end();
    return *this;

}

void MenuBar :: InsertButton(ButtonPtr _button)
{
    buttonList.push_back(_button);
}

void MenuBar :: SwapAlignment()
{
    alignment = (alignment == internal::Horizontal) ? internal::Vertical : internal::Horizontal;
    menuShape->setSize(getFrameDimensions());
    const sf::Vector2f & pos = menuShape->getPosition();
    this->setPosition(pos.x,pos.y);
}


void MenuBar :: setPosition(float posX, float posY)
{
    menuShape->setPosition(posX,posY);
    std::vector<ButtonPtr>::iterator it = buttonList.begin();
    int buttonPos = 0;

    while( it != End )
    {
        auto pos = getMenuItemPositionAt(buttonPos);
        if( (*it)->getGUIType() == internal::Menu )
        {
           MenuBar * p = static_cast<MenuBar*>(*it);
           p->setPosition(pos.x, pos.y);
        }
        else
        {
            IButton * p = *it;
            p->setPosition(pos.x, pos.y);
        }

        buttonPos++;
        it++;
    }
}

void MenuBar :: UnscaleButton(ButtonPtr p)
{
    if ( xScale == 0 || yScale == 0) throw "MenuBar : Cannot Unscale for scale value 0.";
    p->scale(1/xScale,1/yScale);
}

void MenuBar :: scale(float scaleX, float scaleY)
{
    if ( scaleX == 0 || scaleY == 0) throw "MenuBar : Cannot scale for scale value 0.";

    std::cout << " Hello " << std::endl;
    auto setScale = [&] ()->void
    {
            xScale = scaleX;
            yScale = scaleY;
    };

    Iter it = buttonList.begin();
    int buttonPos = 0;


    while( it != End )
    {

        if( (*it)->getGUIType() == internal::Menu )
        {

            MenuBar * p = static_cast<MenuBar*>(*it);
            p->scale(scaleX,scaleY);

        }

        else
        {
            IButton * p = *it;
            UnscaleButton(p);
            p->scale(scaleX,scaleY);
        }

        (*it)->setPosition(getMenuItemPositionAt(buttonPos));
        buttonPos++;
        it++;

    }

    setScale();
    float posX = menuShape->getPosition().x;
    float posY = menuShape->getPosition().y;
    setPosition(posX,posY);
    //menuShape->setSize(sf::Vector2f(frameWidth, frameHeight) );
    menuShape->setSize( getFrameDimensions() );
}


void MenuBar :: move(float xOffset, float yOffset)
{
    setPosition(menuShape->getPosition().x + xOffset ,menuShape->getPosition().y + yOffset);
}


void MenuBar :: Collapse()
{
    isCollapsed = true;
    End = buttonList.begin() + 1;
    //menuShape->setSize(sf::Vector2f(slabWidth, slabHeight));
    menuShape->setSize(getSlabDimensions());
    for(Iter it = buttonList.begin(); it != buttonList.end(); it++)
    {
        ButtonPtr p = *it;
        if ( p->getGUIType() == internal::Menu )
        {
            MenuBar * q = static_cast<MenuBar*>(p);
            q->Collapse();
        }
    }
}


void MenuBar :: Expand()
{
    isCollapsed = false;
    End = buttonList.end();
    menuShape->setSize(getFrameDimensions());
}

void MenuBar :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //if (!isValid) throw"MenuBar is not valid. Call SetUp";
    if ( init )
    {
        target.draw(*menuShape);
        for(auto it = buttonList.begin(); it != End; it++)
            target.draw(*(*it));
    }
}

//***************************************************************







EON

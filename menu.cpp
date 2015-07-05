#include "menu.h"
#include "Utility.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define DefualtPosition 200,100


namespace GUI {


MenuBar :: MenuBar(const char * _name, internal::AlignmentType _alignment,float _slabWidth, float _slabHeight,float _borderSize) : IButton(), menuShape(nullptr), xScale(1), yScale(1), slabHeight(_slabHeight), slabWidth(_slabWidth),borderSize(_borderSize), End(),alignment(_alignment), isCollapsed(false), name(_name), buttonList(),  init(false), count()
{
    //menuShape.reset(new sf::RectangleShape());
    menuShape = new sf::RectangleShape();
    menuShape->setOutlineColor(COL_GRAY);
    menuShape->setOutlineThickness(borderSize);
    menuShape->setPosition(DefualtPosition);
    End = buttonList.end();
}


MenuBar :: MenuBar(MenuBar && obj) : /*menuShape(std::move(obj.menuShape))*/ menuShape(obj.menuShape), xScale(obj.xScale), yScale(obj.yScale), slabHeight(obj.slabHeight), slabWidth(obj.slabWidth), borderSize(obj.borderSize), End(obj.End), alignment(obj.alignment), isCollapsed(obj.isCollapsed), name(obj.name), buttonList(obj.buttonList)
{
    obj.buttonList.clear();
    obj.menuShape;
}


MenuBar & MenuBar :: operator=(MenuBar && obj)
{
    //menuShape = std::move(obj.menuShape);
    menuShape = obj.menuShape;
    obj.menuShape = nullptr;
    xScale = obj.xScale;
    yScale = obj.yScale;
    slabHeight = obj.slabHeight;
    slabWidth = obj.slabWidth;
    borderSize = obj.borderSize;
    End = obj.End;
    alignment = obj.alignment;
    isCollapsed = obj.isCollapsed;
    name = obj.name;
    buttonList = obj.buttonList;
    obj.buttonList.clear();
    return *this;
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


MenuBar & MenuBar :: AddMenuItem(const ButtonSPtr & _button)
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
        MenuBar * p = static_cast<MenuBar*>(_button.get());        
        if ( (p->xScale != xScale) || (p->yScale != yScale) )
        {
            p->scale(xScale,yScale);
        }
    }


    menuShape->setSize(getFrameDimensions());
    _button->setPosition(getMenuItemPositionAt(buttonList.size()));

    if ( _button->getGUIType() == internal::Menu ) {
        MenuBar * p = static_cast<MenuBar*>(_button.get());
        std::cout << "name of Menu : " << p->getName() << "Menu  Position : " << _button->getPosition().x << "   " << _button->getPosition().y << std::endl;
    }

    buttonList.push_back(_button);
    End = buttonList.end();
    return *this;

}


//Do not use
void MenuBar :: InsertButton(ButtonSPtr & _button)
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
    std::vector<ButtonSPtr>::iterator it = buttonList.begin();
    int buttonPos = 0;

    while( it != End )
    {
        auto pos = getMenuItemPositionAt(buttonPos);
        if( (*it)->getGUIType() == internal::Menu )
        {
           MenuBar * p = static_cast<MenuBar*>((*it).get());
           p->setPosition(pos.x, pos.y);
        }
        else
        {
            IButton * p = it->get();
            p->setPosition(pos.x, pos.y);
        }

        buttonPos++;
        it++;
    }
}

void MenuBar :: UnscaleButton(const ButtonSPtr & p)
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

            MenuBar * p = static_cast<MenuBar*>((*it).get());
            p->scale(scaleX,scaleY);

        }

        else
        {
            IButton * p = (*it).get();
            UnscaleButton(*it);
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
        IButton * p = (*it).get();

        if ( p->getGUIType() == internal::Menu )
        {
            MenuBar * q = static_cast<MenuBar*>((*it).get());
            q->Collapse();
        }
    }

    disableHovering();
}


void MenuBar :: Expand()
{    
    isCollapsed = false;
    End = buttonList.end();
    menuShape->setSize(getFrameDimensions());
    enableHovering();
}

void MenuBar :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //if (!isValid) throw"MenuBar is not valid. Call SetUp";
    if ( init )
    {
        target.draw(*menuShape);
        for(auto it = buttonList.begin(); it != End; it++)
            target.draw(*(*it).get());
    }
}

bool MenuBar :: IsMouseInside(sf::Window & window)
{
    sf::Vector2i mPos = sf::Mouse::getPosition(window);

    const sf::FloatRect & pos = menuShape->getGlobalBounds();

    std::cout << "X : " << pos.left << " Y : " << pos.top <<
                 " X : " << pos.left + pos.width << " Y : " << pos.top <<
                 " X : " << pos.left + pos.width << " Y : " << pos.top + pos.height <<
                 " X : " << pos.left << " Y : " << pos.top + pos.height <<
                 std::endl;

    std::cout << " Mouse Position : " << mPos.x << "   " << mPos.y << std::endl;

    return menuShape->getGlobalBounds().contains(mPos.x, mPos.y);

}

void MenuBar :: Hover(sf::Window & window)
{

    auto menuhover = [this, &window] (MenuBar * menubar)-> void
    {
        bool inside = IsMouseInside(window);

        if ( inside ) std::cout << "Mouse is inside " << menubar->getName() << std::endl;
        else std::cout << "Mouse is outside " << menubar->getName() << std::endl;



        if ( !( menubar->isCollapsed ) )
        {
            if ( inside ) return;
            else menubar->Collapse();
        }

        else
        {
            if( inside ) menubar->Expand();
            else return;
        }

    };


    for( ButtonSPtr & button : buttonList )
    {
        switch(button->getGUIType())
        {

        case internal::Menu:
            menuhover( static_cast<MenuBar*>(button.get() ) );
            break;

        case internal::Button:
            button->Hover(window);
            break;
        }

    }
}

//***************************************************************



EON

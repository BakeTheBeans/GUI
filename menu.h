#ifndef MENU_H
#define MENU_H
#include "define.h"
#include <vector>
#include <memory>
#include <set>
#include "button.h"
#include "tools.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "interfaces.h"
#include "Traits.h"


#define DefaultSlabHeight 60
#define DefaultSlabWidth 170
#define DefaultMenuBorderSize 4

#define MENU_DEBUG 0

namespace sf {
class Texture;
class Sprite;
class RenderTarget;
class RectangleShape;

}



namespace GUI {

//class IButton;

class IMenu
{

public:

    virtual ~IMenu() {}

};


//typedef IButton * ButtonSPtr;
typedef std::shared_ptr<IButton> ButtonSPtr;

class MenuBar : public IButton
{
public:
    static const internal::GUI_Type gui_Type = internal::Menu;

private:
    //std::unique_ptr<sf::RectangleShape> menuShape;
    sf::RectangleShape * menuShape;
    float xScale,yScale;
    float slabHeight, slabWidth;
    float borderSize;
protected:
    std::vector<ButtonSPtr>::iterator End;
    internal::AlignmentType alignment;
    bool isCollapsed;
    std::string name;
    std::vector<ButtonSPtr> buttonList;
    typedef std::vector<ButtonSPtr>::iterator Iter;

private:
    bool init;
    int count;

    void setOutlineThickness(float _size){}
    float getOutlineThickness() const {}


private:
    //Non-Copyable
    MenuBar(const MenuBar & obj );
    MenuBar & operator=(const MenuBar & obj);

protected:
    const sf::Vector2f getMenuItemPositionAt(int buttonIndex) const;
    const int xFactor() const;
    const int yFactor() const;
    void UnscaleButton(const ButtonSPtr & p);

public:

    explicit MenuBar(const char * _name,internal::AlignmentType _alignment = internal::Horizontal, float _slabWidth = DefaultSlabWidth, float _slabHeight = DefaultSlabHeight,float _borderSize = DefaultMenuBorderSize);
    ~MenuBar()
    {
        if ( menuShape ) delete menuShape;        
    }
    MenuBar(MenuBar && obj);
    MenuBar & operator=(MenuBar && obj);

    MenuBar & AddMenuItem(const ButtonSPtr & _button);
    IButton * RemoveMenuItem() { throw "MenuBar::RemoveMenuItem - Not implemented"; }

    const sf::Vector2f getSlabDimensions() const;
    const sf::Vector2f getFrameDimensions() const;
    //Do not use
    void InsertButton(ButtonSPtr & _button);
    void draw(sf::RenderTarget & target, sf::RenderStates states) const;
    void setPosition(float posX, float posY);
    void setName(const char * _name);
    std::string getName() const { return name; }
    const sf::Vector2f & getPosition() const { return menuShape->getPosition(); }
    float setBorderSize(float _border);
    float getBorderSize() { return borderSize; }
    void setBorderColor(sf::Color _borderColor) { menuShape->setOutlineColor(_borderColor); }    

    inline bool IsMouseInside(sf::Window & window);
    virtual void scale(float scaleX, float scaleY);
    void move(float xOffset, float yOffset);
    void SwapAlignment();
    void Collapse();
    void Expand();
    virtual void Press() {}
    virtual void Release() {}
    virtual void Hover(sf::Window &window);
    virtual const internal::GUI_Type getGUIType() const { return gui_Type; }

};

//****************************************************************

namespace internal
{
template<>
struct HasSetSize<MenuBar>
{
    static const bool value = false;
};

template<>
struct HasSetFillColor<MenuBar>
{
    static const bool value = false;
};

}//EON


EON

#endif // MENU_H

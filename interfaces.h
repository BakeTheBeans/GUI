#ifndef INTERFACES_H
#define INTERFACES_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <iostream>

#include "define.h"   // Not neede - just for debug

namespace sf {
class Window;
class Event;
}


namespace GUI {


namespace internal
{
    enum AlignmentType
    {
        Horizontal,
        Vertical
    };

}


class IBoxlike
{

public:
    /*
     * Total height - including borders etc.
     */
    virtual float getHeight() const =0;
    /*
     * Total width including borders etc.
     */
    virtual float getWidth() const =0;

    virtual void setSize(float _width, float _height )=0;
    /*
     * Uniform border size
     */

    virtual float getBorderSize() const { return 0; }
    virtual void setBorderSize(float _borderSize) {}

};


//Note - Replace this with a more robust interface taht allows other operations
// like move, resize etc.
class IPosition
{
public:
    virtual ~IPosition(){}
    virtual const sf::Vector2f getPosition() const=0;
    virtual void setPosition(float posX, float posY)=0;
};

class IConfigure
{
protected:
    bool setUp;


    IConfigure() : setUp(false) {}

    /*
     * On invoking this function the object should be
     * completely set up. Any other features added are
     * assuming that the current object has been set up.
    */
    virtual void SetUpDisplay()=0;
public:
     virtual ~IConfigure(){}

    bool isConfigured() const { return setUp; }

    void Configure()
    {
         SetUpDisplay();
         setUp = true;         
    }

};


class IScrollWindowCallBack
{

//protected:
public:
    virtual ~IScrollWindowCallBack() {}
    virtual void ConfigureDisplayObject()=0;
    virtual void ConfigureVerticalScrollBar()=0;
    virtual void ConfigureHorizontalScrollBar()=0;
    virtual void ResizeWindow() {}
    virtual void ResetVerticalScrollBar(){}
    virtual void RestHorizontalScrollBar()
    {        
        throw "^Not implemented^";
    }
};


/*
 * This Interface must be implemented if the class - entity - is to be
 * wrapped with scrollable window.
 */
class IScrollable
{

template<typename T> friend class ScrollableWindow;
friend class IScrollWindowCallBack;

private:
    unsigned int verticalDisplaySize;
    unsigned int verticalPageSize;
    unsigned int horizontalDisplaySize;
    unsigned int horizontalPageSize;
    bool windowFlag;

protected:
    IScrollWindowCallBack * window;
    void AttachCallBackWindow(IScrollWindowCallBack * _window) { window = _window; }

    /*
     * Perform any operation on the entity held by the ScrollableWindow
     * The scrollable window takes care of the window and scroll bars.
     * The logic for the entity goes here.
     */
    virtual void SetUpWindowDisplay()=0;


public:
    /*
     * Sets up the display required for Scrolling window.
     * display size determines the amount of display on
     * the srollable window.
     */
    virtual void WindowDisplay();


//public:
protected:
    void setVerticalPageSize(int _size) {verticalPageSize = _size; }

    void setVerticalDisplaySize(int _size) { verticalDisplaySize = _size; }

    void setHorizontalPageSize(int _size) { horizontalPageSize = _size; }

    void setHorizontalDisplaySize(int _size) { horizontalDisplaySize = _size; }

    /*
     * It is useful to call ConfigureWindow in the entity class
     *  when changes take place in th epage configuration - configuration
     * changes refer to changes in page size or display size and not
     * the page contet itself. Calling ConfigureWindow allos the csrollableWindow
     * class to adjust the scroll bars.
     */
    void ConfigureWindow();

    void resetVerticalScrollBar();

    /*
     * This is method is called when scrollable window page
     * is vertically increased or
     * reduced in size dynamically eg. while zooming
     */
    virtual void changeVerticalPageSpace(int step) { throw "IScollable::CreateVerticalPageSpace not implemented"; }

    /*
     * This is method is called when scrollable window page
     * is horizontally increased or
     * reduced in size dynamically eg. while zooming
     */
    virtual void changeHorizontalPageSpace(int step) { throw "IScollable::CreateHorizontalPageSpace not implemented"; }

    virtual void zoom(float scale) { throw "IScollable::zoom not implemented"; }

    virtual void ResetPosition() {throw "IScollable::ResetPosition not implemented"; }


public:
    /*
     *Total heigh/span of the page to be displayed.
     *Required for Vertical Scrolling.
     */
    int getVerticalPageSize() { return verticalPageSize; }

    /*
     * Width of the display area eg. height of
     * display window.
     * Required for Vertical Scrolling.
     */
    int getVerticalDisplaySize() { return verticalDisplaySize; }

    /*
     *Total width/span of the page to be displayed.
     *Required for Horizontal Scrolling.
     */
    int getHorizontalPageSize() { return horizontalPageSize; }

    /*
     * Width of the display area eg. width of
     * display window.
     * Required for Horizontal Scrolling.
     */
    int getHorizontalDisplaySize() { return horizontalDisplaySize; }

    /*
     * Below functions should be defined in the classes
     * that can used with Scrollable Window. These have the
     * following job:
     * 1. Implemnt what must be diplayed when page is scrolled
     * 2. Logic to stop the scrolling on reaching the start or
     * end of page.
     */
    virtual void scrollUp(int offset)=0;
    virtual void scrollDown(int offset)=0;
    virtual void scrollRight(int offset)=0;
    virtual void scrollLeft(int offset)=0;


public:
    IScrollable();    
    virtual ~IScrollable() {}

};

/*
template<typename T>
struct ScrollableEntityTrait
{
    static const bool CanAdaptToWindow = true;
};
*/

class IMouseInteraction
{
protected:
    bool isMouseInside;
    bool mouseInducedChanges;

    IMouseInteraction() : isMouseInside(false), mouseInducedChanges(false) {}
public:

    virtual bool ContainsMouseInside(sf::Window * window)=0;
    virtual bool InteractWithMouse(sf::Window * window) {}
    virtual void MouseLeft(sf::Window * window) {}

};

class IKeyBoardInteraction
{

protected:
    IKeyBoardInteraction() {}
private:
    virtual bool ActionOnPressingReturn() {}
    virtual void ActionOnPressingDownArrow() {}
    virtual void ActionOnPressingUpArrow() {}

public:
    virtual bool InteractWithKeyBoard(sf::Event & event);

};


class EnclosingBox : public IPosition, public IConfigure, public sf::Drawable, public IMouseInteraction, public IKeyBoardInteraction
{
protected:
    static const float DefaultBorderSize;
    static const sf::Color DefaultBorderColor;
    static const float DefaultMarginSize;
    static const sf::Color DefaultFillColor;

private:
 sf::RectangleShape box;
 float width, height;
 float borderSize;
 float marginSize;


private:

 /*
  * only set the size of all the contained parts,
  * of a complex drawable structure.
  * Realignment is taken care by Configure/SetUpDisplay.
  */
 virtual void SetSize() = 0;
 /*
  * only sets the position of all the contained parts,
  * of a complex drawable structure.
  * Realignment is taken care by Configure/SetUpDisplay.
  */

 virtual void SetPosition()=0;

protected:

 /*
  * The height of the free space in the box
  * free space is the space without border and margin
  */
 float getInternalHeight() const{ return height - 2*marginSize; }

 /*
  * Width of the free space inside the box
  * free space is the space without border and margin
  */
 float getInternalWidth() const { return width - 2*marginSize; }

 /*
  * Internal corner left position of the free space in the box
  * free space is the space without border and margin
  */
 sf::Vector2f getInternalPosition() const;

/*
 *
 * Internal width is the width of free space  with no border or margin
 */
 void setInternalWidth(float _width);

/*
 * Internal width is the height of free space  with no border or margin
 */
 void setInternalHeight(float _height);

public:

    EnclosingBox();

    EnclosingBox(float _width, float _height, float _borderSize, float MarginSize);

    virtual ~EnclosingBox() {}

    void PrintDetails()
    {

        std::cout << "User defined Height : " << height << std::endl;
        std::cout << "Func getHeight() : " << getHeight() << std::endl;
        std::cout << " Global Height " << box.getGlobalBounds().height << std::endl;
        std::cout << "Raw Height + Border" << height + 2*borderSize << std::endl;
        std::cout << "Internal" << getInternalHeight() << std::endl;

        std::cout << "User defined width : " << width << std::endl;
        std::cout << "Func getWidth() : " << getWidth() << std::endl;
        std::cout << " Global Width " << box.getGlobalBounds().width << std::endl;
        std::cout << "Internal" << getInternalWidth() << std::endl;

    }

    /*
     * Total height - including borders etc. Like localBound
     */
   float getHeight() const
   { return height + 2*borderSize; }

    /*
     * Total width including borders etc. Like localBound
     */
    float getWidth() const { return width + 2*borderSize; }

    /*
     * Uniform border size
     */
    virtual const sf::Vector2f getPosition() const;

    /*
     * sets the height and width of the enclosing box.
     * This does not include the border size.
     */
    void setSize(float _width, float _height );

    /*
     * The border size is in addition to the size set to the encloseing box
     */
    void setBorderSize(float _borderSize);

    void setMarginSize(float _marginSize);

    void setFillColor(sf::Color _color) { box.setFillColor(_color); }

    void setBorderColor(sf::Color _color) { box.setOutlineColor(_color); }

    virtual void setPosition(float posX, float posY);    

    virtual float getBorderSize() const { return borderSize; }

    const sf::Color & getBorderColor() const { return box.getOutlineColor(); }

    const sf::Color & getFillColor() const { return box.getFillColor(); }

    float getMarginSize() { return marginSize; }

    virtual bool isResizeable() { return true;}       

    bool ContainsMouseInside(sf::Window * window);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};




} //eon
#endif // INTERFACES_H

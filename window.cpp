#include "window.h"
#include "menupage.h"
#include "directorymenupage.h"
#include "drawingpage.h"

namespace GUI {

template<typename T> const float ScrollableWindow<T>::DefaultScrollBarThickness = 10;
template<typename T> const float ScrollableWindow<T> :: DefaultScrollFrameWidth = 5;

template<typename T>
ScrollableWindow<T> :: ScrollableWindow() : vScroll(internal::Vertical), hScroll(internal::Horizontal),ScrollThickness(DefaultScrollBarThickness), hHide(false),
vHide(false), DisplayObj(0), dummy(0)
{
    T * check = 0;
    IScrollable * ScrollableCheck = static_cast<IScrollable*>(check);
    EnclosingBox * BoxCheck = static_cast<EnclosingBox*>(check);

    {
        dummy = new T();
        dummy->setFillColor(COL_BLACK);
        DisplayObj = dummy;
    }
    setSize(100,100); //Do not remove
    hHide = false;
    vHide = false;
    vScroll.setBorderSize(DefaultScrollFrameWidth);
    hScroll.setBorderSize(DefaultScrollFrameWidth);

    DisplayObj->IScrollable::AttachCallBackWindow(this);

}



template<typename T>
ScrollableWindow<T> :: ScrollableWindow(T * obj) : vScroll(internal::Vertical), hScroll(internal::Horizontal),ScrollThickness(DefaultScrollBarThickness), hHide(false),
vHide(false), DisplayObj(0), dummy(0)
{
    T * check = 0;
    IScrollable * ScrollableCheck = static_cast<IScrollable*>(check);
    EnclosingBox * BoxCheck = static_cast<EnclosingBox*>(check);

    buffer.push_back(obj);
    DisplayObj = obj;

    setSize(100,100); //Do not remove
    hHide = false;
    vHide = false;
    vScroll.setBorderSize(DefaultScrollFrameWidth);
    hScroll.setBorderSize(DefaultScrollFrameWidth);

    DisplayObj->IScrollable::AttachCallBackWindow(this);

}

#if(NEW_DEBUG)
template<typename T>
ScrollableWindow<T> :: ScrollableWindow(T & displayObj) : vScroll(internal::Vertical), hScroll(internal::Horizontal),ScrollThickness(DefaultScrollBarThickness), hHide(false),
vHide(false), DisplayObj(displayObj)
{
    T * check = 0;
    IScrollable * ScrollableCheck = static_cast<IScrollable*>(check);
    EnclosingBox * BoxCheck = static_cast<EnclosingBox*>(check);

    /*
    if ( displayObj == 0 )
    {
        buffer.reset(new T());
        DisplayObj = buffer.get();
    }
    */

    setSize(100,100); //Do not remove
    hHide = false;
    vHide = false;
    vScroll.setBorderSize(DefaultScrollFrameWidth);
    hScroll.setBorderSize(DefaultScrollFrameWidth);

    DisplayObj->IScrollable::AttachCallBackWindow(this);

}
#endif


template<typename T>
void ScrollableWindow<T> :: SetSizeIfFixed()
{

    DisplayObj->Configure();

    hScroll.setSize( DisplayObj->getWidth() - 2 * DefaultScrollFrameWidth, ScrollThickness);
    vScroll.setSize(ScrollThickness, DisplayObj->getHeight() - 2 * DefaultScrollFrameWidth + hScroll.getHeight());

    setInternalHeight( DisplayObj->getHeight() + hScroll.getHeight() );
    setInternalWidth( DisplayObj->getWidth() + vScroll.getWidth() );

}

template<typename T>
void ScrollableWindow<T> :: SetSize()
{
    /*
    if ( ScrollableEntityTrait<T>::CanAdaptToWindow  )
    {
        std::cerr << "Cannot set size for window holding the current type" << std::endl;
        return;
    }
    */    

    if ( !DisplayObj->isResizeable() )
    {
        SetSizeIfFixed();
        return;
    }

    float widthOffset = vHide ?  0 : vScroll.getWidth();
    float heightOffset = hHide ? 0 : hScroll.getHeight();

    DisplayObj->setSize( getInternalWidth() - widthOffset, getInternalHeight() - heightOffset);

    vScroll.setSize(ScrollThickness, getInternalHeight() - 2*vScroll.getBorderSize() );
    hScroll.setSize( getInternalWidth() - 2*hScroll.getBorderSize() - vScroll.getWidth(), ScrollThickness );

}

template<typename T>
void ScrollableWindow<T> :: SetPosition()
{
    const sf::Vector2f & pos = getInternalPosition();
    DisplayObj->setPosition( pos.x,pos.y );
    vScroll.setPosition(pos.x + getInternalWidth() - vScroll.getWidth(), pos.y );
    hScroll.setPosition( pos.x, pos.y + getInternalHeight() - hScroll.getHeight() );

}

template<typename T>
void ScrollableWindow<T> :: setScrollBarColor(sf::Color _color)
{
    vScroll.setBorderColor(_color);
    hScroll.setBorderColor(_color);
}

template<typename T>
void ScrollableWindow<T> :: setScrollStoneColor(sf::Color _color)
{
    vScroll.setStoneColor(_color);
    hScroll.setStoneColor(_color);
}

template<typename T>
void ScrollableWindow<T> :: ResizeWindow()
{    
    setInternalHeight( DisplayObj->getHeight() + hScroll.getHeight() );
    setInternalWidth( DisplayObj->getWidth() + vScroll.getWidth() );
}

template<typename T>
void ScrollableWindow<T> :: SetUpNonAdaptableDisplay()
{

    if ( isConfigured() ) return;
    DisplayObj->setBorderSize(0);

    setMarginSize(0);

    DisplayObj->windowFlag = true;
    DisplayObj->WindowDisplay();
    DisplayObj->windowFlag = false;

    hScroll.setSize( DisplayObj->getWidth() - 2 * DefaultScrollFrameWidth, ScrollThickness);

    vScroll.setSize(ScrollThickness, DisplayObj->getHeight() - 2 * DefaultScrollFrameWidth + hScroll.getHeight());

    hScroll.Configure();
    vScroll.Configure();

    setInternalHeight( DisplayObj->getHeight() + hScroll.getHeight() );
    setInternalWidth( DisplayObj->getWidth() + vScroll.getWidth() );

    SetPosition();

    std::cout << "Inside Scroll Window : Display Size" <<  DisplayObj->getVerticalDisplaySize() << "   Vertical Page Size   " << DisplayObj->getVerticalPageSize() << std::endl;


    vScroll.setPageSize( DisplayObj->getVerticalPageSize() );
    vScroll.setDisplaySize(DisplayObj->getVerticalDisplaySize() );

    hScroll.setPageSize( DisplayObj->getHorizontalPageSize());
    hScroll.setDisplaySize( DisplayObj->getHorizontalDisplaySize());

    if ( !DisplayObj->isConfigured())
    std::cout << "Display Objcet ScrollBar not configured" << std::endl;

}

/*
template<typename T>
void ScrollableWindow<T> :: SetUpAdaptableDisplay()
{

    if ( isConfigured() ) return;
    DisplayObj->setBorderSize(0);
    setMarginSize(0);

    SetSize();
    SetPosition();

    DisplayObj->windowFlag = true;
    DisplayObj->WindowDisplay();
    DisplayObj->windowFlag = false;

    hScroll.Configure();
    vScroll.Configure();

    std::cout << "Inside Scroll Window : Display Size" <<  DisplayObj->getVerticalDisplaySize() << "   Vertical Page Size   " << DisplayObj->getVerticalPageSize() << std::endl;


    vScroll.setPageSize( DisplayObj->getVerticalPageSize() );
    vScroll.setDisplaySize(DisplayObj->getVerticalDisplaySize() );

    hScroll.setPageSize( DisplayObj->getHorizontalPageSize());
    hScroll.setDisplaySize( DisplayObj->getHorizontalDisplaySize());

    if ( !DisplayObj->isConfigured())
    std::cout << "Display Objcet ScrollBar not configured" << std::endl;

}
*/

/*
template<typename T>
void ScrollableWindow<T> :: SetUpDisplay()
{
    //setupdisplay<ScrollableEntityTrait<T>::CanAdaptToWindow>();
    //above won't work because function specialization doesn't work
    //Anywa the use of Trait  here is just rubbish.
    if ( ScrollableEntityTrait<T>::CanAdaptToWindow ) SetUpAdaptableDisplay();
    else SetUpNonAdaptableDisplay();
}
*/


template<typename T>
void ScrollableWindow<T> :: AttachDisplay(T * obj)
{
    if ( obj == 0 ) throw std::runtime_error("Cannot attach null pointer to the window");
    buffer.push_back(obj);

    DisplayObj = obj;
    DisplayObj->IScrollable::AttachCallBackWindow(this);
    SetSize();
}

template<typename T>
T * ScrollableWindow<T> :: DetachDisplay()
{
    auto iter = std::find_if(buffer.begin(), buffer.end(), [this] (T * obj)->bool
    {
            if ( obj == DisplayObj ) return true;

});

    T * p = 0;
    if ( iter != buffer.end() )
    {
        T * p = *iter;
        buffer.erase(iter);
    }

    DisplayObj = buffer.empty() ? dummy : buffer.front();

    setUp = false;
    return p;
}


template<typename T>
void ScrollableWindow<T> :: SetUpDisplay()
{

    //This needs to be changed - incorrect usage of traits, but the work around is bigger pain
    if ( !ScrollableEntityTrait<T>::CanAdaptToWindow  )
    {
        SetUpNonAdaptableDisplay();
        return;
    }

    if ( isConfigured() ) return;
    DisplayObj->setBorderSize(0);
    setMarginSize(0);

    SetSize();
    SetPosition();

    DisplayObj->windowFlag = true;
    DisplayObj->WindowDisplay();
    DisplayObj->windowFlag = false;

    hScroll.Configure();
    vScroll.Configure();

    std::cout << "Inside Scroll Window : Display Size" <<  DisplayObj->getVerticalDisplaySize() << "   Vertical Page Size   " << DisplayObj->getVerticalPageSize() << std::endl;


    vScroll.setPageSize( DisplayObj->getVerticalPageSize() );
    vScroll.setDisplaySize(DisplayObj->getVerticalDisplaySize() );

    hScroll.setPageSize( DisplayObj->getHorizontalPageSize());
    hScroll.setDisplaySize( DisplayObj->getHorizontalDisplaySize());

    if ( !DisplayObj->isConfigured()) DisplayObj->Configure();

}



template<typename T>
void ScrollableWindow<T> :: setVerticalDisplaySize(unsigned int _dispSize)
{
    DisplayObj->setVerticalDisplaySize(_dispSize);
    vScroll.setDisplaySize(_dispSize);
}

template<typename T>
void ScrollableWindow<T> :: setHorizontalDisplaySize(unsigned int _dispSize)
{
    DisplayObj->setHorizontalDisplaySize(_dispSize);
    hScroll.setDisplaySize(_dispSize);
}

template<typename T>
void ScrollableWindow<T> :: ConfigureDisplayObject()
{
    DisplayObj->Configure();
}

template<typename T>
void ScrollableWindow<T> :: ConfigureVerticalScrollBar()
{
    vScroll.setPageSize( DisplayObj->getVerticalPageSize() );
    vScroll.setDisplaySize(DisplayObj->getVerticalDisplaySize() );
    vScroll.Configure();
}

template<typename T>
void ScrollableWindow<T> :: ConfigureHorizontalScrollBar()
{
    hScroll.setPageSize( DisplayObj->getHorizontalPageSize());
    hScroll.setDisplaySize( DisplayObj->getHorizontalDisplaySize());
    hScroll.Configure();
}

template<typename T>
void ScrollableWindow<T> :: ResetVerticalScrollBar()
{
    vScroll.reset();
}

template<typename T>
void ScrollableWindow<T> :: ResetHorizontalScrollBar()
{
    hScroll.reset();
}

template<typename T>
void ScrollableWindow<T> :: ScrollUp(int offset)
{    
   DisplayObj->scrollUp(offset);
   vScroll.setPageSize( DisplayObj->getVerticalPageSize() );
   vScroll.setDisplaySize( DisplayObj->getVerticalDisplaySize() );
   vScroll.scroll(offset, ScrollBar::up);
}

template<typename T>
void ScrollableWindow<T> ::  ScrollDown(int offset)
{
    DisplayObj->scrollDown(offset);
    vScroll.setPageSize( DisplayObj->getVerticalPageSize() );
    vScroll.setDisplaySize( DisplayObj->getVerticalDisplaySize() );
    vScroll.scroll(offset, ScrollBar::down);
}


template<typename T>
void ScrollableWindow<T> :: ScrollRight(int offset)
{    
    DisplayObj->scrollRight(offset);
    hScroll.setPageSize( DisplayObj->getHorizontalPageSize() );
    hScroll.setDisplaySize( DisplayObj->getHorizontalDisplaySize() );
    hScroll.scroll(offset, ScrollBar::right);
}

template<typename T>
void ScrollableWindow<T> ::  ScrollLeft(int offset)
{

    DisplayObj->scrollLeft(offset);
    hScroll.setPageSize( DisplayObj->getHorizontalPageSize() );
    hScroll.setDisplaySize( DisplayObj->getHorizontalDisplaySize() );
    hScroll.scroll(offset, ScrollBar::left);
}


template<typename T>
void ScrollableWindow<T> :: CreateVerticalPageSpace(int step)
{

    DisplayObj->changeVerticalPageSpace(step);
    ConfigureVerticalScrollBar();
    ScrollDown(step);
}

template<typename T>
void ScrollableWindow<T> :: CreateHorizontalPageSpace(int step)
{
    DisplayObj->changeHorizontalPageSpace(step);
    ConfigureHorizontalScrollBar();
    ScrollRight(step);
}


template<typename T>
void ScrollableWindow<T> :: Zoom(float scale)
{

    DisplayObj->zoom(scale);
    ConfigureVerticalScrollBar();
    ConfigureHorizontalScrollBar();

}


template<typename T>
void ScrollableWindow<T> :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    if ( !vScroll.isConfigured())
    std::cout << "Vertical ScrollBar not configured" << std::endl;

    if ( !hScroll.isConfigured())
    std::cout << "Horizontal ScrollBar not configured" << std::endl;

    if ( !DisplayObj->isConfigured())
    std::cout << "Display Object not configured" << std::endl;

    if ( !this->isConfigured())
        std::cout << "Window not configured " << std::endl;

    this->EnclosingBox::draw(target,states);

    if ( !vHide ) target.draw(vScroll);
    if ( !hHide ) target.draw(hScroll );
    target.draw(*DisplayObj);
}


#include "window.inl"





}//EON

#ifndef BUTTON_H
#define BUTTON_H
#include "Utility.h"
#include <memory>
#include <iostream>

#include <memory>
#include <string>
#include <map>
#include <utility>
#include "buttonevent.h"
#include "button.h"
#include "Traits.h"

#if(BUTTON_3)
#include "buttonicons.h"
#endif

#if(BUTTON_2)
#include<boost/tuple/tuple.hpp>
#endif

#if(BUTTON_4)
#include "buttonicons.h"
#include "buttontypes.h"
#include "Properties.h"
#endif


//Useless
 /*
namespace sf {
class Texture;
}
*/

namespace GUI
{

/*
template<>
struct GUITrait
{
    typedef BUTTON::ButtonType GUIType;
};
*/

class IButton :  public sf::Sprite
{
public:
    //static const internal::GUI_Type gui_Type = internal::Button;

protected:
    bool active;    


public:
    virtual ~IButton() {}

    virtual void Press()=0;
    virtual void Release()=0;

    /*
     * NOTE: This should be declared on a base class above this like IVisitable. But it stays here  for now. Every gui entity must define this.
     */
    virtual const internal::GUI_Type getGUIType() const=0;
};


template<typename T> class Button;

namespace internal
{

template<typename T>
struct HasSetSize< GUI::Button<T>>
{
    static const bool value = false;
};

template<typename T>
struct HasText<GUI::Button<T> >
{
    static const bool value = false;
};


template<typename T>
struct HasSetFillColor<GUI::Button<T> >
{
    static const bool value = false;
};


template<typename T>
struct IsDerivedFromEnclosingBox<GUI::Button<T>>
{
    static  const bool value = false;
};


}

//Add Interfaces along the way
/*
class xButton : public IButton, public IHover, public IDrag
{

public:
    xButton();
    virtual ~xButton() {}
};
*/


template<typename T>
class Button :  public IButton /*, public xButton*/
{

public:
    static const internal::GUI_Type gui_Type = internal::Button;

private:
    T textureProp;
public:
    EventHandler buttonEvents;


    //Copy constructor and Assignment operator are private to avoid copying. Use Factory to get buttons
    Button(const Button<T> & _button) {}
    Button<T> & operator=(const Button<T> & obj) {}
protected:
    sf::Texture * _button;
    sf::Texture * _pressedButton;
    bool _pressed;

    void LoadButtonTexture(sf::Texture * tex) { _button = tex; }
    void LoadPressedButtonTexture(sf::Texture * tex) { _pressedButton = tex; }


public:
    Button();
    void setSize(float width, float height)
    {
        std::cout << "Cannot set size on Button  " << std::endl;
    }

    virtual void Press();
    virtual void Release();
    virtual void activate();
    virtual void deactivate();
    virtual const internal::GUI_Type getGUIType() const { return gui_Type; }

};

typedef Button<PlainTexture> PlainButton;


#if(DEPRECATED)
//TextButton complicates the button. It will be very hard to keep track //of both the button and the text on it when properties are applied.
//It is easier to have sprites with text on them.

class TextButton : public sf::Drawable
{
    
    
    
    PlainButton button;
    sf::Font * font;
    sf::Text buttonText;


protected:
    void AlignText();

public:
    TextButton() : button(), font(0), buttonText() {}
    TextButton(const char * _text, const char * _fontType, sf::Color _textColor);

    void setTextFont(const char * fontType);
    void setText(const char * _text);
    void setTextColor(sf::Color textColor);
    const sf::Font & getFont() { return *font;}


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
#endif



#if(DEPRECATED)
//Download Button with icons from http://buttonoptimizer.com/#
//Button should be simple sprite not complicated - Having icon as a
//separate sprite requires tracking the icon along with the button
//for every action like dragging, zoomin. Time to phase this out.

template<typename Icon>
class IconButton : public PlainButton
{
private:
    Icon * icon;
    mutable bool setIcon;

public:
    IconButton();
    ~IconButton();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
#endif





#if(BUTTON_3)

template<typename Icon>
class Button : public IButton
{
private:
    static const char * ImageFile;
    Icon * icon;

    mutable bool setIcon;


protected:
    /*
     * Set the texture rectangle to focus on the presed-button
     */
    virtual void ButtonPress();
    //Set the texture rectangle to focus on the released-button
    virtual void ButtonRelease();
    //Adjust icon to fit correctly on button
    //virtual void setIconPosition();

public:
    Button();
    ~Button();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

/////////////Specialization for void Icon  //////////////

template<>
class Button<void> : public IButton
{
private:
    static const char * ImageFile;

protected:
    //Set the texture rectangle to focus on the presed-button
    virtual void ButtonPress();

    //Set the texture rectangle to focus on the released-button
    virtual void ButtonRelease();


public:
    Button();
    virtual ~Button() {}

};


typedef Button<void> PlainButton;
typedef Button<ArcIcon> ArcIconButton;
typedef Button<AttachmentIcon> AttachmentIconButton;
typedef Button<BoldIcon> BoldIconButton;
typedef Button<CircleIcon> CircleIconButton;
typedef Button<FileIcon> FileIconButton;
typedef Button<FontIcon> FontIconButton;
typedef Button<HomeIcon> HomeIconButton;
typedef Button<ItalicIcon> ItalicIconButton;
typedef Button<LineIcon> LineIconButton;
typedef Button<PencilIcon> PencilIconButton;
typedef Button<PickColorIcon> PickColorIconButton;
typedef Button<PolygonIcon> PolygonIconButton;
typedef Button<SearchIcon> SearchIconButton;
typedef Button<SquareIcon> SquareIconButton;
typedef Button<TrashIcon> TrashIconButton;


#endif


EON
#endif // BUTTON_H

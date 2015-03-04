#ifndef BUTTON_H
#define BUTTON_H
#include "Utility.h"
#include <memory>
#include <iostream>

#include <memory>
#include <string>
#include <map>
#include <utility>



//#define EON }
//#define EON }

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

class IButton : public sf::Sprite
{

protected:

    sf::Texture * _button;
    sf::Texture * _pressedButton;
    bool _pressed;

protected:
    bool active;

    void LoadButtonTexture(sf::Texture * tex) { _button = tex; }
    void LoadPressedButtonTexture(sf::Texture * tex) { _pressedButton = tex; }

    virtual void ButtonPress()=0;
    virtual void ButtonRelease()=0;

public:
    IButton();
    virtual ~IButton() {}
    void Press();
    void Release();
    virtual void activate();
    virtual void deactivate();

};

#if(BUTTON_4)


//Add Interfaces along the way
class xButton : public IButton, public IHover, public IDrag
{

public:
    xButton();
    virtual ~xButton() {}
};



template<typename T>
class Button : public xButton
{
private:
    T textureProp;

public:
    Button();
    void ButtonPress() {}
    void ButtonRelease() {}

};

typedef Button<PlainTexture> PlainButton;

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



#if(BUTTON_2)

class IButton : public sf::Sprite
{

private:
    sf::Texture  _button;
    sf::Texture  _pressedButton;
    bool _pressed;


protected:
void LoadButtonTexture(sf::Texture & tex) { _button = tex; }
void LoadPressedButtonTexture(sf::Texture & tex) { _pressedButton = tex; }


virtual void ButtonPress()=0;
virtual void ButtonRelease()=0;


public:
    IButton();
    virtual ~IButton() {}
    void Press();
    void Release();

};





class ButtonIcons : public sf::Sprite
{
private:
   static const char* ImageFiles[];
   sf::Texture * _icon;

   virtual void setTextureRegion(boost::tuple<int,int,int,int> & rect)=0;

public:
    ButtonIcons(int ImageIndex = 1);
    void Load(boost::tuple<int,int,int,int> & rect)
    {
        setTextureRegion(rect);
        std::cout << "Setting Texture region  for icon" << std::endl;
    }
};


struct SearchIcon : public ButtonIcons
{
    SearchIcon() : ButtonIcons(0) {}
    void setTextureRegion(boost::tuple<int,int,int,int> & rect)
    {
        int p = rect.get<0>();
        int q = rect.get<1>();
        int r = rect.get<2>();
        int s = rect.get<3>();

        this->setTextureRect(sf::IntRect(p,q,r,s) );
    }
};



class NormalButton : public IButton
{
private:
    static const char * ImageFile;
protected:
    //Set the texture rectangle to focus on the presed-button
    virtual void ButtonPress();
    //Set the texture rectangle to focus on the released-button
    virtual void ButtonRelease();
    SearchIcon * icon;

public:
    NormalButton(int i = 12,int j = 105, int k = 30 , int l = 30);
    ~NormalButton() {}

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        icon->setPosition(this->getPosition());
        //target.draw(*this);
        //this->draw(target, states);
        sf::Sprite p = static_cast<sf::Sprite>(*this);
        target.draw(p);
        target.draw(*icon);
//        target.draw(*icon);
    }

};

#endif



#if(BUTTON_1)
class IButton : public sf::Drawable
{
    typedef sf::Sprite* spritePtr;

public:
    bool _pressed;


protected:
    spritePtr _button;
    spritePtr _pressedButton;


protected:
    void LoadButton() { _button = new sf::Sprite(); }
    void LoadPressedButton() { _pressedButton = new sf::Sprite(); }


public:
    IButton() :_pressed(false), _button(nullptr), _pressedButton(nullptr) {}

    virtual ~IButton()
    {
        if ( _button ) delete _button;
        if ( _pressedButton ) delete _pressedButton;
    }

    //virtual void Click() = 0;


};


class NormalButton : public IButton
{

private:
    sf::Texture _bTexture;
    static const char * ImageFile;

public:
    NormalButton();
    ~NormalButton() {}
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif


EON
#endif // BUTTON_H

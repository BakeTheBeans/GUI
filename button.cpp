#include "button.h"
#include "define.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace GUI
{
IButton :: IButton()
{
    _pressed = false;
    active = true;
}

void IButton ::  Press()
{
    if (active)
    {
        this->setTexture(*_pressedButton);
        ButtonPress();
    }
}

void IButton :: Release()
{
    if(active)
    {
        this->setTexture(*_button);
        ButtonRelease();
    }
}

void IButton :: activate()
{
    active = true;
    Release();

}


void IButton :: deactivate()
{
    Press();
    active = false;
}


xButton :: xButton() : IButton(),  IHover( *static_cast<sf::Sprite*>(this) ), IDrag(*static_cast<sf::Sprite*>(this) )
{

}


#if(BUTTON_4)
template<typename T>
Button<T> :: Button() : xButton(),  textureProp()
{
    ButtonTexture * check = static_cast<T*>(0);

    sf::Texture *pTexture = 0;
    pTexture = textureProp.getButtonTexture();
    LoadButtonTexture(pTexture);

    sf::Texture *qTexture = 0;
    qTexture = textureProp.getPressedButtonTexture();
    LoadPressedButtonTexture(qTexture);

    sf::Texture *hTexture = textureProp.getHoverButtonTexture();
    SetUpHover(pTexture, hTexture);
    this->setTexture(*_button);
    this->setTextureRect(sf::IntRect(0,0,204,74));
}


#include "button.inl"

template<typename Icon>
IconButton<Icon> :: IconButton() : PlainButton(),  icon(0)
{
    //Throw compiler error if Icon is not derived from ButtonIcons
    ButtonIcons * p = static_cast<Icon*>(0);

    this->setTexture(*_button);

    icon = new Icon();
    icon->Load();
    setIcon = false;

}

template<typename Icon>
IconButton<Icon> :: ~IconButton()
{
    if ( icon != 0 ) delete icon;
}

template<typename Icon>
void IconButton<Icon> :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    auto ConfigureIcon = [&] () -> void
    {
            auto buttonbounds = this->getGlobalBounds();
            auto iconBounds = icon->getGlobalBounds();
            float x = buttonbounds.width/(3*iconBounds.width);
            float y = buttonbounds.height/iconBounds.height;

            auto pos = this->getPosition();
            icon->setPosition(pos.x + buttonbounds.width/3 , pos.y + 2);
            sf::Color buttonColor = this->getColor();
            icon->setColor(sf::Color(buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a+100));
            icon->scale(0.88*x,0.88*y);

    };


    if (!setIcon)
    {
        ConfigureIcon();
        setIcon = !setIcon;
    }


    sf::Sprite p = static_cast<sf::Sprite>(*this);
    target.draw(p);
    target.draw(*icon);

}

template class IconButton<ArcIcon>;
#endif

#if(BUTTON_3)

template<typename Icon>
const char * Button<Icon>::ImageFile = "button.png";

const char * Button<void>::ImageFile = "button.png";
#endif


#if(BUTTON_3)
template<typename Icon>
Button<Icon> :: Button()
{
    //Throw compiler error if Icon is not derived from ButtonIcons
    //ButtonIcons * p = static_cast<Icon>(0);

#if(TEXTURE_2)
    TextureManager::RegisterGuiComponent(normalButton,ImageFile);
    LoadButtonTexture(TextureManager::getTexture(normalButton));
    LoadPressedButtonTexture(TextureManager::getTexture(normalButton));
#else

    LoadButtonTexture(ResourceManager::getTexture("ButtonImage_1"));
    LoadPressedButtonTexture(ResourceManager::getTexture("ButtonImage_1"));
#endif
    this->setTexture(*_button);
    this->setTextureRect(BUTTON_RELEASE);

    icon = new Icon();
    icon->Load();
    setIcon = false;
}

template<typename Icon>
Button<Icon> :: ~Button()
{
    if ( icon != 0 ) delete icon;
}

template<typename Icon>
void Button<Icon> :: ButtonPress()
{
    this->setTextureRect(BUTTON_PRESS);
}

template<typename Icon>
void Button<Icon> :: ButtonRelease()
{
    this->setTextureRect(BUTTON_RELEASE);
}


template<typename Icon>
void Button<Icon> :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    auto ConfigureIcon = [&] () -> void
    {
            auto buttonbounds = this->getGlobalBounds();
            auto iconBounds = icon->getGlobalBounds();
            float x = buttonbounds.width/(3*iconBounds.width);
            float y = buttonbounds.height/iconBounds.height;

            auto pos = this->getPosition();
           icon->setPosition(pos.x + buttonbounds.width/3  , pos.y);
            sf::Color buttonColor = this->getColor();
            icon->setColor(sf::Color(buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a+100));
            icon->scale(x,y);


    };


    if (!setIcon)
    {        
        ConfigureIcon();
        setIcon = !setIcon;
    }

    sf::Sprite p = static_cast<sf::Sprite>(*this);
    target.draw(p);
    target.draw(*icon);

}

//////////////////void Icon specialization ////////////


Button<void> :: Button()
{
    //Throw compiler error if Icon is not derived from ButtonIcons
    //ButtonIcons * p = static_cast<Icon>(0);

#if(TEXTURE_2)
    TextureManager::RegisterGuiComponent(normalButton,ImageFile);
    LoadButtonTexture(TextureManager::getTexture(normalButton));
    LoadPressedButtonTexture(TextureManager::getTexture(normalButton));

#else
    //ResourceManager::RegisterGuiComponent("ButtonImage",ImageFile);
    LoadButtonTexture(ResourceManager::getTexture("ButtonImage_1"));
    LoadPressedButtonTexture(ResourceManager::getTexture("ButtonImage_1"));
#endif
    this->setTexture(*_button);
    this->setTextureRect(BUTTON_RELEASE);

}

void Button<void> :: ButtonPress()
{
    DEBUG_MESSAGE
    this->setTextureRect(BUTTON_PRESS);
}

void Button<void> :: ButtonRelease()
{
    this->setTextureRect(BUTTON_RELEASE);
}

//button.inl - all the template argument definitions are provided
#include "button.inl"

#endif//End of Button_Test_3


#if(BUTTON_2)
const char * NormalButton::ImageFile = "button.png";
const char *ButtonIcons::ImageFiles[] =
{
        "button_icons_1.png",
        "button_icons_2.jpg"
};


IButton :: IButton()
{
    _pressed = false;
    this->setTexture(_button);

}

void IButton ::  Press()
{
    this->setTexture(_pressedButton);
    ButtonPress();
}

void IButton :: Release()
{
    this->setTexture(_button);
    ButtonRelease();
}



NormalButton :: NormalButton(int i,int j, int k, int l)
{
    icon = new SearchIcon();
    auto foo = boost::tuples::make_tuple<int,int,int,int>(i,j,k,l);
    icon->Load(foo);
    TextureManager::RegisterGuiComponent(normalButton,ImageFile);
    LoadButtonTexture(TextureManager::getTexture(normalButton));
    LoadPressedButtonTexture(TextureManager::getTexture(normalButton));
    this->setTextureRect(sf::IntRect(0,108,100,35));
    icon->setColor(sf::Color::Blue);

}

void NormalButton :: ButtonPress()
{
    this->setTextureRect(sf::IntRect(105,145,100,35));
}


void NormalButton :: ButtonRelease()
{
    this->setTextureRect(sf::IntRect(0,108,100,35));
}


ButtonIcons :: ButtonIcons(int imageIndex) : _icon(0)
{
    TextureManager::RegisterGuiComponent(buttonIcons, ImageFiles[imageIndex]);
    _icon = &TextureManager::getTexture(buttonIcons);
    this->setTexture(*_icon);

}

#endif







#if(BUTTON_1)
NormalButton :: NormalButton() : IButton()
{

    IButton::LoadButton();
    IButton::LoadPressedButton();
    TextureManager::getTextureManager().RegisterGuiComponent(ComponentType::normalButton, ImageFile);

    _bTexture = TextureManager::getTextureManager().getTexture(ComponentType::normalButton);

    _button->setTexture(_bTexture);
    _pressedButton->setTexture(_bTexture);
    _button->setTextureRect(sf::IntRect(0,108,100,35));
    _pressedButton->setTextureRect(sf::IntRect(105,145,100,35));

    //_button->setPosition(200,200);
    //_pressedButton->setPosition(200,200);
}


void NormalButton :: draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    if (!_pressed) target.draw(*IButton::_button);
    else target.draw(*IButton::_pressedButton);
}
#endif



EON

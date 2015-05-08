#include "button.h"
#include "define.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace GUI
{

#if(!OLD_DEBUG)
#else
xButton :: xButton() : IButton(),  IHover( *static_cast<sf::Sprite*>(this) ), IDrag(*static_cast<sf::Sprite*>(this) )
{

}
#endif

template<typename T>
Button<T> :: Button() : IButton(), /*xButton(), */ textureProp()
{
    ButtonTexture * check = static_cast<T*>(0);
    _pressed = false;
    active = true;

    sf::Texture *pTexture = 0;
    pTexture = textureProp.getButtonTexture();
    LoadButtonTexture(pTexture);

    if ( T::isPressable )
    {
        sf::Texture *qTexture = 0;
        qTexture = textureProp.getPressedButtonTexture();
        LoadPressedButtonTexture(qTexture);
    }

#if(!OLD_DEBUG)

#else
    if (T::isHoverable )
    {
        sf::Texture *hTexture = textureProp.getHoverButtonTexture();
        SetUpHover(pTexture, hTexture);

    }
#endif

    this->setTexture(*_button);
    this->setTextureRect(sf::IntRect(0,0,204,74));
}


template<typename T>
void Button<T> :: Press()
{
    if (active)
    {
        this->setTexture(*_pressedButton);
        buttonEvents.FireEvents();
    }

}

template<typename T>
void Button<T> :: Release()
{
    if(active)
    {
        this->setTexture(*_button);
    }
}

template<typename T>
void Button<T> :: activate()
{
    active = true;
    Release();

}

template<typename T>
void Button<T> :: deactivate()
{
    Press();
    active = false;
}




#include "button.inl"


/*
 *
 * Do not use Text Button

TextButton :: TextButton(const char * _text, const char * _fontType, sf::Color _textColor) : button(),  font(0) , buttonText()
{
    if ( _text == 0 || _fontType == 0)
        throw "No Text or Font type provided for TextButton";

    if (! (font = GUI::ResourceManager::getResource<GUI::Font>(_fontType)) ) throw "No Font";

    button.scale(BUTTON_SCALE_X,BUTTON_SCALE_Y);
    buttonText.setFont(*font);
    buttonText.setColor(_textColor);
    buttonText.setString(std::string(_text));

    AlignText();
}


void TextButton :: AlignText()
{
    int charSize = 18;
    buttonText.setCharacterSize(charSize);

    double xdiff=0, ydiff=0;
    xdiff = button.getGlobalBounds().width - buttonText.getGlobalBounds().width;
    ydiff = button.getGlobalBounds().height - buttonText.getGlobalBounds().height;

    sf::Vector2f buttonPos  = button.getPosition();
    buttonText.setPosition( buttonPos.x+10, buttonPos.y+2);
}

void TextButton :: setTextFont(const char * _fontType)
{
    font = GUI::ResourceManager::getResource<GUI::Font>(_fontType);

}

void TextButton :: setText(const char * _text)
{
    buttonText.setString(std::string(_text));
}

void TextButton :: setTextColor(sf::Color textColor)
{
    buttonText.setColor(textColor);
}


void TextButton :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(button);
    target.draw(buttonText);

}

*/




#if(DEPRECATED)

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

EON

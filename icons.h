#ifndef ICONS_H
#define ICONS_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Utility.h"
#include "Traits.h"
#include "buttonevent.h"

namespace GUI {


class Icon : public sf::Drawable
{
    friend class IconBuilder;
    sf::Sprite icon;
    sf::Texture * iconTexture;
public:
    EventHandler iconEvents;

protected:
    Icon() : icon(), iconTexture(0) {}
public:
    virtual ~Icon() {}

    void setPosition(int posX, int posY)
    {
        icon.setPosition(posX,posY);
    }

    void scale(float x, float y)
    {
        icon.scale(x,y);
    }

    void setColor(sf::Color color)
    {
       icon.setColor(color);
    }

   void draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
       target.draw(icon);
   }


};


class IconBuilder
{
    static const char * ImageName;

    virtual sf::Texture * getTexture();
    //virtual sf::Texture * getPressedButtonTexture();
    //virtual sf::Texture * getHoverButtonTexture();
    IconBuilder() {}

public:

    template <typename T> static Icon * getIcon()
    {
        Icon * p = new Icon();
        p->iconTexture = ResourceManager::getResource<Texture>( T::getImageName() );
        p->icon.setTexture( *(p->iconTexture) );
        return p;
    }


};


//class UpIcon : public Icon

struct UpIcon
{
    static const char * getImageName() { return "UpIcon";}
};

namespace internal
{

template<>
struct HasSetSize<Icon>
{
    static const bool value = false;
};

template<>
struct IsScalable<Icon>
{
    static const bool value = true;
};

template<>
struct HasSetFillColor<Icon>
{
    static const bool value = false;
};


}


}//EON
#endif // ICONS_H

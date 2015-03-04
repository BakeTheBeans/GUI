#ifndef PROPERTIES_H
#define PROPERTIES_H
#include "define.h"
#include <utility>

#define ObjectContainsMouseCursor(self,mousePos) self.getGlobalBounds().contains( (mousePos.x - window->getPosition().x), (mousePos.y - window->getPosition().y) )

#define NAME std::cout << Type << std::endl;



namespace sf {
    class Sprite;
    class Texture;
    class Window;
}

namespace GUI {


struct Properties
{

    bool hover;
    bool drag;
    bool save;
    bool zoom;
};



class IHover
{
static constexpr const char * Type = "Property : HOVER";
private:

    sf::Sprite & self;
    const sf::Texture * hoverTexture;
    const sf::Texture * originalTexture;
    bool isHoverTextureSet;
    bool mode;

protected:
    void SetUpHover(sf::Texture * originalTexture, sf::Texture * _hover);


public:
    IHover(sf::Sprite & derived) : self(derived), hoverTexture(0), originalTexture(0), isHoverTextureSet(false),  mode(false)
    { }

    virtual ~IHover()
    {
        hoverTexture = 0;
        originalTexture = 0;
    }

    void EnableHovering() { mode = true; }
    void DisableHovering() { mode = false; }
    void Hover(sf::Window * window);
};



class IDrag
{
static constexpr const char * Type = "Property : DRAG";
    enum CouplingState
    {
        Capture,
        Release
    };


private:
    sf::Sprite & self;
    bool dragmode;

    typedef std::pair<int,int> Position;

    Position prevMousePosition;
    const int PIXELS_MOVED = 0;
    const int DELAY = 10;
protected:

    IDrag( sf::Sprite & derived) : self(derived), dragmode(false), prevMousePosition(-1,-1)
    {  }


    CouplingState CheckMouseCoupling();
    void RecordMousePosition(sf::Window * window);

public:
    virtual ~IDrag() {}
    void EnableDragging() {  dragmode = true; }
    void DisableDragging() { dragmode = false; }
    void Drag(sf::Window * window);


};



EON
#endif // PROPERTIES_H

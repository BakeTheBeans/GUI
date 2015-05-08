#ifndef DIRECTORYMENU_H
#define DIRECTORYMENU_H
#include "define.h"
#include "interfaces.h"
#include "directorymenupage.h"
#include "Utility.h"
#include <memory>
#include <string>
#include "ComplexObject.h"
//#include "define.h"

namespace sf {
class RenderTarget;
}

namespace GUI {

#if(NEW_DEBUG)
class DirectoryMenu : /*public EnclosingBox, */public internal::ComplexObject
#else
class DirectoryMenu : public EnclosingBox
#endif
{

static const float DefaultWidth;
static const float DefaultHeight;
static const float DefaultBorderSize;


private:    
    std::map<std::string, MenuTiles>  TileMap;

    DirectoryMenuPage menuPage;
    ScrollableWindow<DirectoryMenuPage> * menuPageWindow;

    //std::map<std::string,IButton*> buttons;
    GUI::Button<GUI::CancelTexture> CancelButton;
    GUI::Button<GUI::FileTexture> FileButton;

private:
virtual void SetSize(){}

protected:
//void AddButton(IButton * _button) {}
#if(NEW_DEBUG)
void ConfigureSubElements();
std::string getXmlTagName() { return "DirectoryMenu"; }
#endif

public:
    DirectoryMenu();
    DirectoryMenu(float width, float height, float _borderSize = DefaultBorderSize);
    void setSize(float _width, float _height )
    {
        throw "Cannot set size for DirectoryMenu";
    }
#if(NEW_DEBUG)
    //void SetUpDisplayFromXml();
#endif
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};




} //EON

#endif // DIRECTORYMENU_H


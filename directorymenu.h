#ifndef DIRECTORYMENU_H
#define DIRECTORYMENU_H
#include "define.h"
#include "interfaces.h"
#include "directorymenupage.h"
#include "Utility.h"
#include <memory>
#include <string>
#include "ComplexObject.h"
//#include "buttonicons.h"
//#include "define.h"
#include "icons.h"

namespace sf {
class RenderTarget;
}

namespace GUI {


class DirectoryMenu : public internal::ComplexObject, public ICallBackEventHandler
{

static const float DefaultWidth;
static const float DefaultHeight;
static const float DefaultBorderSize;


private:    
    std::map<std::string, MenuTiles>  TileMap;

    DirectoryMenuPage menuPage;
    ScrollableWindow<DirectoryMenuPage> * menuPageWindow;
    //ScrollableWindow<DirectoryMenuPage> menuPageWindow;

    //std::map<std::string,IButton*> buttons;
    GUI::Button<GUI::CancelTexture> CancelButton;
    GUI::Button<GUI::FileTexture> FileButton;
    Icon * icon;


private:
virtual void SetSize(){}

protected:
//void AddButton(IButton * _button) {}

void ConfigureSubElements();
std::string getXmlTagName() { return "DirectoryMenu"; }

private:
bool ActionOnPressingReturn();
void ActionOnPressingDownArrow();
void ActionOnPressingUpArrow();

public:
    DirectoryMenu();
    DirectoryMenu(float width, float height, float _borderSize = DefaultBorderSize);
    void setSize(float _width, float _height )
    {
        throw "Cannot set size for DirectoryMenu";
    }

    void MoveUpDirectory();
    void ClickUpIcon();


    bool InteractWithMouse(sf::Window * window);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};


} //EON

#endif // DIRECTORYMENU_H


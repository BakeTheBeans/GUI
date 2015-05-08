#ifndef MENUPAGE_H
#define MENUPAGE_H

#include "define.h"
#include "interfaces.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
//#include "tools.h"
#include "Utility.h"
#include "textmenutiles.h"
#include "factory.h"
#include "Traits.h"

namespace  GUI {


class MenuPage : public EnclosingBox, public IScrollable
{


    static const float DefaultHeight;
    static const float DefaultWidth;    
    static const int DefaultNumberofTiles;
    static const float DefaultTileThickness;

protected:
    std::vector<MenuTiles*> menuTileList;
    int numOfTiles;
    float slabHeight;
    int StartDisplayIndex;   
    typedef std::vector<MenuTiles*>::iterator TileIt;
    TileIt start, stop;
    float slabHeightWithBorders;
    int fontSize;
    TileIt endOfPage;
private:
    bool tilesConfigured;


private:
 virtual void SetSize();
 virtual void SetPosition();
 void DisposeTiles();

protected:
 void SetUpWindowDisplay();

public:
 static MenuTiles * getMenuTile()
 {
     static const float DefaultBorderSize = 2;
     static const float DefaultMarginSize = 0.4;
     static const float DefaultFontSize = 25;
     static const float DefaultTileThickness = 40;


     sf::Font * font = GUI::ResourceManager::getResource<GUI::Font>("Font_2");
     return new MenuTiles
             (font,
              DefaultWidth,
              DefaultTileThickness,
              DefaultBorderSize,
              "",
              DefaultFontSize,
              DefaultMarginSize,
              COL_GRAY_7,
              COL_BLACK);


 }


public:
    MenuPage();
    virtual ~MenuPage();

    bool AddMenuTile(MenuTiles * tile);
    MenuTiles * RemoveMenuTile(int index);

    int getNumberOfTiles() { return menuTileList.size(); }
    void setTextFontSize(int _size);


    void setTileThickness(float _slabHeight);    

    void setSize(float _width, float _height );

    virtual void scrollUp(int offset);
    virtual void scrollDown(int offset);
    virtual void scrollRight(int offset);
    virtual void scrollLeft(int offset);    


    void SetUpDisplay();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};


template<>
struct ScrollableEntityTrait<MenuPage>
{
    static const bool CanAdaptToWindow = false;
};

}//EON

#endif // DIRECTORYMENUPAGE_H

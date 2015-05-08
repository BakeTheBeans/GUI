#include "directorymenu.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <algorithm>
#include "factory.h"
//#include "GuiAttributeBuilder.h"
#include <string>
#include <scroll.h>

namespace  GUI {


const float DirectoryMenu ::  DefaultWidth = 400;
const float DirectoryMenu ::  DefaultHeight = 600;
const float DirectoryMenu ::  DefaultBorderSize = 5;

#if(NEW_DEBUG)
DirectoryMenu :: DirectoryMenu() : /*EnclosingBox() ,*/internal::ComplexObject(), menuPage(), menuPageWindow(0), CancelButton(), FileButton()
  #else
DirectoryMenu :: DirectoryMenu() : menuPage(), menuPageWindow(0), CancelButton(), FileButton()
  #endif
{
    GuiFactory & factory = GuiFactory::GetFactoryInstance();

    menuPage.setFillColor(COL_GRAY_14);

    menuPage.setBorderSize(5);
    menuPage.setBorderColor(COL_GREEN);
    menuPage.setPosition(100,100);
    menuPage.setTextFontSize(15);
    menuPage.setTileThickness(30);

    menuPageWindow = new GUI::ScrollableWindow<GUI::DirectoryMenuPage>(menuPage);
    menuPageWindow->setBorderSize(2);

    menuPageWindow->setPosition(300,100);
    menuPageWindow->setScrollBarColor(COL_GRAY_4);
    menuPageWindow->setVerticalDisplaySize(15);

    menuPageWindow->Configure();

    CancelButton.setScale(0.4,0.4);
    FileButton.setScale(0.4,0.4);

    sf::Font * font = GUI::ResourceManager::getResource<GUI::Font>("Font_2");

    TileMap["DirectoryNameLabel"] = MenuTiles
            (font,
             DefaultWidth,  //Width
             40,//TileThickness
             0, //BorderSize
             "Open",
             10, //Font Size
             0.4, //Margin
             COL_BLACK,  //LabelColor
             COL_BLACK,
             internal::Center
             );

    TileMap["DirectoryNameArea"] =  MenuTiles
            (font,
             200,  //Width
             30,//TileThickness
             0, //BorderSize
             "Directory Name Area",
             15, //Font Size
             0.4, //Margin
             COL_BLACK,  //LabelColor
             COL_BLUE
             ); //Font Color

    TileMap["Title"] =  MenuTiles
            (font,
             200,  //Width
             30,//TileThickness
             0, //BorderSize
             "Title",
             15, //Font Size
             0.4, //Margin
             COL_BLACK,  //LabelColor
             COL_BLUE
             ); //Font Color


    setMarginSize(0);
    setBorderSize(5);
    setBorderColor(COL_GRAY_3);

#if(NEW_DEBUG)
    Register<GUI::EnclosingBox>("EnclosingBox", *static_cast<EnclosingBox*>(this) );
    Register<GUI::ScrollableWindow<DirectoryMenuPage>>("DirectoryMenuPage",*menuPageWindow );
    Register<GUI::MenuTiles>("Title", TileMap["Title"]);
    Register<GUI::MenuTiles>("Label", TileMap["DirectoryNameLabel"] );
    Register<GUI::MenuTiles>("TextBox", TileMap["DirectoryNameArea"]);
    Register<GUI::Button<GUI::CancelTexture>>("CancelButton", CancelButton);
    Register<GUI::Button<GUI::FileTexture>>("FileButton", FileButton);

#endif

}


#if(NEW_DEBUG)
void DirectoryMenu :: ConfigureSubElements()
{
   for(auto & menu : TileMap) menu.second.Configure();
   setUp = true;
   MenuTiles & textBar = TileMap["DirectoryNameArea"];
   textBar.setText(menuPage.getCurrentDirectoryName() );

}

#endif

void DirectoryMenu :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    EnclosingBox::draw(target,states);
    target.draw( TileMap.at("DirectoryNameArea") );
    target.draw( TileMap.at("DirectoryNameLabel") );
    target.draw( TileMap.at("Title") );
    target.draw(*menuPageWindow);
    target.draw(CancelButton);
    target.draw(FileButton);
}





} //EON

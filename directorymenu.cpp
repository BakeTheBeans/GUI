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


DirectoryMenu :: DirectoryMenu() : internal::ComplexObject(), menuPage(), menuPageWindow(0), CancelButton(), FileButton()
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
    icon = IconBuilder::getIcon<UpIcon>();

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

    Register<GUI::EnclosingBox>("EnclosingBox", *static_cast<EnclosingBox*>(this) );
    Register<GUI::ScrollableWindow<DirectoryMenuPage>>("DirectoryMenuPage",*menuPageWindow );
    Register<GUI::MenuTiles>("Title", TileMap["Title"]);
    Register<GUI::MenuTiles>("Label", TileMap["DirectoryNameLabel"] );
    Register<GUI::MenuTiles>("TextBox", TileMap["DirectoryNameArea"]);
    Register<GUI::Button<GUI::CancelTexture>>("CancelButton", CancelButton);
    Register<GUI::Button<GUI::FileTexture>>("FileButton", FileButton);
    Register<GUI::Icon>("UpIcon", *icon);

    icon->iconEvents.AddEvent<DirectoryMenu>(this, &DirectoryMenu::MoveUpDirectory );


}


void DirectoryMenu :: MoveUpDirectory()
{
    if ( menuPage.MoveUpDirectory() ) TileMap["DirectoryNameArea"].setText( menuPage.getCurrentDirectoryName() );
}

void DirectoryMenu :: ClickUpIcon()
{
    icon->iconEvents.FireEvents();
}

void DirectoryMenu :: ConfigureSubElements()
{
   for(auto & menu : TileMap) menu.second.Configure();
   setUp = true;
   MenuTiles & textBar = TileMap["DirectoryNameArea"];
   textBar.setText(menuPage.getCurrentDirectoryName() );

}

//This is acting weird
bool DirectoryMenu :: InteractWithMouse(sf::Window * window)
{
    if ( menuPage.ContainsMouseInside(window) )
    {
        if ( menuPage.InteractWithMouse(window) )
        {
            MenuTiles & textBar = TileMap["DirectoryNameArea"];
             textBar.setText(menuPage.getCurrentDirectoryName());
             return true;
        }
    }
    else return false;

}

bool DirectoryMenu :: ActionOnPressingReturn()
{
    if (menuPage.ActionOnPressingReturn() )
    {
        MenuTiles & textBar = TileMap["DirectoryNameArea"];
        textBar.setText(menuPage.getCurrentDirectoryName());
    }
}

void DirectoryMenu :: ActionOnPressingDownArrow()
{
    menuPage.ActionOnPressingDownArrow();

    if ( menuPage.getSelectedTileIndex() >= menuPage.getVerticalDisplaySize() ) menuPageWindow->ScrollDown(1);

}

void DirectoryMenu :: ActionOnPressingUpArrow()
{
     menuPage.ActionOnPressingUpArrow();
     if ( menuPage.getSelectedTileIndex() >= menuPage.getVerticalDisplaySize() ) menuPageWindow->ScrollUp(1);
}

void DirectoryMenu :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    EnclosingBox::draw(target,states);
    target.draw( TileMap.at("DirectoryNameArea") );
    target.draw( TileMap.at("DirectoryNameLabel") );
    target.draw( TileMap.at("Title") );
    target.draw(*menuPageWindow);
    target.draw(CancelButton);
    target.draw(FileButton);
    target.draw(*icon);

}


} //EON

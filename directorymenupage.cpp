#include "directorymenupage.h"
#include <algorithm>
#include <iterator>

namespace  GUI {


const int DirectoryMenuPage :: MaxDisplayTiles = 15;

 DirectoryMenuPage :: DirectoryMenuPage() : MenuPage(), infoList(),  isDirectoryChanged(true), curDir()
 {
    curDir = Directory::getCurrentDirectoryPath();
    infoList = Directory::getDirectoryContents(curDir);
    SetUpNewDirectory();

 }


 void DirectoryMenuPage ::  SetUpNewDirectory()
 {

     if ( !isDirectoryChanged  ) return;
     int count = 0;

     auto Start = infoList.begin();
     auto Stop = infoList.end();

     sf::Vector2f pos = getInternalPosition();
     MenuTiles * tile  = 0;
     for(auto it = Start; it != Stop; it++ )
     {         
        tile = ( count < menuTileList.size() ) ? menuTileList[count] : getMenuTile();
        tile->setBorderColor(COL_BLACK);
        tile->setText( it->fileName );
        tile->setTextColor( ( it->type == DirectoryInfo::Directory ) ? COL_GREEN : ( it->type == DirectoryInfo::File ) ? COL_BLUE : COL_BLACK );
        tile->setPosition( pos.x, pos.y + tile->getHeight()*count );
        if ( count >= menuTileList.size() ) this->AddMenuTile(tile);
        count++;

     }
     //if ( !isConfigured() ) Configure();
     if ( !isConfigured() ) SetUpWindowDisplay();
     setUp = true;
     setVerticalPageSize(count);
     isDirectoryChanged = false;
     start = menuTileList.begin();
     stop = menuTileList.begin() + getVerticalDisplaySize();
     endOfPage = menuTileList.begin() + count;


 }

  bool DirectoryMenuPage  :: MoveUpDirectory()
  {
     resetVerticalScrollBar();

      int pos = std::string::npos;
      if (  (pos =  curDir.find_last_of('/') ) != std::string::npos )
      {
          curDir.erase( curDir.begin() + pos, curDir.end() );
      }

      if ( pos == 0 ) return false;

      infoList.clear();
      infoList = Directory::getDirectoryContents(curDir);
      isDirectoryChanged = true;

      SetUpNewDirectory();

      ConfigureWindow();

      return true;

  }


  bool DirectoryMenuPage  :: MoveIntoDirectory(std::string folder)
  {
      throw "Not Implemented";
  }


}//EON

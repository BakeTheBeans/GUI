//#include "directorymenupage.h"
#include "menupage.h"
#include <algorithm>
#include <iterator>


namespace  GUI {

const float  MenuPage ::  DefaultHeight = 400;
const float  MenuPage ::  DefaultWidth = 300;
const float MenuPage :: DefaultTileThickness = 20;
const int MenuPage :: DefaultNumberofTiles = 0;

MenuPage :: MenuPage() : EnclosingBox(), menuTileList(), numOfTiles(0), slabHeight(), StartDisplayIndex(0), start(), stop(), slabHeightWithBorders(), fontSize(0), endOfPage(), tilesConfigured(true), selectedTile(-1)
 {
    slabHeight = DefaultTileThickness;
    setVerticalDisplaySize(DefaultNumberofTiles);

    setInternalHeight(DefaultHeight);
    setInternalWidth(DefaultWidth);
    start = menuTileList.begin();
    stop = menuTileList.end();
 }

 MenuPage :: ~MenuPage()
 {
     std::for_each( menuTileList.begin(), menuTileList.end(), [] (MenuTiles * tile) -> void
     {
        if (tile)  delete tile;
     });
 }

 void MenuPage :: DisposeTiles()
 {
     for(auto it = menuTileList.begin(); it != menuTileList.end(); it++)
     {
         delete *it;
     }
     menuTileList.clear();
 }

 void MenuPage :: setTileThickness(float _slabHeight)
 {

     slabHeight = _slabHeight;
     tilesConfigured = false;
     setUp = false;
 }

 void MenuPage :: setTextFontSize(int _size)
 {
    fontSize = _size;
    setUp = false;
 }

 void MenuPage :: setSize(float _width, float _height )
 {
     std::cerr << "Cannot directly set size for MenuPage. Set the number of display tiles and tilethickness" << std::endl;
 }

 bool MenuPage :: AddMenuTile(MenuTiles * tile)
 {
     if (!tile ) return false;
     menuTileList.push_back(tile);
     start = menuTileList.begin();
     stop = menuTileList.end();
     numOfTiles += 1;
     setUp = false;
 }

 MenuTiles * MenuPage :: RemoveMenuTile(int index)
 {
     if ( index >= menuTileList.size() ) throw "Cannot remove tiles from index outside the container size";
     MenuTiles * p = menuTileList[index];
     menuTileList.erase(menuTileList.begin() + index, menuTileList.begin() + index + 1 );
     stop = menuTileList.end();
     numOfTiles -= 1;
     setUp = false;
     return p;

 }

  void MenuPage :: SetSize()
  {

      if ( menuTileList.size() > 0 )
      {
          float tileborder = menuTileList[0]->getBorderSize();
          slabHeight = getInternalHeight()/menuTileList.size() - 2*tileborder;
          float width  = getInternalWidth()  - 2*tileborder;

          for(auto it = menuTileList.begin(); it != menuTileList.end(); it++)
          {
              (*it)->setSize(width, slabHeight );
          }
      }
  }


  void MenuPage ::  SetUpDisplay()
  {
     if ( !getVerticalDisplaySize() ) setVerticalDisplaySize(numOfTiles);

      if (menuTileList.size() > 0 )
      {

          float tileborder = menuTileList[0]->getBorderSize();
          slabHeightWithBorders = slabHeight + 2*tileborder;

          sf::Vector2f pos = getInternalPosition();
          float width  = getInternalWidth()  - 2*tileborder;
          int count = 0;
          for(MenuTiles * p : menuTileList)
          {
              if ( fontSize ) p->setFontSize(fontSize);
              if ( !p->isConfigured() || !tilesConfigured )
              {
                  p->setSize(width, slabHeight );
                  p->Configure();
              }
              p->setPosition( pos.x, pos.y + count*(p->getHeight()) );

              count++;
          }

//         numOfTiles = count;
          setInternalHeight( ( count > getVerticalDisplaySize() ? count : getVerticalDisplaySize() ) * slabHeightWithBorders + 2*getMarginSize());

      }

      start = menuTileList.begin();
      stop = menuTileList.end();


  }


/*
 * Only to be called by window class. Not for external use.
 */
  void MenuPage :: SetUpWindowDisplay()
  {

      SetUpDisplay();
      DEBUG_MESSAGE;
      std::cout << " Display Size: " << getVerticalDisplaySize() << std::endl;
      setInternalHeight( ( numOfTiles < getVerticalDisplaySize() ?  numOfTiles : getVerticalDisplaySize() ) * slabHeightWithBorders + 2*getMarginSize());

      setVerticalPageSize(numOfTiles);
      start = menuTileList.begin();
      stop = menuTileList.begin() + ( (getVerticalDisplaySize() > numOfTiles) ? numOfTiles : getVerticalDisplaySize() );
      endOfPage = menuTileList.end();
      setUp = true;
  }

  void MenuPage :: SetPosition()
  {

      sf::Vector2f pos = getInternalPosition();

      if ( menuTileList.size() > 0 )
      {
          menuTileList[0]->setPosition(pos.x, pos.y + menuTileList[0]->getBorderSize() );
          int count = 0;
          for(auto it = menuTileList.begin(); it != menuTileList.end(); it++)
          {
              (*it)->setPosition( pos.x, pos.y + count*(*it)->getHeight() );
              count++;
          }
      }
  }

  /*
  void MenuPage :: ActionOnPressingReturn()
  {


  }
*/
  void MenuPage :: ActionOnPressingDownArrow()
  {
      if ( selectedTile == menuTileList.size() - 1 ) return;

      std::cout << " Selected Tile : " << selectedTile << std::endl;
      if ( selectedTile > -1 )
      {
          MenuTiles * p = menuTileList[selectedTile];
          p->UnHighLightTile();
      }

      selectedTile++;
      MenuTiles * p = menuTileList[selectedTile];
      p->HighLightTile();

  }

  void MenuPage :: ActionOnPressingUpArrow()
  {
      if ( selectedTile == 0 ) return;

      if ( selectedTile < menuTileList.size() - 1 )
      {
          MenuTiles * p = menuTileList[selectedTile];
          p->UnHighLightTile();
      }

      selectedTile--;
      MenuTiles * p = menuTileList[selectedTile];
      p->HighLightTile();


  }

  int MenuPage :: getMouseSelectedTileIndex(sf::Window * _window)
  {
      int count = 0;
      int index = -1;
      for(MenuTiles * tile : menuTileList )
      {          
          if ( tile->ContainsMouseInside(_window) )
          {
              //tile->InteractWithMouse(_window);
              tile->HighLightTile();
              if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
              {
                  index = count;
                  break;
              }
              
          }
          //else tile->MouseLeft(_window);
          else tile->UnHighLightTile();
          count++;
      } 
      
      return index;
  }

  bool MenuPage :: InteractWithMouse(sf::Window * _window)
  {
    throw "MenuPage::InteractWithMouse not implemented";
  }

  void MenuPage :: scrollUp(int offset)
  {

      if ( std::distance(start,menuTileList.begin() ) == 0 ) return;
      start -= offset;
      stop = start + getVerticalDisplaySize();//numOfTiles;
      sf::Vector2f pos = getInternalPosition();

      int count = 0;
      for(auto it = start; it!= stop; it++  )
      {
          (*it)->setPosition( pos.x, pos.y + (*it)->getHeight()*count++ );
      }

  }


  void MenuPage :: scrollDown(int offset)
  {
      if ( std::distance(stop, endOfPage ) == 0 ) return;

      stop += offset;
      start = stop - getVerticalDisplaySize(); //numOfTiles;

      //std::cout << " Distance : " << std::distance(start,stop) << std::endl;

      sf::Vector2f pos = getInternalPosition();

      int count = 0;
      for(auto it = start; it!= stop; it++  )
      {
          (*it)->setPosition( pos.x, pos.y + (*it)->getHeight()*count++ );
      }


  }

  void MenuPage :: scrollRight(int offset)
  {
      std::cout << " Horizontal scrolling not implemented" << std::endl;
  }

  void MenuPage :: scrollLeft(int offset)
  {
      std::cout << " Horizontal scrolling not implemented" << std::endl;
  }


  void MenuPage :: draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
      this->EnclosingBox::draw(target,states);        

      std::for_each( start, stop, [&] (MenuTiles * tile)->void
      {
        target.draw(*tile);
      });
  }


}//EON

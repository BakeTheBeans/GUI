#include "unittest.h"
#if(SCRATCH_TEST)
#include "Utility.h"
#include <string>
#include "factory.h"
#else

#include "button.h"
#include <algorithm>
#include "buttonicons.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#endif

#define WINDOW_POSITION window->getPosition().x, window->getPosition().y



UnitTest::UnitTest(sf::Event & _event) : event(_event), window(0)
{
#if(!NO_DISPLAY)
    window = new sf::RenderWindow(sf::VideoMode(1024,900), "UnitTest Window", sf::Style::Resize | sf::Style::Close);
//#if(NO_DISPLAY)
#else
    //window->close();
    std::cout << "\n***********You are running in NO DISPLAY mode possibly for debugging*********\n" <<std::endl;
#endif
}

//Draw::MouseProjector ScratchTest::mp = Draw::MouseProjector::getMouseProjector();

#if(SCRATCH_TEST)
void ScratchTest :: SetUpEnvironment()
{
    Draw::MouseProjector::getMouseProjector().EnableProjection();
    flag = false;
    //p = new Draw::ContinuousLine();
    //p = new Draw::Triangle();
    //p = new Draw::Line();
    //p = new Draw::Rectangle();
    //p = new Draw::Quad();
    //p = new Draw::Polygon<5>();
    //p = new Draw::BlockTriangle();
    //p = new Draw::BlockRectangle();
    //p = new Draw::BlockQuad();
    //p = new Draw::BlockPolygon<5>();
    //p = new Draw::Pentagon();
    //p = new Draw::Hexagon();
    //p = new Draw::EquilateralTriangle();
    p =  new Draw::RegularBlockPolygon<5>();

    //p = new Draw::Circle();
    //p = new Draw::BlockCircle();
    //p = new Draw::Polygon<4>();
    //p = new Draw::BlockPolygon<5>();
    //mp.EnableProjection();
    Draw::MouseProjector::getMouseProjector().DisableMouseProjection();
}

void ScratchTest :: InsidePollingImpl()
{

    if (!flag )
    {
        //flag = rect.StartDraw(*window);
        flag = p->StartDraw(*window);
    }

    if ( flag)
    {
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::P) ) p->scale(1.2,1.2);
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::F)) p->BringToFocus(*window);
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::C)) p->setColor(sf::Color::Green);
    }

    if ( flag )
    {
        if ( p->isMouseInside() )
        {
            if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
            {
                if ( ! (p->isSelected()) )p->select();
                else p->deselect();
            }

            if( p->isSelected() )
            {
                p->drag();
                //p->rotate();
                //if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) ) p->rotateByAngle(30);
            }
        }
    }


    if ( flag )
    {
        Draw::VertexShapes * q = static_cast<Draw::VertexShapes*>(p);
        if ( q->highlightEdge(*window) && sf::Mouse::isButtonPressed(sf::Mouse::Left) ) q->selectEdge();
        if ( q->isAnyEdgeSelected() ) q->setEdgeColor(sf::Color::Red );
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D)) q->deselectEdge();
    }



    //mp.Project(*window);
    Draw::MouseProjector::getMouseProjector().Project(*window);
}

void ScratchTest :: NoDisplayFunction()
{

}


void ScratchTest :: DisplayObjects()
{

    window->clear();
    window->draw(*p);
    window->draw(Draw::MouseProjector::getMouseProjector());
    window->display();
}


#endif


#if(DRAW_APPLICATION_TEST)
 void DrawAppTest :: SetUpEnvironment() {}
 void DrawAppTest :: InsidePollingImpl() {}

 void DrawAppTest :: DisplayObjects() {}
 void DrawAppTest :: NoDisplayFunction() {}

#endif


#if(DRAW_TEST)


void DrawTest :: SetUpEnvironment()
{



#if(Test_1)
    flag = false;

    Draw::MouseProjector::getMouseProjector().EnableProjection();
    Draw::ShapeFactory & factory = Draw::ShapeFactory::getShapeFactory();

    //p = factory.CreateInstance<Draw::Triangle>();
    p = factory.CreateShapeInstance<Draw::Triangle>();
    //static_cast<Draw::VertexShapes*>(p)->setVertexColor(1,sf::Color::Black);


    //p = new Draw::ContinuousLine();
    //p = new Draw::Triangle();
    //p = new Draw::Line();
    //p = new Draw::Rectangle();
    //p = new Draw::Quad();
    //p = new Draw::Polygon<5>();
    //p = new Draw::BlockTriangle();
    //p = new Draw::BlockRectangle();
    //p = new Draw::BlockQuad();
    //p = new Draw::BlockPolygon<5>();
    //p = new Draw::Pentagon();
    //p = new Draw::Hexagon();
    //p = new Draw::EquilateralTriangle();
    //p =  new Draw::RegularBlockPolygon<5>();

    //p = new Draw::Circle();
    //p = new Draw::BlockCircle();
    //p = new Draw::Polygon<4>();
    //p = new Draw::BlockPolygon<5>();
    //mp.EnableProjection();
    Draw::MouseProjector::getMouseProjector().DisableMouseProjection();
#endif


#if(Test_2)
#if(NEW_DEBUG)
scrollWindow->setPosition(100,100);
scrollWindow->setSize(600,600);
page.Configure();
scrollWindow->Configure();
#endif
#endif

#if(Test_3)
#if(NEW_DEBUG)
scrollWindow->setPosition(100,100);
scrollWindow->setSize(600,600);
page.Configure();
scrollWindow->Configure();
#endif
#endif


}

void DrawTest :: NoDisplayFunction()
{

    char input;
    while( std::cin >> input  )
    {
        if ( std::tolower(input) == 'u' )   scrollWindow->ScrollUp(5);

        if ( std::tolower(input) == 'd' )  scrollWindow->ScrollDown(5);
    }

}



void DrawTest :: InsidePollingImpl()
{

#if(Test_3)
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::C))
    {
        page.CreateVerticalPageSpace(10);
    }

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
    {
        scrollWindow->ScrollDown(5);
    }

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
    {
        scrollWindow->ScrollUp(5);
    }

    std::cout << " Page Size : " << page.getVerticalPageSize() << "     Display Size : " << page.getVerticalDisplaySize() << std::endl;

#endif

#if(Test_2)


    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::V))
    {
        scrollWindow->CreateVerticalPageSpace(10);
    }

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::H))
    {
        scrollWindow->CreateHorizontalPageSpace(10);
    }

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
    {
        scrollWindow->ScrollDown(5);
    }

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
    {
        scrollWindow->ScrollUp(5);
    }

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
    {
        scrollWindow->ScrollRight(5);
    }

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
    {
        scrollWindow->ScrollLeft(5);
    }

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::I))
    {
        //page.zoomIn(1.2);
        scrollWindow->Zoom(1.2);
    }

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::O))
    {
        std::cout << " Zooming Out : " << std::endl;
        //page.zoomIn(.9);
        scrollWindow->Zoom(0.9);
    }


    if (!flag )
    {
        if ( flags[2] )
        {
            flags[0] = page.DrawShape<Draw::Rectangle>(*window);
            if ( flags[0] ) flags[2] = false;
        }

        if ( flags[0] )
        {
            flags[1] = page.DrawShape<Draw::Triangle>(*window);
            if ( flags[1] ) flags[0] = false;
        }

        if ( flags[1] )
        {
            flags[2] = page.DrawShape<Draw::BlockHexagon>(*window);
            if ( flags[2] ) flag = true;
        }

    }



    if ( flag )
    {
        page.EnablePageLoop();
    }


    //Save and load
/*
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)  )
    {
        page.Save("SavedFile.dr");
    }

    else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::L)  )
    {
        page.Load("SavedFile.dr");
    }
*/




#elif(Test_1)


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)  )
    {
        Draw::ShapeFactory::getShapeFactory().Save( "ShapeSavedFile.dr");
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)  )
    {
        //p = Draw::ShapeFactory::getShapeFactory().Load( "ShapeSavedFile.dr" );
        p = Draw::ShapeFactory::getShapeFactory().Load("ShapeSavedFile.dr" );

    }



    if (!flag )
    {
        //flag = rect.StartDraw(*window);
        flag = p->StartDraw(*window);

    }


    if ( flag)
    {
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::P) ) p->scale(1.2,1.2);
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::F)) p->BringToFocus(*window);
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::C)) p->setColor(sf::Color::Green);
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down ) ) static_cast<Draw::VertexShapes*>(p)->MoveShapeUp(5);
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up ) ) static_cast<Draw::VertexShapes*>(p)->MoveShapeDown(5);

    }

    if ( flag )
    {
        if ( p->isMouseInside() )
        {
            if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
            {
                if ( ! (p->isSelected()) )p->select();
                else p->deselect();
            }

            if( p->isSelected() )
            {
                //p->drag();
                //p->rotate();
                //if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) ) p->rotateByAngle(30);

            }
        }
    }


    if ( flag )
    {
        Draw::VertexShapes * q = static_cast<Draw::VertexShapes*>(p);
        //if ( q->highlightEdge(*window) && sf::Mouse::isButtonPressed(sf::Mouse::Left) ) q->selectEdge();
        //if ( q->isAnyEdgeSelected() ) q->setEdgeColor(sf::Color::Red );
        //if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D)) q->deselectEdge();
        /*
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::S ) )
        {
            Draw::VertexShapes * q = static_cast<Draw::VertexShapes*>(p);
            q->Serialize("ShapeSavedFile.dr");
        }
        */

    }
    Draw::MouseProjector::getMouseProjector().Project(*window);
#endif




}



void DrawTest :: DisplayObjects()
{

    window->clear();
#if(Test_1)
    /*if (flag)*/ window->draw(*p);
    window->draw(Draw::MouseProjector::getMouseProjector());
#elif(Test_2)
#if(NEW_DEBUG)
    window->draw(*scrollWindow);
#else
       window->draw(page);
#endif
#elif(Test_3)
    window->draw(*scrollWindow);
#endif
    window->display();
}

#endif



#if(DIRECTORYMENUPAGE_TEST)
void DirectoryMenuPageTest :: SetUpEnvironment()
{
    menuPage.setFillColor(COL_GRAY_14);

    menuPage.setBorderSize(5);
    menuPage.setBorderColor(COL_GREEN);
    menuPage.setPosition(100,100);
    menuPage.setTextFontSize(15);

#if(SCROLL_WINDOW)
    menuPageWindow = new GUI::ScrollableWindow<GUI::DirectoryMenuPage>(menuPage);

    menuPageWindow->setBorderSize(2);

    menuPageWindow->setPosition(300,100);
    menuPageWindow->setScrollBarColor(COL_GRAY_4);
    menuPageWindow->setVerticalDisplaySize(10);
    menuPageWindow->setSize(200,300);

    menuPageWindow->Configure();
#else
    menuPage.Configure();

#endif
}

void DirectoryMenuPageTest :: InsidePollingImpl()
{

#if(SCROLL_WINDOW)
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        menuPageWindow->ScrollDown(1);
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        menuPageWindow->ScrollUp(1);
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        menuPage.MoveUpDirectory();
    }
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        menuPageWindow->ScrollUp(1);
#endif

}

void DirectoryMenuPageTest :: NoDisplayFunction()
{
    std::cout << "Press 'u' to move up the directory " << std::endl;
    char s;
    //while( std::cin >> s  )
    while(true)
    {

//       if ( std::tolower(s) == 'u' ) menuPage.MoveUpDirectory();
//       else break;

       menuPage.MoveUpDirectory();

    }

}


void DirectoryMenuPageTest :: DisplayObjects()
{
    window->clear();

#if(SCROLL_WINDOW)
    window->draw(*menuPageWindow);
#else
    window->draw(menuPage);
#endif
    window->display();

}
#endif



#if(MENUPAGE_TEST)
void MenuPageTest :: SetUpEnvironment()
{

#if(Test_1)

#ifdef SCROLL_WINDOW
#undef SCROLL_WINDOW
#endif

    menuPage.setFillColor(COL_GRAY_14);
    menuPage.setBorderSize(10);
    menuPage.setMarginSize(5);
    menuPage.setBorderColor(COL_GREEN);

    for(auto it = konoha.begin(); it != konoha.end(); it++)
    {
        GUI::MenuTiles * p = GUI::MenuPage::getMenuTile();
        p->setText(*it);
        menuPage.AddMenuTile(p);
    }


    menuPage.setSize(100,400);
    menuPage.setPosition(100,100);
    menuPage.Configure();

#elif(Test_2)

    menuPage.setSize(400,400);
    menuPage.setPosition(200,200);
    for(auto it = konoha.begin(); it != konoha.end(); it++)
    {
        GUI::MenuTiles * p = GUI::MenuPage::getMenuTile();
        p->setText(*it);
        menuPage.AddMenuTile(p);
    }
    //menuPage.Configure();
#if(SCROLL_WINDOW)
    menuWindow->setSize(200,400);
    menuWindow->setPosition(100,100);
    menuWindow->setVerticalDisplaySize(3);
    menuWindow->Configure();
#endif

#elif(Test_3)

#ifdef SCROLL_WINDOW
#undef SCROLL_WINDOW
#endif

 //menuPage.setSize(0,0);//Note size is zero
 for(auto it = konoha.begin(); it != konoha.end(); it++)
 {
     GUI::MenuTiles * p = GUI::MenuPage::getMenuTile();
     p->setText(*it);
     menuPage.AddMenuTile(p);
     //menuPage.setPosition(100,300);
 }

 menuPage.setFillColor(COL_GREEN);
 menuPage.setBorderSize(5);
 menuPage.setMarginSize(5);
 menuPage.setTextFontSize(15);
 menuPage.setPosition(100,100);
 menuPage.Configure(); //Configuring sets adjusts the configuration
//menuPage.SetUpWindowDisplay();
#endif


#if(Test_4)

 menuPage.setSize(200,500);//Note size is zero
 for(auto it = konoha.begin(); it != konoha.end(); it++)
 {
     GUI::MenuTiles * p = GUI::MenuPage::getMenuTile();
     p->setText(*it);
     menuPage.AddMenuTile(p);
     menuPage.setPosition(100,300);
 }

 menuPage.setTextFontSize(15);
 menuPage.Configure(); //Configuring sets adjusts the configuration

#if(SCROLL_WINDOW)
menuWindow->setSize(200,200);
menuWindow->setVerticalDisplaySize(6);
menuWindow->setPosition(100,100);
menuWindow->Configure();
#endif

#endif

}


void MenuPageTest :: InsidePollingImpl()
{

#if(Test_2 && !SCROLL_WINDOW)
    window->setTitle("Press R for fun");

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        menuPage.AddMenuTile( menuPage.RemoveMenuTile(0) );
        menuPage.Configure();
    }

#endif

#if(Test_2 && SCROLL_WINDOW)
    window->setTitle("Press R for fun");

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        menuPage.AddMenuTile( menuPage.RemoveMenuTile(0) );
        menuWindow->Configure();
    }

#endif

#if(Test_4 && SCROLL_WINDOW)
if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) menuWindow->ScrollDown(1);

if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) menuWindow->ScrollUp(1);
#endif
}


void MenuPageTest :: DisplayObjects()
{
    window->clear();
#if(SCROLL_WINDOW)
    window->draw(*menuWindow);
#else
    window->draw(menuPage);
#endif
    window->display();

}

#endif


#if(SCROLLABLETEXTWINDOW_TEST)

void ScrollableTextWindowTest :: SetUpEnvironment()
{

    const char * Text = "Press Down Arrow to scroll down and up arrow to scroll up. Robert \"Bobby\" Astor is a rising New York Hedge Fund Manger on the cusp of making the biggest ever deal. But everything is chamged when is father, the Chairman of the New York Stock Exchange is killed in a bizzare accident. This result allows us to return to power,\" said Herzog to supporters at a sports arena in Tel Aviv. \"We will wait for the final results, we talked to the chiefs of the relevant parties and we will wait. But I promise to make every effort to form a government dedicated to social issues in Israel\". \"We're in this for the long haul. We're not afraid and we won't give up. We love the people of Israel, we love the land of Israel, we love Israel's Torah and the soldiers of the Israel Defense Force,\" Bennett told activists at the partpy's headquarters, adding he was not disappointed with his voters, \"on the contrary, I'm proud of the religious Zionism.";

    try{


     textBox.setFont(GUI::ResourceManager::getResource<GUI::Font>("Font_3"));
     textBox.setText(Text);
     textBox.setFontSize(20);
     //textBox.setSize(180,40);
     textBox.setFillColor(COL_BLACK);
     textBox.setMarginSize(10);
     textBox.setTextColor(COL_BLUE);    
    }


     catch(const char * ss)
     {
         std::cout << ss << std::endl;
     }


    sWindow->setBorderSize(5);
    sWindow->setMarginSize(1);
    sWindow->setScrollBarColor(COL_GREEN);
    sWindow->setScrollStoneColor(COL_GRAY_9);
    sWindow->setScrollBarColor(COL_RED);
    sWindow->setSize(600,200);
    sWindow->setPosition(200,200);



    sWindow->Configure();

}

void ScrollableTextWindowTest :: InsidePollingImpl()
{
if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
    sWindow->ScrollDown(1);
if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up)  )
    sWindow->ScrollUp(1);
}


void ScrollableTextWindowTest :: DisplayObjects()
{
    window->clear();
    window->draw(*sWindow);
    window->display();

}



#endif


#if(SCROLLWINDOW_TEST)

void ScrollableWindowTest :: SetUpEnvironment()
{


    scrollWindow.setPosition(100,100);
    scrollWindow.setSize(300,300);
    scrollWindow.setBorderSize(5);
    scrollWindow.setScrollBarColor(COL_GRAY_5);
    scrollWindow.setScrollStoneColor(COL_GRAY_16);
    scrollWindow.setFillColor(COL_BLACK);

    scrollWindow.setMarginSize(0);
    scrollWindow.PrintDetails();
}

void ScrollableWindowTest :: InsidePollingImpl()
{

}

void ScrollableWindowTest :: DisplayObjects()
{
    window->clear();
    window->draw(scrollWindow);
    window->display();
}

#endif

#if(MENUTILES_TEST)

MenuTilesTest  :: MenuTilesTest (sf::Event & _event) : UnitTest(_event), menuTile(0)
{
    sf::Font * ff= GUI::ResourceManager::getResource<GUI::Font>("Font_3");
    menuTile = new GUI::MenuTiles(ff);
}

void MenuTilesTest  :: SetUpEnvironment()
{
#if(!NO_DISPLAY)
    window->setTitle("Press T to keep change Text and A to change alignment.... and spacebar to quit :)");
#endif
    menuTile->setTextColor(COL_RED);
    //menuTile->setPosition(300,300);
    menuTile->setSize(200,40);
    menuTile->setFontSize(20);
    menuTile->setPosition(100,300);
    //menuTile->setFontSize(30);
    menuTile->setTextAlignment(GUI::internal::Right);
    menuTile->setMarginSize(0.2);
    menuTile->Configure();
}

void MenuTilesTest  :: InsidePollingImpl()
{
    static int i = 0, j = 1;
    std::string Text[] =
    {
        "Your Text Here",
        "Hello Hello Hello",
        "Bake The Beans",
        "L",
        "This Text is very long",
        "This is an even longer text"
    };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) )
    {
        menuTile->setText(Text[i]);
        i = i == 4  ? 0 : i + 1;
    }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
    {
        menuTile->setTextAlignment(static_cast<GUI::internal::TextAlignment>(j));
        j = j == 3 ? 1 : j + 1;

    }

}

void MenuTilesTest  :: DisplayObjects()
{
    window->clear();
    window->draw(*menuTile);
    window->display();
}


//void MenuTilesTest  :: CleanUp() { window->close(); }

void MenuTilesTest :: NoDisplayFunction()
{
    std::cout << "Hit t to change text and a to change alignment and s to break" << std::endl;

    char input;
    while(std::cin >> input )
    {
        static int i = 0, j = 1;
        const char * Text[] =
        {
            "Your Text Here",
            "Hello Hello Hello",
            "Bake The Beans",
            "L",
            "This Text is very long",
            "This is an even longer text"
        };

        if ( std::tolower(input) == 't' )
        {
            menuTile->setText(Text[i]);
            i = i == 5 ? 0 : i + 1;
        }

        if ( std::tolower(input) == 'a'  )
        {
            menuTile->setTextAlignment(static_cast<GUI::internal::TextAlignment>(j));
            j = j == 3 ? 1 : j + 1;

        }

        if ( std::tolower(input) == 's'  )
        {
            break;
        }
    }
}


#endif


#if(DIRECTORY_MENU_TEST)
void DirectoryMenuTest:: SetUpEnvironment()
{
   //dirMenu.setSize(100,300);
   //dirMenu.setPosition(100,100);
   //dirMenu.Configure();

    //dirMenu.SetUpDisplayFromXml();
    dirMenu.SetUpFromXml();
    dirMenu.setPosition(100,10);

    //dirMenu.Configure();
}

void  DirectoryMenuTest::  InsidePollingImpl()
{
/*
    if ( dirMenu.ContainsMouseInside(window)  )
    {
        dirMenu.InteractWithMouse(window);
    }
*/
    dirMenu.InteractWithKeyBoard(event);

    if ( event.type == sf::Event::KeyPressed )
    {
        if ( event.key.code == sf::Keyboard::P ) dirMenu.ClickUpIcon();
    }

}

void  DirectoryMenuTest::  CleanUp()
{

}

void  DirectoryMenuTest::  DisplayObjects()
{
    window->clear();
    window->draw(dirMenu);
    window->display();
}
#endif



#if(SCROLLBAR_TEST)

void ScrollBarTest :: SetUpEnvironment()
{


#if(Test_1 || Test_5)
    scrollBar.setPosition(200,200);
    scrollBar.setStoneColor(COL_GRAY_7);
    scrollBar.setPageSize(300);
    scrollBar.setDisplaySize(60);

#elif(Test_2 || Test_6)
    scrollBar.setPosition(300,200);
    scrollBar.setStoneColor(COL_GRAY_14);
    scrollBar.setPageSize(100);
    scrollBar.setDisplaySize(100);

#elif(Test_3 || Test_7)
    scrollBar.setPosition(200,200);
    scrollBar.setStoneColor(COL_GRAY_9);
    scrollBar.setPageSize(300);
    scrollBar.setDisplaySize(15);

#elif(Test_4 || Test_8)
    scrollBar.setMarginSize(4);
    scrollBar.setBorderSize(5);
    scrollBar.setPageSize(300);
    scrollBar.setFillColor(COL_YELLOW);
    scrollBar.setDisplaySize(15);
    scrollBar.setBorderColor(COL_GRAY_9);
    scrollBar.setPosition(200,200);
    scrollBar.setStoneColor(COL_GRAY_9);

#endif

#if(Test_1)
scrollBar.setSize(20,400);
#elif(Test_2)
scrollBar.setSize(10,200);
#elif(Test_3)
scrollBar.setSize(20,140);
#elif(Test_4)
scrollBar.setSize(20,300);
#elif(Test_5)
scrollBar.setSize(140,20);
#elif(Test_6)
scrollBar.setSize(200,10);
#elif(Test_7)
scrollBar.setSize(140,20);
#elif(Test_8)
scrollBar.setSize(300,20);
#endif



}

void ScrollBarTest :: InsidePollingImpl()
{
#if(Test_1)
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
        scrollBar.scroll(100,GUI::ScrollBar::down);

    else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
        scrollBar.scroll(100,GUI::ScrollBar::up );
#elif(Test_2)
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
        scrollBar.scroll(8,GUI::ScrollBar::down);

    else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
        scrollBar.scroll(100,GUI::ScrollBar::up );
#elif(Test_3)
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
        scrollBar.scroll(8,GUI::ScrollBar::down);

    else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
        scrollBar.scroll(100,GUI::ScrollBar::up );
#elif(Test_4)
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
        scrollBar.scroll(20,GUI::ScrollBar::down);

    else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
        scrollBar.scroll(10,GUI::ScrollBar::up );
#elif(Test_5)
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
        scrollBar.scroll(100,GUI::ScrollBar::right);

    else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
        scrollBar.scroll(100,GUI::ScrollBar::left );
#elif(Test_6)
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
        scrollBar.scroll(8,GUI::ScrollBar::left);

    else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
        scrollBar.scroll(100,GUI::ScrollBar::right );
#elif(Test_7)
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
        scrollBar.scroll(8,GUI::ScrollBar::right);

    else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
        scrollBar.scroll(100,GUI::ScrollBar::left );
#elif(Test_8)
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
        scrollBar.scroll(20,GUI::ScrollBar::right);

    else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
        scrollBar.scroll(10,GUI::ScrollBar::left );

#endif
}


void ScrollBarTest :: DisplayObjects()
{

    window->clear();
    window->draw(scrollBar);
    window->display();
}

#endif

#if(TEXTBOX_TEST)


void TextBoxTest  :: InsidePollingImpl()
{
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
    {
        textBox.scrollUp(1.0);
    }

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
    {
        textBox.scrollDown(1.0);
    }

}

void TextBoxTest :: SetUpEnvironment()
{
#if(!DEBUG)
    textBox.setTextBoxColor(COL_BLACK);
#else
    textBox.setFillColor(COL_BLACK);
    textBox.setBorderColor(COL_GRAY_5);
    textBox.setBorderSize(5);
    textBox.setMarginSize(1);
#endif
    textBox.setTextColor(COL_BLUE);
    textBox.setSize(400,300);
    //textBox.setBorderSize(10);
    textBox.setPosition(400,400);
    textBox.setFont(GUI::ResourceManager::getResource<GUI::Font>("Font_3"));
    textBox.setBorderSize(4);

    textBox.setFontSize(20);

    textBox.setText("Press Down Arrow to scroll down and up arrow to scroll up. Robert \"Bobby\" Astor is a rising New York Hedge Fund Manger on the cusp of making the biggest ever deal. But everything is chamged when is father, the Chairman of the New York Stock Exchange is killed in a bizzare accident. This result allows us to return to power,\" said Herzog to supporters at a sports arena in Tel Aviv. \"We will wait for the final results, we talked to the chiefs of the relevant parties and we will wait. But I promise to make every effort to form a government dedicated to social issues in Israel\". \"We're in this for the long haul. We're not afraid and we won't give up. We love the people of Israel, we love the land of Israel, we love Israel's Torah and the soldiers of the Israel Defense Force,\" Bennett told activists at the partpy's headquarters, adding he was not disappointed with his voters, \"on the contrary, I'm proud of the religious Zionism.");
    //textBox.SetUpDisplay();
    textBox.Configure();
}


void TextBoxTest :: DisplayObjects()
{
    window->clear();
    window->draw(textBox);
    window->display();

}

void TextBoxTest :: CleanUp()
{
    window->close();

}

void TextBoxTest :: NoDisplayFunction()
{
    std::cout << "Press 'u' to scroll up and 'd' to scroll down and anything else to break out" << std::endl;
    char s;
    while( std::cin >> s  )
    {

       if ( std::tolower(s) == 'u' )  textBox.scrollUp(1.0);
       else if ( std::tolower(s) == 'd') textBox.scrollDown(1.0);
       else break;

    }

}

#endif


#if(MENUBAR_TEST)
void MenuBarTest :: SetUpEnvironment()
{

    GUI::ButtonFactory::RegisterButton<GUI::FileTexture>();
    GUI::ButtonFactory::RegisterButton<GUI::PlainTexture>();
    GUI::ButtonFactory::RegisterButton<GUI::CancelTexture>();
    GUI::ButtonFactory::RegisterButton<GUI::EditTexture>();
    GUI::ButtonFactory::RegisterButton<GUI::MenuTexture>();

   GUI::GuiFactory factory = GUI::GuiFactory::GetFactoryInstance();
   //newBar =  factory.CreateObject<GUI::MenuBar>();
   //newBranch =  factory.CreateObject<GUI::MenuBar>();
   //bar =factory.CreateObject<GUI::MenuBar>();



//*****Play with combinations**************


    //newBar = new GUI::MenuBar("Hello", GUI::MenuBar::Vertical, 100, 40, 4);
    newBar = new GUI::MenuBar("Hello", GUI::internal::Vertical, 100, 40, 4);
    newBar->AddMenuItem(GUI::ButtonFactory::getButton<GUI::FileTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::EditTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::PlainTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::CancelTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::MenuTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::FileTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::PlainTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::PlainTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::PlainTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::CancelTexture>());

    //newBranch = new GUI::MenuBar("NewBranch", GUI::MenuBar::Vertical,100, 40,4);
    newBranch = new GUI::MenuBar("NewBranch", GUI::internal::Vertical,100, 40,4);
    newBranch->AddMenuItem(GUI::ButtonFactory::getButton<GUI::FileTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::FileTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::PlainTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::PlainTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::PlainTexture>());

    newBar->setPosition(100,120);
    newBranch->setPosition(100,200);
    const sf::Vector2f & pos = newBar->getPosition();
    newBar->AddMenuItem(newBranch);


    newBar->setName("MainMenu");
    newBar->SwapAlignment();

    newBranch->setName("Branch");
    //newBranch->SwapAlignment();

    newBar->scale(0.8,0.8);
    //newBar->scale(0.5,0.5);

    bar = new GUI::MenuBar("Hello", GUI::internal::Vertical, 100,40,2);
    //bar = new GUI::MenuBar("Hello", GUI::MenuBar::Vertical, 100,40,2);
    bar->setBorderColor(sf::Color::Blue);
    bar->AddMenuItem(GUI::ButtonFactory::getButton<GUI::EditTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::PlainTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::PlainTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::PlainTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::CancelTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::PlainTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::CancelTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::MenuTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::FileTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::PlainTexture>()).AddMenuItem(GUI::ButtonFactory::getButton<GUI::PlainTexture>());

    bar->setPosition(600,200);


}

void MenuBarTest :: InsidePollingImpl()
{

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::C))
    {
        newBar->Collapse();
    }

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        newBar->Expand();
    }
}


void MenuBarTest :: DisplayObjects()
{
    window->clear();
    window->draw(*newBar);
//    window->draw(*newBranch); //Do not draw this.
    window->draw(*bar);
    window->display();

}

void MenuBarTest :: CleanUp()
{
    window->close();

}
#endif


#if(BUTTON_TEST)
void ButtonTest_1 :: SetUpEnvironment()
{

    TestHovering = true;
    TestDragging = true;


#if(BUTTON_TEST_4)

    GUI::IButton * p = 0;
    SETUP_BUTTON(p,ButtonType
::B_PLAIN,GUI::PlainTexture,600,100,COL_GREEN);
    SETUP_BUTTON(p,ButtonType
::B_FILE,GUI::FileTexture,200,100,COL_MAGENTA);
    SETUP_BUTTON(p,ButtonType
::B_EDIT,GUI::EditTexture, 300,100,COL_CYAN);
    SETUP_BUTTON(p,ButtonType
::B_CANCEL,GUI::CancelTexture, 300,100,COL_RED);
    SETUP_BUTTON(p,ButtonType
::B_BACK,GUI::BackTexture,400,100,COL_BLUE);
    SETUP_BUTTON(p,ButtonType
::B_MENU,GUI::MenuTexture,500,100,COL_YELLOW);
    SETUP_BUTTON(p,ButtonType
::B_SETTINGS,GUI::SettingsTexture,600,300,COL_GREEN);
    SETUP_BUTTON(p,ButtonType
::B_NAVIGATE, GUI::NavigateTexture, 100,300,COL_MAGENTA);
    SETUP_BUTTON(p,ButtonType
::B_NEXT,GUI::NextTexture,200,300,COL_CYAN);
    SETUP_BUTTON(p,ButtonType
::B_SAVE,GUI::SaveTexture,300,300,COL_RED);
    SETUP_BUTTON(p,ButtonType
::B_STOP,GUI::StopTexture,400,300,COL_BLUE);
    SETUP_BUTTON(p,ButtonType
::B_TOOLS,GUI::ToolsTexture,500,300,COL_YELLOW);


//PropertyTest();
if ( TestHovering ) SetUpHovering();
if ( TestDragging ) SetUpDragging();
#endif

}

void ButtonTest_1 :: SetUpHovering()
{

    GUI::IButton * foo = ButtonMap[ButtonType::B_PLAIN].get();
    HoverPtr bar = static_cast<GUI::IHover*>(static_cast<GUI::xButton*>(   foo) );
    TestHover.push_back(bar);


    foo = ButtonMap[ButtonType::B_FILE].get();
    bar = static_cast<GUI::IHover*>(static_cast<GUI::xButton*>(   foo) );
    TestHover.push_back(bar);


    foo = ButtonMap[ButtonType::B_MENU].get();
    bar = static_cast<GUI::IHover*>(static_cast<GUI::xButton*>(   foo) );
    TestHover.push_back(bar);

    for(auto it = TestHover.begin(); it != TestHover.end(); it++)
        (*it)->EnableHovering();
}


void ButtonTest_1 :: SetUpDragging()
{

    GUI::IButton * foo = ButtonMap[ButtonType::B_NEXT].get();
    DragPtr bar = static_cast<GUI::IDrag*>(static_cast<GUI::xButton*>(   foo) );
    TestDrag.push_back(bar);

    foo = ButtonMap[ButtonType::B_EDIT].get();
    bar = static_cast<GUI::IDrag*>(static_cast<GUI::xButton*>(foo) );
    TestDrag.push_back(bar);

    foo = ButtonMap[ButtonType::B_SETTINGS].get();
    bar = static_cast<GUI::IDrag*>(static_cast<GUI::xButton*>(foo) );
    TestDrag.push_back(bar);

    for(auto it = TestDrag.begin(); it != TestDrag.end(); it++)
        (*it)->EnableDragging();
}



void ButtonTest_1 :: ImplementHovering()
{
    //if ( event.MouseMoved )
    if ( event.type == sf::Event::MouseMoved )
    {
        for(auto it = TestHover.begin(); it != TestHover.end(); it++)
            (*it)->Hover(window);

    }
}

void ButtonTest_1 :: ImplementDragging()
{
    if ( event.MouseMoved )
    {
        DEBUG_MESSAGE
                std::cout << " Size = " << TestDrag.size() << std::endl;
        for(auto it = TestDrag.begin(); it != TestDrag.end(); it++)
            (*it)->Drag( window );
            //(*it)->Drag( WINDOW_POSITION );
    }
}


void ButtonTest_1 :: ImplementDraggingAndHovering()
{
    float window_x = window->getPosition().x;
    float window_y = window->getPosition().y;

    sf::Vector2i mousePos = sf::Mouse::getPosition();
    for(auto it= ButtonMap.begin(); it != ButtonMap.end(); it++)
    {
        sf::Sprite & obj = *(it->second);

        HoverPtr hp = static_cast<GUI::IHover*>( (static_cast<GUI::xButton*>( it->second.get() ) ) );
        hp->Hover(window);


        DragPtr dp = static_cast<GUI::IDrag*>( (static_cast<GUI::xButton*>(it->second.get() ) ) );
        dp->Drag(window);
    }
}



ButtonTest_1::ButtonType::code ButtonTest_1 ::  MapNumericKeyToButton(sf::Keyboard::Key key)
{    
    switch(key)
    {


    case sf::Keyboard::Num1: return ButtonType::B_BACK | ButtonType::B_FILE;

    case sf::Keyboard::Num2: return ButtonType::B_CANCEL | ButtonType::B_NAVIGATE;

    case sf::Keyboard::Num3: return ButtonType::B_SAVE| ButtonType::B_NAVIGATE;

    case sf::Keyboard::Num4:  return ButtonType::B_SETTINGS | ButtonType::B_TOOLS | ButtonType::B_PLAIN;

    case sf::Keyboard::Num5:  return ButtonType::B_MENU | ButtonType::B_BACK | ButtonType::B_EDIT | ButtonType::B_STOP;


    case sf::Keyboard::Num6: return ButtonType::B_PLAIN;
/*
    case sf::Keyboard::Num7: return ButtonType::B_CIRCLE | ButtonType::B_PICK_COLOR | ButtonType::B_HOME;

    case sf::Keyboard::Num8: return ButtonType::B_HOME | ButtonType::B_PENCIL | ButtonType::B_CIRCLE | ButtonType::B_NEWBUTTON;

    case sf::Keyboard::Num9: return ButtonType::B_SQUARE | ButtonType::B_LINE | ButtonType::B_xBUTTON;

    case sf::Keyboard::Num0: return ButtonType::B_FILE | ButtonType::B_BOLD | ButtonType::B_NEWBUTTON;

    //case sf::Keyboard::P : return ButtonType::B_NEWBUTTON;
*/
    default: return ButtonType::NONE;
}


}



void ButtonTest_1 :: InsidePollingImpl()
{
    auto mappedCode = MapNumericKeyToButton(event.key.code);

    auto ButtonPress = [&] (ButtonTest_1::ButtonType::code _code)-> void
    {
        for(auto it = ButtonMap.begin(); it != ButtonMap.end(); it++ )
           if ( it->first == (_code & it->first) ) it->second->Press();

    };

    auto ButtonRelease = [&] (ButtonType::code _code)-> void
    {
      for(auto it = ButtonMap.begin(); it != ButtonMap.end(); it++ )
          if ( it->first == ( _code & it->first ) ) it->second->Release();

    };

    if ( event.type == sf::Event::KeyPressed && mappedCode != ButtonType::NONE)
    {
        ButtonPress( mappedCode );
    }

    if( event.type == sf::Event::KeyReleased && mappedCode != ButtonType::NONE )
    {
        ButtonRelease( mappedCode);
    }

    //if ( TestHovering )  ImplementHovering();
    //if ( TestDragging ) ImplementDragging();
    if(TestDragging || TestHovering) ImplementDraggingAndHovering();


    if( event.type == sf::Event::MouseMoved )
    {
        int Mx = event.mouseMove.x;
        int My = event.mouseMove.y;
    }



    window->clear(COL_BLACK);
 //   std::for_each(ButtonMap.begin(), ButtonMap.end(), [&] (std::map<ButtonType::code, ButtonPtr>::value_type & item)->void { window->draw( *(item.second) );} );    

    for(auto it = ButtonMap.begin(); it != ButtonMap.end(); it++)
    window->draw( *(it->second) );
    window->display();

}

void ButtonTest_1 :: NoDisplayFunction()
{

    //throw "Not Implemented";
    //if(TestDragging || TestHovering) ImplementDraggingAndHovering();

    std::cout << "Press any P to press NewButton Images, R to release and anything else to break" << std::endl;
    char press;
    while ( std::cin >> press )
    {
        std::cout << "Press Button";

        if(TestDragging || TestHovering) ImplementDraggingAndHovering();
    }

}

void ButtonTest_1 :: CleanUp()
{
    window->close();
}

#endif


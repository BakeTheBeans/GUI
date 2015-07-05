    #ifndef UNITTEST_H
#define UNITTEST_H

#include "define.h"
#include "ScartchMe.h"

#if(SCRATCH_TEST)
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "drawableshapes.h"
#include "mouseprojector.h"

#else
#include "button.h"
//#include "buttontypes.h"
#include <memory>
#include <map>
#endif


#if(MENUBAR_TEST)
#include "button.h"
#include "menu.h"
#include "factory.h"
#include <memory>
#define _S(arg) std::shared_ptr<GUI::IButton>((arg))

#endif

#if(TEXTBOX_TEST)
#include "textbox.h"
#endif

#if(SCROLLBAR_TEST)
#include "tools.h"
#endif

#if(DIRECTORY_MENU_TEST)
#include "directorymenu.h"
#endif

#if(MENUTILES_TEST)
#include "textmenutiles.h"
#include "Utility.h"
#endif

#if(SCROLLWINDOW_TEST)
#include "window.h"
#endif

#if(SCROLLABLETEXTWINDOW_TEST)
#include "window.h"
#endif

#if(MENUPAGE_TEST)
#include "menupage.h"
#include "window.h"
#endif

#if(DIRECTORYMENUPAGE_TEST)
#include "directorymenupage.h"
#endif

#if(DRAW_TEST)
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "drawableshapes.h"
#include "mouseprojector.h"
#include "shapefactory.h"
#include "drawingpage.h"
#include "window.h"
#endif

#if(DRAW_APPLICATION_TEST)
#include "drawapp.h"
#endif

#define NO_DISPLAY 0
#define U_BUTTON_PRESS(arg) event.key.code == sf::Keyboard::arg

#if(BUTTON_TEST_4)
#define SETUP_BUTTON(ButPtr,Type, Icon, PosX,PosY,Color ) \
            ButPtr = CreateButton<Icon>(Type); \
            ButPtr->scale(0.35,0.35); \
            ButPtr->setPosition(PosX,PosY); \
            ButPtr->setColor(Color);

#endif


#define MousePositionRelativeToWindow(window) sf::Vector2i( (sf::Mouse::getPosition().x - window->getPosition().x ), (sf::Mouse::getPosition().y - window->getPosition().y ) );




namespace {
class RenderWindow;
class Event;
}



class UnitTest
{

protected:
    sf::Event & event;
    sf::RenderWindow * window;

public:    

       UnitTest(sf::Event & _event);
       virtual ~UnitTest()
       {           
           if ( window ) delete window;
       }

       sf::RenderWindow * getWindowHandle() { return window; }
       sf::Event & getEvent() { return event; }


       virtual void SetUpEnvironment()=0;
       virtual void InsidePollingImpl()=0;
       virtual void DisplayObjects()=0;

       virtual void CleanUp()
       {
           DEBUG_MESSAGE
#if(!NO_DISPLAY)
           window->close();
#endif
       }
       virtual void NoDisplayFunction(){}
};


#if(SCRATCH_TEST)
class  ScratchTest : public UnitTest
{

    //******Create your variables here to **********

    Draw::IDrawableShapes * p;
    //static Draw::MouseProjector mp;
    bool flag;
    //**********************************************

public:
     ScratchTest(sf::Event & _event) : UnitTest(_event)
     {


     }

     ~ScratchTest()
     {
          if(p) delete p;
     }

     virtual void SetUpEnvironment();
     virtual void InsidePollingImpl();
     //virtual void CleanUp();
     virtual void DisplayObjects();
     virtual void NoDisplayFunction();
};
#endif

#if(DRAW_APPLICATION_TEST)
class DrawAppTest : public UnitTest
{

    //******Create your variables here to **********
    Draw::DrawApp app;

    //**********************************************

public:
     DrawAppTest(sf::Event & _event) : UnitTest(_event), app()
     {      

     }

     ~DrawAppTest ()
     {
        DEBUG_MESSAGE
     }

     virtual void SetUpEnvironment();
     virtual void InsidePollingImpl();
     virtual void DisplayObjects();
     virtual void NoDisplayFunction();
};
#endif




#if(DRAW_TEST)



class  DrawTest : public UnitTest
{

    //******Create your variables here to **********
#if(Test_1)
    Draw::IDrawableShapes * p;
    bool flag;
#elif(Test_2)

    Draw::DrawingPage *page, *page1;

    GUI::ScrollableWindow<Draw::DrawingPage> * scrollWindow;
    bool flags[3];
    bool flag;


#elif(Test_3)
#if(NEW_DEBUG || NO_DISPLAY)
    Draw::DrawingPage page;
    GUI::ScrollableWindow<Draw::DrawingPage> * scrollWindow;
#endif
#endif
    //bool flag;
    //**********************************************

public:
#if(Test_1)
    DrawTest(sf::Event & _event) : UnitTest(_event), p(0), flag(false)
#elif(Test_2)
    DrawTest(sf::Event & _event) : UnitTest(_event), page(), page1(), flags(), flag(false)
  #elif(Test_3)
    DrawTest(sf::Event & _event) : UnitTest(_event), page(), scrollWindow(0)
#endif
     {
#if(Test_2)
            flags[0] = flags[1] = false;
            flags[2] = true;
            scrollWindow = new GUI::ScrollableWindow<Draw::DrawingPage>();
#endif

#if(Test_3)
            scrollWindow = new GUI::ScrollableWindow<Draw::DrawingPage>(page);
#endif
     }




     ~DrawTest()
     {
//          if(p) delete p;
     }

     virtual void SetUpEnvironment();
     virtual void InsidePollingImpl();
     virtual void DisplayObjects();
     virtual void NoDisplayFunction();
};


#endif

#if(DIRECTORYMENUPAGE_TEST)
class  DirectoryMenuPageTest : public UnitTest
{

    //******Create your variables here to **********

    GUI::DirectoryMenuPage menuPage;
#if(SCROLL_WINDOW)
    GUI::ScrollableWindow<GUI::DirectoryMenuPage> * menuPageWindow;
#endif
    //**********************************************

public:
     DirectoryMenuPageTest(sf::Event & _event) : UnitTest(_event)
     {
#if(SCROLL_WINDOW)
         menuPageWindow = new GUI::ScrollableWindow<GUI::DirectoryMenuPage>(menuPage);
#endif
     }

     ~DirectoryMenuPageTest()
     {

     }

     virtual void SetUpEnvironment();
     virtual void InsidePollingImpl();
     //virtual void CleanUp();
     virtual void DisplayObjects();
    virtual void NoDisplayFunction();
};
#endif


#if(MENUPAGE_TEST)


class MenuPageTest : public UnitTest
{
    GUI::MenuPage menuPage;
    std::vector<std::string> konoha = {
        "Naruto Uzumaki",
        "Sasuke Uchiha",
        "Madara Uchiha",
        "Shisui Uchiha",
        "Sakura Haruno",
        "Ten Ten",
        "Gaara",
        "Orochimaru",
        "Minato Namikawa",
        "Kakashi Hatake",
        "Jiraiya",
        "Shikamaru Nara",
        "Choji Akimichi"
    };

#if(SCROLL_WINDOW)
    GUI::ScrollableWindow<GUI::MenuPage> * menuWindow;
#endif

public:
     MenuPageTest(sf::Event & _event) : UnitTest(_event), menuPage()
     {
        #if(SCROLL_WINDOW)
           menuWindow = new GUI::ScrollableWindow<GUI::MenuPage>(menuPage);
        #endif
     }

     virtual ~MenuPageTest()
     {

     }

     virtual void SetUpEnvironment();
     virtual void InsidePollingImpl();
     //void CleanUp() {}
     virtual void DisplayObjects();
     void NoDisplayFunction() {}
};


#endif




#if(SCROLLABLETEXTWINDOW_TEST)
typedef GUI::ScrollableWindow<GUI::TextBox> ScrollableTextWindow;

class ScrollableTextWindowTest : public UnitTest
{
    GUI::TextBox textBox;
    ScrollableTextWindow  * sWindow;

public:
     ScrollableTextWindowTest(sf::Event & _event) : UnitTest(_event), textBox(), sWindow(0)
     {
         sWindow = new GUI::ScrollableWindow<GUI::TextBox>(textBox);
     }

     virtual ~ScrollableTextWindowTest()
     {
         if ( sWindow) delete sWindow;
     }

     virtual void SetUpEnvironment();
     virtual void InsidePollingImpl();
     //virtual void CleanUp();
     virtual void DisplayObjects();
     void NoDisplayFunction() {}
};


#endif


#if(SCROLLWINDOW_TEST)
class  ScrollableWindowTest : public UnitTest
{

    GUI::ScrollableWindow  scrollWindow;


public:
     ScrollableWindowTest (sf::Event & _event) : UnitTest(event) {}


     virtual ~ScrollableWindowTest() {  }
     virtual void SetUpEnvironment();
     virtual void InsidePollingImpl();
     //virtual void CleanUp();
     virtual void DisplayObjects();
     void NoDisplayFunction() {}
};


#endif




#if(MENUTILES_TEST)
class  MenuTilesTest : public UnitTest
{

    GUI::MenuTiles * menuTile;


public:
     MenuTilesTest (sf::Event & _event);


     virtual ~MenuTilesTest() { if(menuTile) delete menuTile; }
     virtual void SetUpEnvironment();
     virtual void InsidePollingImpl();
     //virtual void CleanUp();
     virtual void DisplayObjects();
     void NoDisplayFunction();
};


#endif

#if(DIRECTORY_MENU_TEST)

class  DirectoryMenuTest : public UnitTest
{

    GUI::DirectoryMenu dirMenu;


public:
     DirectoryMenuTest(sf::Event & _event) : UnitTest(_event), dirMenu()
     {

     }

     virtual void SetUpEnvironment();
     virtual void InsidePollingImpl();
     virtual void CleanUp();
     virtual void DisplayObjects();

};


#endif


#if(SCROLLBAR_TEST)
class  ScrollBarTest : public UnitTest
{

private:
#if(Test_1 || Test_2 | Test_3 || Test_4 )
    GUI::ScrollBar scrollBar{ GUI::internal::Vertical, 20, 300,5};
#else
    GUI::ScrollBar scrollBar{ GUI::internal::Horizontal,300,20,5};
#endif
public:
     ScrollBarTest (sf::Event & _event) : UnitTest(_event)
     {

     }

     virtual void SetUpEnvironment();
     virtual void InsidePollingImpl();
//     virtual void CleanUp();
     virtual void DisplayObjects();

};


#endif


#if(TEXTBOX_TEST)
class  TextBoxTest : public UnitTest
{

    GUI::TextBox textBox;

public:
     TextBoxTest(sf::Event & _event) : UnitTest(_event), textBox()
     {

     }

     virtual void SetUpEnvironment();
     virtual void InsidePollingImpl();
     virtual void CleanUp();
     virtual void DisplayObjects();
     virtual void NoDisplayFunction();

};

#endif

#if(MENUBAR_TEST)
class  MenuBarTest : public UnitTest
{

    GUI::MenuBar * newBar;
    GUI::MenuBar * newBranch;
    GUI::MenuBar *bar;

public:

    MenuBarTest(sf::Event & _event) : UnitTest(event), newBar(0), newBranch(0) {}

    ~MenuBarTest()
    {
        if ( newBar) delete newBar;
        if ( newBranch) delete newBranch;
        if (bar) delete bar;
    }
    virtual void SetUpEnvironment();
     virtual void InsidePollingImpl();
     virtual void CleanUp();
     virtual void DisplayObjects();

};
#endif




#if(BUTTON_TEST)
class  ButtonTest_1 : public UnitTest
{

const int NUM_OF_BUTTONS = 12;
public:
bool TestHovering;
bool TestDragging;

public:
    /*
     * This enum type must exist in the Button Class itself
     * but since I'm likely to add more button types and more
     * features I'm definig the enum in this test class.
     * THIS HAS TO BE MOVED OUT THOUGH
     */

    struct ButtonType
    {
        enum code
        {

#if(BUTTON_TEST_4)
            NONE      =     0,
            B_PLAIN  =   1 << 0,
            B_FILE     =   1 << 1,
            B_CANCEL    =  1 << 2,
            B_STOP  =  1 << 3,
            B_EDIT    =  1 << 4,
            B_SETTINGS   =  1 << 5,
            B_MENU   =   1 << 6,
            B_TOOLS =   1 << 7,
            B_NAVIGATE   =    1 << 8,
            B_SAVE =    1 << 9,
            B_NEXT = 1 << 10,
            B_BACK   =  1 << 11,

#endif
            //Can't have more than 32 with enum represented as int
        };

        friend code operator|(const code & left, const code & right)
        {
            return static_cast<code>(int(left) + int(right));
        }

    };


typedef std::unique_ptr<GUI::IButton> ButtonPtr;

private:
    //std::vector<ButtonPtr> ButtonList;
    std::map<ButtonType::code, ButtonPtr> ButtonMap;


//#if(BUTTON_TEST_3))
    template<typename TIcon>
    GUI::IButton * CreateButton(ButtonType::code _buttonCode)
    {
        auto it = ButtonMap.find(_buttonCode);
        //ButtonList.push_back(ButtonPtr(p));
        if ( it == ButtonMap.end() )
        {

            GUI::IButton * p = new GUI::Button<TIcon>();
            ButtonMap.insert(std::make_pair(_buttonCode, ButtonPtr(p) ));
            return p;
        }
        else
        {
            return it->second.get();
        }
    }

//#endif


    /*
     * Maps numeric keys 0,1,2.. to ButtonTypes
     * Avoids alphbetic keys.
     */
    ButtonType::code MapNumericKeyToButton(sf::Keyboard::Key);

protected:
    typedef GUI::IHover * HoverPtr;
    typedef GUI::IDrag * DragPtr;

    std::vector<HoverPtr> TestHover;
    std::vector<DragPtr> TestDrag;


    void SetUpHovering();
    void ImplementHovering();
    void SetUpDragging();
    void ImplementDragging();
    void ImplementDraggingAndHovering();

public:
    ButtonTest_1(sf::Event & _event) : UnitTest(_event), ButtonMap() {}
    virtual void SetUpEnvironment();
    virtual void InsidePollingImpl();
    virtual void CleanUp();
    virtual void NoDisplayFunction();


};


#endif

#endif // UNITTEST_H

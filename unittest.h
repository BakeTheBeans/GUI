#ifndef UNITTEST_H
#define UNITTEST_H
#include "define.h"
#include "button.h"
//#include "buttontypes.h"
#include <memory>
#include <map>

//#include <typeinfo>
#define NO_DISPLAY 0
#define U_BUTTON_PRESS(arg) event.key.code == sf::Keyboard::arg
#if(BUTTON_TEST_3)
#define SETUP_BUTTON(ButPtr,Type, Icon, PosX,PosY,Color ) \
            ButPtr = CreateButton<Icon>(Type); \
            ButPtr->setPosition(PosX,PosY); \
            ButPtr->setColor(Color);
#endif

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
    sf::RenderWindow * window;
    sf::Event & event;

public:    

       UnitTest(sf::Event & _event);
       ~UnitTest()
       {
           if ( window ) delete window;
       }

       sf::RenderWindow * getWindowHandle() { return window; }
       sf::Event & getEvent() { return event; }

       virtual void SetUpEnvironment()=0;
       virtual void InsidePollingImpl()=0;
       virtual void CleanUp()=0;
       virtual void NoDisplayFunction(){}
};



class  ScratchTest : public UnitTest
{

    //******Create your variables here to **********

    sf::Font font;
    sf::Sprite Menu;
    sf::Text message;
    //**********************************************

public:
     ScratchTest(sf::Event & _event) : UnitTest(_event)
     {
         if ( !font.loadFromFile("/home/rohit/Projects/Draw/Texture/XeroxSansSerifWideOblique.ttf") ) throw " Could not load font file";

     }

     virtual void SetUpEnvironment();
     virtual void InsidePollingImpl();
     virtual void CleanUp();

};



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
#if(BUTTON_TEST_3)
            NONE      =     0,
            B_NORMAL  =   1 << 0,
            B_ARC     =   1 << 1,
            B_BOLD    =  1 << 2,
            B_CIRCLE  =  1 << 3,
            B_FILE    =  1 << 4,
            B_FONT   =  1 << 5,
            B_HOME   =   1 << 6,
            B_ITALIC =   1 << 7,
            B_LINE   =    1 << 8,
            B_PENCIL =    1 << 9,
            B_PICK_COLOR = 1 << 10,
            B_POLYGON   =  1 << 11,
            B_SEARCH   =   1  << 12,
            B_SQUARE   =   1 << 13,
            B_TRASH   =     1 << 14,
#endif

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
#if(BUTTON_TEST_3)
            B_NEWBUTTON  =   1 << 15,
            B_xBUTTON    =   1 << 16,
            B_xARC       =   1 << 17
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




#endif // UNITTEST_H

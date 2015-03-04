#include "unittest.h"
#include "button.h"
#include <algorithm>
#include "buttonicons.h"


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#define WINDOW_POSITION window->getPosition().x, window->getPosition().y

#if(SCRATCH_TEST)
#include "Utility.h"
#include <string>

#endif

UnitTest::UnitTest(sf::Event & _event) : event(_event)
{

    window = new sf::RenderWindow(sf::VideoMode(800,600), "UnitTest Window", sf::Style::Resize | sf::Style::Close);
#if(NO_DISPLAY)
    window->close();
    std::cout << "You are running in NO DISPLAY mode possibly for debugging";
#endif
}

/*
template<typename TIcon>
GUI::IButton* ButtonTest_1 :: CreateButton()
{
    IButton * p = new GUI::Button<TIcon>();
    ButtonList.push_back(ButtonPtr(p));
    return p;
}

template GUI::IButton* ButtonTest_1::CreateButton<void>();
template GUI::IButton* ButtonTest_1::CreateButton<GUI::ArcIcon>();


template GUI::IButton* ButtonTest_1::CreateButton<GUI::AttachmentIcon>();
template GUI::IButton* ButtonTest_1::CreateButton<GUI::BoldIcon>();
template GUI::IButton* ButtonTest_1::CreateButton<GUI::CircleIcon>();
template GUI::IButton* ButtonTest_1::CreateButton<GUI::FileIcon>();
template GUI::IButton* ButtonTest_1::CreateButton<GUI::FontIcon>();
template GUI::IButton* ButtonTest_1::CreateButton<GUI::HomeIcon>();
template GUI::IButton* ButtonTest_1::CreateButton<GUI::ItalicIcon>();
template GUI::IButton* ButtonTest_1::CreateButton<GUI::LineIcon>();
template GUI::IButton* ButtonTest_1::CreateButton<GUI::PencilIcon>();
template GUI::IButton* ButtonTest_1::CreateButton<GUI::PickColorIcon>();
template GUI::IButton* ButtonTest_1::CreateButton<GUI::PolygonIcon>();
template GUI::IButton* ButtonTest_1::CreateButton<GUI::SearchIcon>();
template GUI::IButton* ButtonTest_1::CreateButton<GUI::SquareIcon>();
template GUI::IButton* ButtonTest_1::CreateButton<GUI::TrashIcon>();
*/



void ScratchTest :: SetUpEnvironment()
{
    sf::Texture * MenuTexture = GUI::ResourceManager::getTexture( "MenuBox" );



//    font.loadFromFile("/home/rohit/Projects/Draw/Texture/LiberationMonoBold.ttf");
    message.setString(std::string( "WARNING!"));
    message.setPosition(250,250);
    message.setFont(font);
    message.setColor(COL_BLUE);
    message.setStyle(sf::Text::Bold);
    message.setCharacterSize(10);

    Menu.setTexture(*MenuTexture);
    Menu.setPosition(200,200);
    Menu.scale(1.5,1.5);
}

void ScratchTest :: InsidePollingImpl()
{

    window->clear();
    //window->draw(Menu);
    window->draw(message);
    window->display();
}

void ScratchTest :: CleanUp()
{
    window->close();

}


void ButtonTest_1 :: SetUpEnvironment()
{

    TestHovering = true;
    TestDragging = true;

#if(BUTTON_TEST_3)
    GUI::IButton * p = 0;
    SETUP_BUTTON(p,ButtonType
::B_NORMAL,void,600,100,COL_GREEN);
    SETUP_BUTTON(p,ButtonType
::B_ARC,GUI::ArcIcon,200,100,COL_MAGENTA);
    SETUP_BUTTON(p,ButtonType
::B_BOLD,GUI::BoldIcon, 300,100,COL_CYAN);
    SETUP_BUTTON(p,ButtonType
::B_CIRCLE,GUI::CircleIcon, 300,100,COL_RED);
    SETUP_BUTTON(p,ButtonType
::B_FILE,GUI::FileIcon,400,100,COL_BLUE);
    SETUP_BUTTON(p,ButtonType
::B_FONT,GUI::FontIcon,500,100,COL_YELLOW);
    SETUP_BUTTON(p,ButtonType
::B_HOME,GUI::HomeIcon,600,300,COL_GREEN);
    SETUP_BUTTON(p,ButtonType
::B_ITALIC, GUI::ItalicIcon, 100,300,COL_MAGENTA);
    SETUP_BUTTON(p,ButtonType
::B_LINE,GUI::LineIcon,200,300,COL_CYAN);
    SETUP_BUTTON(p,ButtonType
::B_PENCIL,GUI::PencilIcon,300,300,COL_RED);
    SETUP_BUTTON(p,ButtonType
::B_PICK_COLOR,GUI::PickColorIcon,400,300,COL_BLUE);
    SETUP_BUTTON(p,ButtonType
::B_POLYGON,GUI::PolygonIcon,500,300,COL_YELLOW);
    SETUP_BUTTON(p,ButtonType
::B_SEARCH,GUI::SearchIcon,300,500,COL_GREEN);
    SETUP_BUTTON(p,ButtonType
::B_SQUARE,GUI::SquareIcon,100,500,COL_MAGENTA);
    SETUP_BUTTON(p,ButtonType
::B_TRASH,GUI::TrashIcon,200,500,COL_BLUE);


#if(DEBUG)
 GUI::IButton * q = new GUI::NewButton();
 q->setPosition(400,400);
 q->scale(0.5,0.5);
 ButtonMap.insert(std::make_pair(ButtonType::B_NEWBUTTON,ButtonPtr(q)) );
#endif
 q = new GUI::Button<GUI::PlainTexture>();
 q->setPosition(100,400);
 //q->setColor(COL_BLUE);
 q->scale(0.5,0.5);
 ButtonMap.insert(std::make_pair(ButtonType::B_xBUTTON, ButtonPtr(q) ));

 q = new GUI::IconButton<GUI::ArcIcon>();
 q->setPosition(250,400);
 q->scale(0.5,0.5);
 //q->setColor(COL_BLUE);
 ButtonMap.insert(std::make_pair(ButtonType::B_xARC, ButtonPtr(q) ));



    std::for_each(ButtonMap.begin(), ButtonMap.end(), [] (std::pair<const ButtonType::code, ButtonPtr> & item)->void
    {item.second->scale(0.8,0.8);} );
#endif

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
#if(BUTTON_TEST_3)
    case sf::Keyboard::Num1: return ButtonType::B_ARC | ButtonType::B_FILE | ButtonType::B_BOLD | ButtonType::B_xARC;

    case sf::Keyboard::Num2: return ButtonType::B_LINE | ButtonType::B_ITALIC;
    case sf::Keyboard::Num3: return ButtonType::B_CIRCLE| ButtonType::B_HOME;

    case sf::Keyboard::Num4:  return ButtonType::B_SQUARE | ButtonType::B_PENCIL | ButtonType::B_FONT;

    case sf::Keyboard::Num5:  return ButtonType::B_SEARCH | ButtonType::B_NORMAL | ButtonType::B_POLYGON | ButtonType::B_PENCIL;

    case sf::Keyboard::Num6: return ButtonType::B_SQUARE | ButtonType::B_FILE;

    case sf::Keyboard::Num7: return ButtonType::B_CIRCLE | ButtonType::B_PICK_COLOR | ButtonType::B_HOME;

    case sf::Keyboard::Num8: return ButtonType::B_HOME | ButtonType::B_PENCIL | ButtonType::B_CIRCLE | ButtonType::B_NEWBUTTON;

    case sf::Keyboard::Num9: return ButtonType::B_SQUARE | ButtonType::B_LINE | ButtonType::B_xBUTTON;

    case sf::Keyboard::Num0: return ButtonType::B_FILE | ButtonType::B_BOLD | ButtonType::B_NEWBUTTON;

    //case sf::Keyboard::P : return ButtonType::B_NEWBUTTON;

    default: return ButtonType::NONE;
#endif


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




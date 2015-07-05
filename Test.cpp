#include <iostream>
#include "define.h"
#include "ScartchMe.h"
#include <algorithm>
#include <iterator>
#include <cmath>

#define STOP_ON_PRESSING_SPACEBAR if ( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space )\
{\
    running = false;\
}

//#define SCRATCH 1

#if(SCRATCH)
#include "Scratch.h"
#else
#include "Utility.h"
#include "unittest.h"
#include "drawapp.h"
#endif


int main()
{


#if(SCRATCH)

    std::vector<int> foo = {1,45,78,100,56,298.190,2876};
    std::min(foo.begin(),foo.end());

#else
    sf::Event event;
    UnitTest * Test = 0;
    try
    {

        GUI::ResourceManager::RegisterResources();
    }

    catch(const char * ss)
    {        
        std::cout << ss << std::endl;
    }


try{

#if(SCRATCH_TEST)
        Test = new ScratchTest(event);
#elif(BUTTON_TEST)
        Test = new ButtonTest_1(event);
#elif(MENUBAR_TEST)
        Test = new MenuBarTest(event);
#elif(TEXTBOX_TEST)
        Test = new TextBoxTest(event);
#elif(SCROLLBAR_TEST)
        Test = new ScrollBarTest(event);
#elif(DIRECTORY_MENU_TEST)
        Test = new DirectoryMenuTest(event);
#elif(MENUTILES_TEST)
        Test = new MenuTilesTest(event);
#elif(SCROLLWINDOW_TEST)
        Test = new ScrollableWindowTest(event);
#elif(SCROLLABLETEXTWINDOW_TEST)
        Test = new ScrollableTextWindowTest(event);
#elif(MENUPAGE_TEST)
        Test = new MenuPageTest(event);
#elif(DIRECTORYMENUPAGE_TEST)
        Test = new DirectoryMenuPageTest(event);
#elif(DirectoryMenuTest)
       Test = new DirectoryMenuTest(event);
#elif(DRAW_TEST)
       Test = new DrawTest(event);
#elif(DRAW_APPLICATION_TEST)
       Test = new DrawAppTest(event);
#elif(DRAW_APP)
        Test = new Draw::DrawApp(event);
#endif

               Test->SetUpEnvironment();

    bool running = true;
    int _count = 0;
    while(running)
    {
        _count++;
        //if ( _count == 3) running = false;
#if(!NO_DISPLAY)
        while( Test->getWindowHandle()->pollEvent(event) )
        {
            DEBUG_MESSAGE
            STOP_ON_PRESSING_SPACEBAR;
            Test->InsidePollingImpl();           
        }

        Test->DisplayObjects();
#else
        Test->NoDisplayFunction();
        break;
#endif

    }
}
    catch(const char * ss)
    {
        std::cout << ss << std::endl;
    }

    Test->CleanUp();
    DEBUG_MESSAGE
    delete Test;
    DEBUG_MESSAGE

    GUI::ResourceManager::Dispose();
    DEBUG_MESSAGE
#endif

    return 0;

}



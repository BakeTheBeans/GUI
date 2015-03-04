#include <iostream>
#include "define.h"

#define STOP_ON_PRESSING_SPACEBAR if ( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space )\
{\
    running = false;\
}



#if(SCRATCH)
#include "Scratch.h"
//#include "Utility.h"
#else
#include "Utility.h"
#include "unittest.h"
#endif

int main()
{
#if(SCRATCH)
/*
    const char * filename = "/home/rohit/Projects/Draw/Texture/Resource.xml";

try{
    GUI::xmlParser xml(filename);
    xml.OpenDocument();
    xml.Enter("Button");
    GUI::ResourceNode * p = 0;

    while( (p = xml.getNext()) )
    {
            std::cout << xml.key << std::endl;
            std::cout << p->filename << std::endl;
            std::cout << p->description << std::endl;

    }



}
    catch(const char * ss)
    {
        std::cerr << ss << std::endl;
    }
*/

    Foo TestFoo;
    //TestFoo.Add(new Dog(10)).Add(new Cat(4)).Add(new Cow(8)).Add(new Dog(6)).Add(new Cat(9)).Add(newDog(12)).Add(new Cow(3));

    TestFoo.Add(new Canine(new Dog(10))).Add(new Feline(new Cat(10))).Add(new Bovine(new Cow(10)));
    TestFoo.getResource<Bovine>(2)->Print();





#else
    sf::Event event;
    UnitTest * Test = 0;
    try{
        GUI::ResourceManager::RegisterResources();
    }

    catch(const char * ss)
    {
        std::cout << ss << std::endl;
    }


try{

#if(SCRATCH_TEST)
        Test = new ScratchTest(event);
#else
    Test = new ButtonTest_1(event);
#endif

    Test->SetUpEnvironment();
    bool running = true;

    while(running)
    {
        while( Test->getWindowHandle()->pollEvent(event) )
        {
            STOP_ON_PRESSING_SPACEBAR;
            Test->InsidePollingImpl();           
        }

#if(NO_DISPLAY)
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
    delete Test;

#endif

    return 0;

}

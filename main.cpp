#include <iostream>
#include "Utility.h"
#define TEST 0

#if(TEST)
#define BUTTON_TEST_1 0
#define BUTTON_TEST_2 0
#include <SFML/Graphics.hpp>
#endif

#if(BUTTON_TEST_1)
#include "button.h"
#endif


#if(BUTTON_TEST_2)
#include "button.h"
#endif

#if(BUTTON_TEST_3)
#include "button.h"
#endif

#include <cctype>
#include <string>
#include <algorithm>

using namespace std;

int main()
{


    sf::RenderWindow window(sf::VideoMode(600,600),"Press space to exit");
    sf::Event event;
#if(TEST)
    sf::Texture buttonTexture;
    sf::Texture pressedButtonTexture;

    buttonTexture.loadFromFile("button.png",sf::IntRect(0,108,100,35));
    pressedButtonTexture.loadFromFile("button.png", sf::IntRect(105,145,100,35));


    sf::Sprite button;
    sf::Sprite pressedbutton;


    button.setTexture(buttonTexture,true);
    pressedbutton.setTexture(pressedButtonTexture);
    button.setPosition(100,100);
    pressedbutton.setPosition(100,100);
    button.setColor(sf::Color(255,255,255));
    pressedbutton.setColor(sf::Color(255,255,255));

    sf::Sprite * Button = &button;

#endif

#if(BUTTON_TEST_1)


    GUI::NormalButton normalButton;

    std::cout << "pressed state = " << normalButton._pressed <<std::endl;

    //normalButton.setPosition(200,200);
#endif

#if(BUTTON_TEST_2)

    std::cout <<"Enter four numbers " << std::endl;
    int i,j,k,l;
    std::cin >> i >> j >> k >> l;
  //  boost::tuples::tuple<int,int,int,int> region = boost::tuples::make_tuple(i,j,k,l);

  //int i=0,j=0,k=10,l=10;
    GUI::NormalButton normalButton(i,j,k,l);

    normalButton.setPosition(200,200);
    normalButton.setColor(sf::Color::Blue);
    //normalButton.scale(0.5,0.5);

  //GUI::ButtonIcons buttonIcon;
    /*
    GUI::SearchIcon buttonIcon;
    buttonIcon.Load(region);
    buttonIcon.setPosition(100,100);
*/

#endif

#if(BUTTON_TEST_3)
    using namespace GUI;


GUI::Button<PencilIcon> IconButton;
GUI::PlainButton NormalButton;


IconButton.setPosition(200,200);
IconButton.setColor(sf::Color::Green);
IconButton.scale(0.8,0.8);


NormalButton.setPosition(400,200);
NormalButton.setColor(sf::Color::Red);
NormalButton.scale(0.8,0.8);

GUI::NewButton newFileButton;
newFileButton.setPosition(300,300);
newFileButton.scale(0.8,0.8);

//NormalButton.deactivate();


#endif

    bool running = true;
    while ( running )
    {

        //Press spacebar to close
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ) running = false;        


        while(window.pollEvent(event))
        {
            if ( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P )
            {
#if(BUTTON_TEST_1)
                normalButton._pressed = true;
#endif
#if(BUTTON_2)
                normalButton.Press();
#endif
#if(BUTTON_TEST_3)
                IconButton.Press();
                newFileButton.Press();
#endif
            }

            if ( event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P )
            {
#if(BUTTON_TEST_1)
                normalButton._pressed = false;
#endif
#if(BUTTON_2 || BUTTON_TEST_3)
                IconButton.Release();
                newFileButton.Release();
#endif

#if(BUTTON_TEST_3)
                if ( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A )
                {
                    NormalButton.deactivate();
                }
#endif

            }
        }



#if(TEST)

        while(window.pollEvent(event))
        {
            if ( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P )
                Button = &pressedbutton;
            if ( event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P )
                Button = &button;

        }

        window.clear();
        window.draw(*Button);
        //window.draw(pressedbutton);
        window.display();

#endif


#if(BUTTON_TEST_1 || BUTTON_TEST_2 || BUTTON_TEST_3)

        window.clear(sf::Color(100,100,100));
        window.draw(IconButton);
        window.draw(NormalButton);
     //   window.draw(buttonIcon);
        window.draw(newFileButton);
        window.display();

#endif




}

    //window.close();



std::string name = "Rohit Shivaswamy";
std::transform(name.begin(), name.end(), name.begin(), [](char c)->char {return std::toupper(c);}    );

std::cout << name << std::endl;

}


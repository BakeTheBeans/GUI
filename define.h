#ifndef DEFINE_H
#define DEFINE_H
#include <iostream>

#define BUTTON_TEST_1 0
#define BUTTON_TEST_2 0
#define BUTTON_TEST_3 0
#define BUTTON_TEST_4 1

#if(BUTTON_TEST_1)
#ifndef BUTTON_1
#define BUTTON_1 1
#endif
#ifndef TEXTURE_1
#define TEXTURE_1 1
#endif
#endif

#if(BUTTON_TEST_2)
#ifndef BUTTON_2
#define BUTTON_2 1
#endif
#ifndef TEXTURE_2
#define TEXTURE_2 1
#endif
#endif

#if(BUTTON_TEST_3)
#ifndef BUTTON_3
#define BUTTON_3 1
#endif
#ifndef TEXTURE_2
#define TEXTURE_2 0
#endif
#endif

#if(BUTTON_TEST_4)
#ifndef BUTTON_4
#define BUTTON_4 1
#endif
#endif


#define SCRATCH 0
#define SCRATCH_TEST 0
#define DEBUG 0
#define EON }  // end of namespace
#define DEBUG_MESSAGE std::cerr << "I AM HERE : FIle : " << __FILE__  << "  at LINE : " << __LINE__ << std::endl;

#define PrintRectBounds(bar) std::cout << "Left : " << bar.left  << "  Right : " << bar.left + bar.width << "   Top : " << bar.top << "   Bottom : " << bar.top + bar.height << std::endl;



#if(DEBUG)
#define TM(arg) td::transform(arg.begin(), arg.end(), arg.begin(), [](char c)->char {return std::toupper(c);}  );
#endif


#define COL_GREEN sf::Color::Green
#define COL_BLUE  sf::Color::Blue
#define COL_RED   sf::Color::Red
#define COL_MAGENTA  sf::Color::Magenta
#define COL_YELLOW  sf::Color::Yellow
#define COL_CYAN    sf::Color::Cyan
#define COL_WHITE   sf::Color::White
#define COL_BLACK   sf::Color::Black
#define COL_GRAY    sf::Color(100,100,100)

#define ARC_ICON               sf::IntRect(395,440,32,32)
#define ATTACHMENT_ICON        sf::IntRect(105,295,32,32)
#define BOLD_ICON              sf::IntRect(106,487,32,32)
#define CIRCLE_ICON            sf::IntRect(250,440,32,32)
#define FILE_ICON              sf::IntRect(298,152,32,32)
#define FONT_ICON              sf::IntRect(12,487,32,32)
#define HOME_ICON              sf::IntRect(12,105,32,32)
#define ITALIC_ICON            sf::IntRect(58,487,32,32)
#define LINE_ICON              sf::IntRect(347,440,32,32)
#define PENCIL_ICON            sf::IntRect(345,100,32,32)
#define PICK_COLOR_ICON        sf::IntRect(12,437,32,32)
#define POLYGON_ICON           sf::IntRect(298,440,32,32)
#define POWER_ICON             sf::IntRect(155,295,32,32)
#define REFRESH_ICON           sf::IntRect(250,392,32,32)
#define SEARCH_ICON            sf::IntRect(345,102,32,32)
#define SQUARE_ICON            sf::IntRect(203,440,32,32)
#define TRASH_ICON             sf::IntRect(298,55,32,32)
#define BUTTON_PRESS           sf::IntRect(105,145,100,35)
#define BUTTON_RELEASE         sf::IntRect(105,0,100,35)//sf::IntRect(0,108,100,35)



#endif // DEFINE_H

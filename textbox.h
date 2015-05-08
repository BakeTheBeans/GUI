#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "define.h"
//#include "scroll.h"
#include "interfaces.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <vector>


namespace GUI {
class TextBox : public EnclosingBox, public IScrollable
{

    static const int DefaultBorderSize;
    static const sf::Color DefaultBorderColor;
    static const sf::Color DefaulTextBoxColor;
    static const float DefualtTextBoxWidth;
    static const float DefualtTextBoxHeight;
    static const float DefaultMarginSize;
    static const float DefaultCharSize;

    sf::Font * font;
    sf::Text text;
    const char * rawText;
    unsigned int numOfTextRows, rowsPerPage;

    std::vector<std::string> textChain  ;
    unsigned int charSize;
    int currentTextPos;
    unsigned int startIndex, stopIndex;
    bool flag;

public:
    bool isScrollBarVisible;

protected:
    void CalculaterowsPerPage();
    void AlignText();
    virtual void SetSize();
    virtual void SetPosition();
    void SetUpDisplay();
    void SetUpText();

public:
    TextBox(sf::Font * _font = 0, float width = DefualtTextBoxWidth, float height = DefualtTextBoxHeight,float _margin = DefaultMarginSize, int _charSize = DefaultCharSize);

    void setFont(sf::Font * _font)  { font = _font; }
    void setFontSize(int num);
    void setText(const char * _text);

    void setTextColor(sf::Color _textColor) { text.setColor(_textColor); }
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   void scrollUp(int offset);
   void scrollDown(int offset);
   void scrollRight(int offset){ throw "Not Implemented"; }
   void scrollLeft(int offset) { throw "Not Implemented"; }
   void SetUpWindowDisplay();
   int getVerticalPageSize() { return numOfTextRows; }
   int getVerticalDisplaySize() { return rowsPerPage; }
   int getHorizontalPageSize() { std::cout <<  "Not Implemeneted"; }
   int getHorizontalDisplaySize(){ std::cout <<  "Not Implemeneted"; }



};
EON
#endif // TEXTBOX_H

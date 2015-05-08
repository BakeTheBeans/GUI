#include "textbox.h"
#include <algorithm>
#include "string.h"
#include <sstream>
#include <utility>
#include "scroll.h"

#define SPACE ' '
#define HYPHEN_NEWLINE "-\n"
#define NEWLINE "\n"
#define CHAR_GAP  3



namespace GUI {

const int TextBox :: DefaultBorderSize = 4;
const sf::Color TextBox :: DefaultBorderColor = COL_GRAY;
const sf::Color TextBox :: DefaulTextBoxColor = COL_BLACK;
const float TextBox :: DefualtTextBoxWidth = 400;
const float TextBox :: DefualtTextBoxHeight = 100;
const float TextBox :: DefaultMarginSize = 10;
const float TextBox :: DefaultCharSize = 15;



TextBox :: TextBox(sf::Font * _font, float width, float height,float _margin, int _charSize) : EnclosingBox(), font(font), text(), rawText(0), numOfTextRows(0), rowsPerPage(), textChain(),  charSize(_charSize), currentTextPos(0),startIndex(0), stopIndex(0), flag(false), isScrollBarVisible(true)
{

    text.setPosition(0,0);
    if ( height && width ) this->setSize(width,height);
    else this->setSize(100,100);
}


void TextBox :: CalculaterowsPerPage()
{
    if ( font == 0) throw "No Font assigned to TextBox";
    if ( rawText == 0) throw "Null or \'0\' text not permissible";

    auto getHeightAndSpacing = [this] ()->int
    {
        sf::Text dummy("Y\nY",*font,charSize);
        int TotalHeight = dummy.getGlobalBounds().height;
        dummy.setString("Y");
        int charHeight = dummy.getGlobalBounds().height;
        return TotalHeight - charHeight;
    };

    std::string dummyString = "Y\nY";
    sf::Text dummy(dummyString,*font,charSize);
    //int charHeight = dummy.getGlobalBounds().height;
    try
    {
        int vert = getHeightAndSpacing();
       rowsPerPage = getInternalHeight()/vert;
    }

    catch(const char *ss)
    {
       throw "Limit on the rows is undefined. Either character size is bigger than text size or too small.";
    }
    if ( !stopIndex ) stopIndex = std::min<int>((int)textChain.size(), rowsPerPage-1);

}


/*
 *
 * The logic for fitting text in the box does not consider the
 * gap between the characters/spacing.
 *
 */
void TextBox :: AlignText()
{
    const int FACTOR = 3;
    std::string dummyString(rawText);
    sf::Text dummy;

    dummy.setCharacterSize(charSize);
    dummy.setFont(*font);
    dummy.setString(dummyString);
    numOfTextRows = 0;
    textChain.clear();

    float bufferMargin = sf::Text("W",*font,charSize).getGlobalBounds().width;
    float rightLimit = getInternalWidth();
    float hyphenNewLineWidth = sf::Text("-\n",*font,charSize).getGlobalBounds().width;

    sf::Vector2f prevSize = sf::Vector2f(0,0);
    sf::Vector2f limit;
    int insertIndex = 0;
    int i = 0;

    while(i < dummyString.size() )
    {
        limit =  dummy.findCharacterPos(i);

        if ( limit.x >= ( rightLimit - FACTOR*bufferMargin )  )
        {
            insertIndex = (prevSize.x + hyphenNewLineWidth <= rightLimit) ? i-1: i-2;

            if ( insertIndex <= 0 ) break;

            textChain.push_back(std::string());
            std::string & textString = textChain[textChain.size() - 1];

            if ( dummyString[insertIndex] == SPACE  || dummyString[insertIndex-1] == SPACE)
            {
                textString.append(dummyString.begin(), dummyString.begin() + insertIndex);
                textString.append(NEWLINE);
            }
            else
            {
                textString.append(dummyString.begin(), dummyString.begin() + insertIndex);
                textString.append(HYPHEN_NEWLINE);
            }

            i = -1;

            dummyString.erase(dummyString.begin(), dummyString.begin() +insertIndex);

            numOfTextRows++;
            std::cout << textString;
        }
        i++;
        prevSize = limit;

    }

    if ( !dummyString.empty() )
    {
        textChain.push_back(dummyString);
        numOfTextRows++;
    }
    flag = true;
}

void TextBox :: SetUpDisplay()
{
    SetSize();
    SetPosition();
    SetUpText();
}

void TextBox :: SetUpWindowDisplay()
{
    SetUpDisplay();
    setUp = true;
}


//void TextBox :: SetUpDisplay()
void TextBox :: SetUpText()
{
    CalculaterowsPerPage();
    std::stringstream ss;
    std::cout << textChain.size() << std::endl;
    for(int i = startIndex; i<= stopIndex; i++)
    {
        ss << textChain[i];
    }

    text.setString(ss.str());

}

void TextBox :: scrollUp(int offset)
{

    if ( startIndex == 0 ) return;

    int decrement  = startIndex - offset;
    startIndex = decrement < 0 ?  0 : decrement;
    stopIndex = startIndex + rowsPerPage - 1;

    SetUpText();
    //SetUpDisplay();
}

void TextBox :: scrollDown(int offset)
{
    if ( stopIndex == numOfTextRows - 1) return;
    int increment  = startIndex + offset;
    startIndex = increment > (numOfTextRows - rowsPerPage ) ?  numOfTextRows - rowsPerPage - 1 : increment;
    stopIndex = startIndex + rowsPerPage - 1;

    SetUpText();
    //SetUpDisplay();
}

void TextBox :: setFontSize(int num)
{
    charSize = num;
    text.setCharacterSize(charSize);
    if ( charSize && font && rawText ) AlignText();
}

void TextBox :: setText(const char * _text)
{
    rawText = _text;
    std::cout << rawText << std::endl;
    if( charSize && font && rawText )
    {
        text.setFont(*font);
        AlignText();
    }
    text.setColor(COL_BLUE);
}

void TextBox :: SetSize()
{
    if( charSize && font && rawText )  AlignText();
}

void TextBox :: SetPosition()
{
    sf::Vector2f pos = getInternalPosition();
    text.setPosition(pos.x, pos.y);

}


void TextBox :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!flag) throw "TextBox :: font or charactersize or the text is not assigned to be displayed in the TextBox";
    this->EnclosingBox::draw(target,states);

    target.draw(text);

}


}//EON

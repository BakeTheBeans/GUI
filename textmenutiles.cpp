#include "textmenutiles.h"
#include <algorithm>


namespace  GUI {

const sf::Color MenuTiles :: DefaultTextColor = COL_GRAY_15;
const float MenuTiles :: DefaultTileWidth = 200;
const float MenuTiles :: DefaultTileHeight = 30;
const int MenuTiles :: DefaultFontSize = 15;


MenuTiles :: MenuTiles() : EnclosingBox(DefaultTileWidth, DefaultTileHeight, 10, 0), tileText(), font(0), rawText(""), fontSize(10), alignment(GUI::internal::Center)
{
}


MenuTiles :: MenuTiles(sf::Font * _font, float _tileWidth, float _tileHeight, float _borderSize, std::string _text, int _fontSize, float _textMarginSize, sf::Color _tileColor, sf::Color _textColor,  internal::TextAlignment _alignment ) : EnclosingBox(_tileWidth, _tileHeight, _borderSize, _textMarginSize), tileText(), font(_font), rawText(_text), fontSize(_fontSize), alignment(_alignment)
{
    //if ( !font ) throw "MenuTiles : No font provided";

    this->EnclosingBox::setFillColor(_tileColor);
    setMarginSize(_textMarginSize);

    tileText.setFont(*font);
    tileText.setString(rawText);
    tileText.setCharacterSize(fontSize);

    this->EnclosingBox::setPosition(100,100);
    tileText.setPosition( this->EnclosingBox::getInternalPosition() );

    SetAlignment();
}

void MenuTiles :: SetAlignment()
{
    float xspace = ( getInternalWidth() -  tileText.getGlobalBounds().width)/2;
    float yspace = ( getInternalHeight() - tileText.getGlobalBounds().height )/2;

    //The text height doesn't align correctly.
    //I have checked my calculations, probably a bug in sf::Text
    float posY = getInternalPosition().y + yspace - bufferHeightMargin();
    float posX = 0;

    if ( alignment == internal::Center ) posX = getInternalPosition().x + xspace;
    else if ( alignment == internal::Left ) posX = getInternalPosition().x + bufferWidthMargin();
    else posX = getInternalPosition().x + 2*xspace - bufferWidthMargin();

    tileText.setPosition(posX,posY);

}

void MenuTiles :: setFont(sf::Font * ff)
{
    font = ff;
}

void MenuTiles :: SetUpDisplay()
{
    SetSize();
    //SetPosition();
    setUp = true;
}

void MenuTiles :: setTextAlignment(internal::TextAlignment _align)
{
    alignment = _align;
    SetAlignment();
}

float MenuTiles :: bufferWidthMargin()
{
    return getMarginSize() * sf::Text("W",*font,fontSize).getGlobalBounds().width;
}

float MenuTiles :: bufferHeightMargin()
{
    return getMarginSize() * sf::Text("W",*font,fontSize).getGlobalBounds().height;
}

void MenuTiles :: ResizeText()
{    
    std::string dummyString;

    sf::Text dummyText;
    dummyText.setFont(*font);
    dummyText.setCharacterSize(fontSize);

    if ( dummyText.getGlobalBounds().height > getInternalHeight() - 2*bufferHeightMargin() )
    {
        tileText.setString("");
        return;
    }

    int i = 0;
    while( i < rawText.size() )
    {
        dummyString.push_back(rawText[i]);
        dummyText.setString(dummyString);
        if ( dummyText.getLocalBounds().width > ( getInternalWidth() - bufferWidthMargin() ) )
        {           
            dummyString.erase(dummyString.end()-1, dummyString.end() );            
            break;
        }
        i++;
    }

    tileText.setString(dummyString);
    SetAlignment();
}

void MenuTiles :: setText(std::string _text)
{
    rawText  = _text;
    ResizeText();
}

void MenuTiles :: setFontSize(int _fontSize)
{
    fontSize = _fontSize;
    tileText.setCharacterSize(fontSize);
    ResizeText();
}

void MenuTiles :: SetSize()
{
    ResizeText();
}

void MenuTiles :: SetPosition()
{
    SetAlignment();
}

void MenuTiles :: setTextColor(sf::Color _color)
{
    tileText.setColor(_color);
}



void MenuTiles :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    this->EnclosingBox::draw(target,states);
    target.draw(tileText);
}

}//EON



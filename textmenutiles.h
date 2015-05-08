#ifndef TEXTMENUTILES_H
#define TEXTMENUTILES_H
#include "interfaces.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include "tools.h"
#include "Utility.h"
#include "Traits.h"

namespace  GUI {


class MenuTiles :  public EnclosingBox
{

    static const sf::Color DefaultTextColor;
    static const float DefaultTileWidth;
    static const float DefaultTileHeight;
    static const int DefaultFontSize;

    sf::Text tileText;
    const sf::Font * font;
    std::string rawText;
    int fontSize;
    internal::TextAlignment alignment;

protected:
    void ResizeText();
    void SetAlignment();
    virtual void SetSize();
    virtual void SetPosition();
    float bufferWidthMargin();
    float bufferHeightMargin();
    void SetUpDisplay();


public:
    MenuTiles();
    MenuTiles(sf::Font * _font, float _tilewidth = DefaultTileWidth, float _tileHeight = DefaultTileHeight, float _borderSize = EnclosingBox::DefaultBorderSize, std::string _text = "Text", int _fontSize = DefaultFontSize, float _textMarginSize = EnclosingBox::DefaultMarginSize, sf::Color _tileColor = EnclosingBox::DefaultFillColor , sf::Color _textColor = DefaultTextColor, internal::TextAlignment _alignment = internal::Left);

    void setFont(sf::Font * ff);
    virtual ~MenuTiles() {}
    void setText(std::string);
    void setFontSize(int _fontSize);
    void setTextAlignment(internal::TextAlignment _align);
    void setTextColor(sf::Color _color);

    const sf::Color & getTextColor() { return tileText.getColor(); }
    float getFontSize() const { return fontSize; }
    const std::string getText()  { return tileText.getString(); }


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

namespace internal {


template<>
struct HasText<MenuTiles>
{
    static const bool value = true;
};

}//EON


}//EON
#endif // TEXTMENUTILES_H

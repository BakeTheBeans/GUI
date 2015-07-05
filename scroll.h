#ifndef SCROLL_H
#define SCROLL_H
#include "define.h"
#include "interfaces.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <vector>


#include "DebugTool.h"

namespace GUI {


class ScrollBar : public EnclosingBox
{
public:
    static const sf::Color DefaultScrollBarFrameColor;
    static const sf::Color DefaultScrollFillColor;
    static const sf::Color DefaultScrollStoneColor;
    static const float DefaultScrollBarWidth;

public:

    enum Direction
    {
        up,
        down,
        right,
        left
    };

private:
    internal::AlignmentType alignment;
    unsigned int stoneWidth,stoneHeight;
    sf::RectangleShape stone;
    int displaySize;
    int pageSize;
    int currentStonePos;    

    virtual void SetUpDisplay();

protected:
    virtual void SetPosition();
    virtual void SetSize();
    void updateStonePosition();

protected:
    void setStoneSize();
public:
    //ScrollBar() : track(-1) {}
    ScrollBar(internal::AlignmentType _alignment);
    ScrollBar(internal::AlignmentType _align,float barWidth,float barHeight, float barThickness);
    void setHolderSpaceColor(sf::Color hColor)
    { this->EnclosingBox::setFillColor(hColor); }

    void setHolderFrameColor(sf::Color fcolor)
    { this->EnclosingBox::setBorderColor(fcolor); }

    void setAlignment(internal::AlignmentType _alignment){}
    void setStoneColor(sf::Color sColor) { stone.setFillColor(sColor); }

    void setDisplaySize(int _size);
    void setPageSize(int _size);
    void scroll(float dist, ScrollBar::Direction _dir);
    void reset();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};


}//EON
#endif // SCROLL_H

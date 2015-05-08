#include "scroll.h"

namespace GUI {

const sf::Color ScrollBar :: DefaultScrollBarFrameColor = COL_GRAY_3;
const sf::Color ScrollBar :: DefaultScrollFillColor = COL_BLACK;
const sf::Color ScrollBar :: DefaultScrollStoneColor = COL_GRAY_9;
const float ScrollBar :: DefaultScrollBarWidth  = 8;


ScrollBar :: ScrollBar(internal::AlignmentType _alignment) : EnclosingBox(), alignment(_alignment),stoneWidth(),stoneHeight(), stone(), displaySize(), pageSize(), currentStonePos(1)
{
    this->EnclosingBox::setBorderColor(DefaultScrollBarFrameColor);
    this->EnclosingBox::setFillColor(DefaultScrollFillColor);
    stone.setFillColor(DefaultScrollStoneColor);
}


ScrollBar :: ScrollBar(internal::AlignmentType _align,float barWidth, float barHeight, float barThickness) : EnclosingBox(), alignment(_align), stoneWidth(), stoneHeight(), stone(), displaySize(0), pageSize(0), currentStonePos(1)
{
    if ( !barThickness) throw "ScrollBar thickness must be non-zero.";
    if ( (alignment == internal::Horizontal && (barWidth < barHeight) )|| ( alignment == internal::Vertical && (barHeight < barWidth) ) )
        throw "Scroll Bar dimensions not compatible with the alignment type.";


    this->EnclosingBox::setSize(barWidth, barHeight);
    this->EnclosingBox::setBorderSize(barThickness);
    this->EnclosingBox::setBorderColor(DefaultScrollBarFrameColor);
    this->EnclosingBox::setFillColor(DefaultScrollFillColor);

    if (alignment == internal::Vertical )
    {
        stoneWidth = barWidth;
        stoneHeight = barHeight;
    }
    else
    {
        stoneHeight = barHeight;
        stoneWidth = barWidth;
    }

}

void ScrollBar ::  SetUpDisplay()
{
    setDisplaySize(displaySize);
    setStoneSize();
}

void ScrollBar :: SetSize()
{


    if (alignment == internal::Vertical )
    {
        if( getInternalHeight() < getInternalWidth() ) throw "Scroll Bar dimensions not compatible with the alignment type.";
        stoneWidth = getInternalWidth();

    }
    else
    {
        if( getInternalHeight() > getInternalWidth() ) throw "Scroll Bar dimensions not compatible with the alignment type.";
        stoneHeight = getInternalHeight();
    }

    setDisplaySize(displaySize);
    setPageSize(pageSize);
    stone.setSize(sf::Vector2f(stoneWidth, stoneHeight) );
}

void ScrollBar :: setStoneSize()
{
    if (alignment == internal::Vertical )
    {

        float _size = (displaySize * this->EnclosingBox::getInternalHeight() )/pageSize;
        stoneHeight = _size > getInternalHeight() ? getInternalHeight() : _size;

    }

    else
    {
        float _size = (displaySize * getInternalWidth() )/pageSize;
        stoneWidth = _size > getInternalWidth() ? getInternalWidth() : _size;

    }    
    stone.setSize(sf::Vector2f(stoneWidth,stoneHeight));
}

void ScrollBar :: setDisplaySize(int _size)
{
    displaySize = _size;
    setStoneSize();
}

void ScrollBar :: setPageSize(int _size)
{
    pageSize = _size;
    setStoneSize();
}

void ScrollBar :: scroll(float dist, ScrollBar::Direction _dir)
{

    switch (_dir)
    {
    case ScrollBar::up:
        if ( currentStonePos == 1) return;
        currentStonePos = currentStonePos - dist < 1 ? 1 : currentStonePos - dist;
        break;

    case ScrollBar::down:
        if (currentStonePos == pageSize - displaySize ) return;
        currentStonePos =  currentStonePos + dist > pageSize ? pageSize : currentStonePos + dist;
        break;

    case ScrollBar::left:
        if ( currentStonePos == 1) return;
        currentStonePos = currentStonePos - dist < 1 ? 1 : currentStonePos - dist;
        break;


    case ScrollBar::right:
        if (currentStonePos == pageSize ) return;
        currentStonePos =  currentStonePos + dist > pageSize ? pageSize : currentStonePos + dist;
        break;

    default:
        throw "Unrecognized type";

    }

    updateStonePosition();
}

void ScrollBar :: updateStonePosition()
{

    if ( alignment == internal::Vertical)
    {
        float holderTop = this->EnclosingBox::getInternalPosition().y;
        float holderBottom = holderTop + this->EnclosingBox::getInternalHeight() - stoneHeight;
        float stoneTopPos = 1;
        float stoneBottomPos = pageSize - displaySize;

        float pos = holderTop +  (holderBottom - holderTop) * (currentStonePos - stoneTopPos)/(stoneBottomPos - stoneTopPos);
        stone.setPosition( stone.getPosition().x,  pos );

    }

    else if ( alignment == internal::Horizontal )
    {
        float holderLeft = getInternalPosition().x;
        float holderRight = holderLeft + getInternalWidth() - stoneWidth;
        float stoneLeftPos = 1;
        float stoneRightPos = pageSize - displaySize;

        float pos = holderLeft + (holderRight - holderLeft)*(currentStonePos - stoneLeftPos)/(stoneRightPos - stoneLeftPos);
        stone.setPosition( pos, stone.getPosition().y);
    }


}


void ScrollBar :: reset()
{
    currentStonePos = 1;
    updateStonePosition();

}

void ScrollBar :: SetPosition()
{
    stone.setPosition( getInternalPosition() );
}


void ScrollBar :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    this->EnclosingBox::draw(target,states);
    target.draw(stone);
}

}//EON

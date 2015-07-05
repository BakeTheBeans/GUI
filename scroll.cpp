#include "scroll.h"


namespace GUI {

const sf::Color ScrollBar :: DefaultScrollBarFrameColor = COL_GRAY_3;
const sf::Color ScrollBar :: DefaultScrollFillColor = COL_BLACK;
const sf::Color ScrollBar :: DefaultScrollStoneColor = COL_GRAY_9;
const float ScrollBar :: DefaultScrollBarWidth  = 8;


ScrollBar :: ScrollBar(internal::AlignmentType _alignment) : EnclosingBox(), alignment(_alignment),stoneWidth(),stoneHeight(), stone(), displaySize(), pageSize(), currentStonePos(-1)
{
    this->EnclosingBox::setBorderColor(DefaultScrollBarFrameColor);
    this->EnclosingBox::setFillColor(DefaultScrollFillColor);
    stone.setFillColor(DefaultScrollStoneColor);

}



ScrollBar :: ScrollBar(internal::AlignmentType _align,float barWidth, float barHeight, float barThickness) : EnclosingBox(), alignment(_align), stoneWidth(), stoneHeight(), stone(), displaySize(0), pageSize(0), currentStonePos(-1)
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
    if ( currentStonePos == -1 ) currentStonePos = displaySize;

#if(VERBOSE_DEBUG)
    if ( alignment == internal::Horizontal )    std::cout << "Horizonatal Scroll Bar " << std::endl;
    else std::cout << "Verical Scroll Bar " << std::endl;
    std::cout << "WINDOW SCROLL   Page Size " << pageSize << "    Display Size  : " << displaySize << "     Scroll POsition  " << currentStonePos <<  "   Stone  Size "  <<  ( (alignment == internal::Horizontal ) ? stoneWidth : stoneHeight ) <<  "Display Size ... " << displaySize <<  std::endl;
#endif

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
#if(VERBOSE_DEBUG)
    if ( alignment == internal::Vertical ) { std::cout << "Setting Vertical Page Size.................." << std::endl; }
    else if ( alignment == internal::Horizontal) {std::cout << "Setting Horizontal Page Size.................." << std::endl; }
#endif
    updateStonePosition();
}

void ScrollBar :: scroll(float dist, ScrollBar::Direction _dir)
{

    switch (_dir)
    {
    case ScrollBar::up:
        if ( currentStonePos <= displaySize) return;
        currentStonePos = (currentStonePos - dist) < displaySize ? displaySize : currentStonePos - dist;
        break;

    case ScrollBar::down:
        if (currentStonePos >= pageSize ) return;
        currentStonePos =  ( currentStonePos + dist ) > pageSize ? pageSize : currentStonePos + dist;
        break;

    case ScrollBar::left:
        if ( currentStonePos <= displaySize) return;
        currentStonePos = (currentStonePos - dist) < displaySize ? displaySize : currentStonePos - dist;
        break;

    case ScrollBar::right:
        if (currentStonePos >= pageSize ) return;
        currentStonePos =  ( currentStonePos + dist ) > pageSize ? pageSize : currentStonePos + dist;
        break;

    default:
        throw "Unrecognized type";

    }


    updateStonePosition();
#if(VERBOSE_DEBUG)
    std::cout << "WINDOW SCROLL   Page Size " << pageSize << "    Display Size  : " << displaySize << "     Scroll POsition  " << currentStonePos <<  "   Stone  Size "  <<  ( (alignment == internal::Horizontal ) ? stoneWidth : stoneHeight ) <<  std::endl;
#endif

}



void ScrollBar :: updateStonePosition()
{

    if ( pageSize == displaySize && currentStonePos > displaySize )
    {  
        currentStonePos = displaySize;        
    }


    if ( alignment == internal::Vertical)
    {
#if(VERBOSE_DEBUG)
        std::cout << " Updating Stone Position for Vertical Scroll Bar " << std::endl;
#endif
        float holderTop = this->EnclosingBox::getInternalPosition().y;
        float holderBottom = holderTop + this->EnclosingBox::getInternalHeight() - stoneHeight;
        float stoneTopPos = 0;
        float stoneBottomPos = pageSize - displaySize;


        float mappedCurrentPos = currentStonePos - displaySize;


        float pos = pageSize != displaySize ? ( holderTop +  (holderBottom - holderTop) * ( mappedCurrentPos - stoneTopPos)/(stoneBottomPos - stoneTopPos) ) : holderTop;

#if(VERBOSE_DEBUG)
        std::cerr << " Mapped Position : " << ( pos - holderTop) << "     currentStonePos : " << currentStonePos << std::endl;
#endif

        /*
         * if the page size changes dynamic increasing the stonSize
         * then the below condition prevents the stone from sticking
         * out of the holder
         */
        if( ( pos - holderTop +  stoneHeight) > getInternalHeight() )
        {
            pos = pos - stoneHeight + (2*displaySize - currentStonePos);
            currentStonePos = mappedCurrentPos + displaySize;
        }

        stone.setPosition( stone.getPosition().x,  pos );        

    }

    else if ( alignment == internal::Horizontal )
    {
#if(VERBOSE_DEBUG)
        std::cout << " Updating Stone Position for Horizontal Scroll Bar " << std::endl;
#endif
        float holderLeft = getInternalPosition().x;
        float holderRight = holderLeft + getInternalWidth() - stoneWidth;
        float stoneLeftPos = 0;
        float stoneRightPos = pageSize - displaySize;
        float mappedCurrentPos = currentStonePos - displaySize;

        float pos =  pageSize != displaySize ? ( holderLeft +  (holderRight - holderLeft) * ( mappedCurrentPos - stoneLeftPos)/(stoneRightPos - stoneLeftPos) ) : holderLeft;

        /*
         * if the page size changes dynamic increasing the stonSize
         * then the below condition prevents the stone from sticking
         * out of the holder
         */
        if ( ( pos - holderLeft + stoneWidth ) > getInternalWidth() )
        {
            pos = pos - stoneWidth + (2*displaySize - currentStonePos );
            currentStonePos = mappedCurrentPos + displaySize;
        }

        stone.setPosition( pos, stone.getPosition().y);
    }


}


void ScrollBar :: reset()
{
    currentStonePos = displaySize;
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

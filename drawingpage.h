#ifndef DRAWINGPAGE_H
#define DRAWINGPAGE_H
#include <vector>
#include <fstream>
#include <SFML/Graphics/Drawable.hpp>
#include "shapefactory.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "interfaces.h"
#include <utility>
#include "window.h"

#define PAUSE_DRAWING sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
#define RESUME_DRAWING sf::Keyboard::isKeyPressed(sf::Keyboard::R)
#define FINISH_DRAWING sf::Mouse::isButtonPressed(sf::Mouse::Right)

namespace sf {
class RenderTarget;
class RenderStates;
}
//public EnclosingBox, public IScrollable

namespace Draw {

#if(NEW_DEBUG)
class DrawingPage : public GUI::EnclosingBox, public GUI::IScrollable
#else
class DrawingPage : public sf::Drawable
#endif
{    

#if(NEW_DEBUG)
friend class GUI::ScrollableWindow<DrawingPage>;
#endif

    typedef int _size;

    enum drawingStatus
    {
        started,
        progress,
        paused,
        complete
    };

    typedef IDrawableShapes * ShapePtr;
    std::vector<ShapePtr> shapeColl;
    ShapePtr currentShape, selectedShape;
    bool pageLoop, pause;
    drawingStatus status;

    std::pair<int,int> pageScrollPos, pageSize, displaySize;

    std::pair<sf::Vector2f,sf::Vector2f> bounds;  //Bounding box that encompasses all the shapes

public:

    DrawingPage() : shapeColl(), currentShape(nullptr), selectedShape(nullptr), pageLoop(false), pause(false), status(started), pageScrollPos(), pageSize(), displaySize()
    {
    }

    //Inside implementation Loop
    template<typename T>
    bool DrawShape(sf::Window & window)
    {

        bool returnValue = false;
        pageLoop = false;
        switch(status)
        {

        case started:
            currentShape = ShapeFactory::getShapeFactory().template CreateShapeInstance<T>();
            status = progress;
            break;

        case progress:
            //if ( PAUSE_DRAWING )
            if ( !ContainsMouseInside(&window) )
            {
                status = paused;
                currentShape->StopDraw();
            }
            else
            {
                if ( currentShape->StartDraw(window) )
                {
                    shapeColl.push_back(currentShape);
                    currentShape = nullptr;
                    status = complete;
                }
            }
            break;

        case paused:
            //if ( RESUME_DRAWING ) status = progress;
            if ( ContainsMouseInside(&window) ) status = progress;
            break;

        case complete:
            if(FINISH_DRAWING)
            {
                returnValue =  true;
                status = started;
                pageLoop = true;
            }

            break;
        }

        return returnValue;
    }

     void EnablePageLoop();
     bool isShapeSelected() { return selectedShape != nullptr; }
     ShapePtr getSelectedShape() { return selectedShape; }
     void Save(std::string filename);
     void Load(std::string filename);

#if(NEW_DEBUG)
protected:
     virtual void changeVerticalPageSpace(int step);
     virtual void changeHorizontalPageSpace(int step);

public:
     int getVerticalPageSize() {return pageSize.second;}
     int getVerticalDisplaySize() {return displaySize.second; }
     int getHorizontalPageSize() { return pageSize.first; }
     int getHorizontalDisplaySize(){ return displaySize.first; }

     void SetSize();
     void SetPosition() {}
     void SetUpWindowDisplay();
     void SetUpDisplay();

     void CreateVerticalPageSpace(int step);
     void CreateHorizontalPageSpace(int step);
     //void ResetPosition();
     void zoom(float scale);

     virtual void scrollUp(int offset);

     virtual void scrollDown(int offset);

     virtual void scrollRight(int offset);

     virtual void scrollLeft(int offset);

#endif

     void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};



}//EON
#endif // DRAWINGPAGE_H

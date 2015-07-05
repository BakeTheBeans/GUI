#ifndef DRAWAPP_H
#define DRAWAPP_H
#include "ComplexObject.h"
#include "drawingpage.h"
#include "drawableshapes.h"
#include "menu.h"
#include "button.h"
#include <memory>
#include "factory.h"
#include <SFML/Window.hpp>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "unittest.h"
#include "buttonevent.h"

using namespace  GUI;

namespace Draw  {

class DrawApp;

class ShapeManager : public ICallBackEventHandler
{
friend class DrawApp;
private:
    enum Shape
    {
        none,
        w_line,
        w_triangle,
        w_rectangle,
        w_rhombus,
        w_quad,
        w_pentagon,
        w_hexagon,
        w_octagon,
        w_circle,
        b_triangle,
        b_rectangle,
        b_rhombus,
        b_quad,
        b_pentagon,
        b_hexagon,
        b_octagon,
        b_circle,
    };


    Shape currentShape;

    ShapeManager() : currentShape(none) {}

    Shape getCurrentShape() { return currentShape; }

    /*
    void DrawLine() {currentShape = line; }

    void DrawRectangle() {currentShape = rectangle; }

    void DrawCircle() {currentShape = circle; }
    */

    template<int ShapeType> void DrawShape() { currentShape = static_cast<Shape>(ShapeType); }



};




class DrawApp : public UnitTest, public GUI::internal::ComplexObject
{

typedef ShapeManager SM;
typedef std::shared_ptr<MenuBar> MenuBarSPtr;
typedef ScrollableWindow<DrawingPage> DrawingWindow;
typedef std::shared_ptr<GUI::IButton> ButtonSPtr;
typedef void (DrawApp::*FuncPtr )();

private:

  DrawApp(const DrawApp & obj);
  DrawApp & operator=(const DrawApp & obj);

  std::unordered_map<std::string, MenuBarSPtr> menuBarMap;
  DrawingWindow drawSpace;
  std::unordered_map<std::string,ButtonSPtr> buttonMap;
  std::map<SM::Shape,FuncPtr> shapeFuncMap;
  bool active;
  ShapeManager sm;
  DrawingPage * page;

  void activateButton();
  template<typename T>
      void DrawShape()
      {
        DrawingPage * page = static_cast<DrawingPage*>(drawSpace.getCurrentPage());
        active = page->template DrawShape<T>(*window);
      }

public:
  //void TestPressButton() { b->Press(); }
  //void TestReleaseButton() { b->Release(); }


public:
    DrawApp(sf::Event & _event);
    void Initialize();
    void SetSize() {}
    void ConfigureSubElements();
    std::string getXmlTagName() { return "DrawApplication"; }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void ApplicationPolling();


    void SetUpEnvironment();
    void InsidePollingImpl();
    void DisplayObjects();



};


}
#endif // DRAWAPP_H

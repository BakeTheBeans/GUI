#ifndef WINDOW_H
#define WINDOW_H
#include "interfaces.h"
#include "scroll.h"
#include "textbox.h"
//#include "menupage.h"
//#include "directorymenupage.h"
#include <memory>
#include <list>

namespace GUI {

template<typename T>
class ScrollableWindow : public EnclosingBox, public IScrollWindowCallBack
{
    friend class IScrollable;
    static const float DefaultScrollBarThickness;
    static const float DefaultScrollFrameWidth;


private:
    //ScrollableWindow(const ScrollableWindow<T> & obj ) {}
    //ScrollableWindow<T> & operator=(const ScrollableWindow<T> & obj) {throw "Do not implement";}

protected:  
    virtual void SetSize();
    void SetSizeIfFixed();
    virtual void SetPosition();
    void SetUpDisplay();
    void SetUpNonAdaptableDisplay();

    //void SetUpAdaptableDisplay();

    void ConfigureDisplayObject();
    void ConfigureVerticalScrollBar();
    void ConfigureHorizontalScrollBar();
    void ResetVerticalScrollBar();
    void ResetHorizontalScrollBar();
    virtual void ResizeWindow();

private:

    ScrollBar vScroll {internal::Vertical};
    ScrollBar  hScroll {internal::Horizontal};
    float ScrollThickness;
    bool hHide,vHide;    
    T * DisplayObj;
    std::list<T*> buffer;

    T * dummy;

public:
  ScrollableWindow();
  ScrollableWindow(T * displayObj);
  virtual ~ScrollableWindow()
  {
    if ( dummy ) delete dummy;
    for(T * p : buffer) delete p;
  }

  void setScrollBarColor(sf::Color _color);
  void setScrollStoneColor(sf::Color _color);
  void setVerticalDisplaySize(unsigned int _dispSize);
  void setHorizontalDisplaySize(unsigned int _dispSize);

  void CreateVerticalPageSpace(int step);
  void CreateHorizontalPageSpace(int step);
  void Zoom(float scale);

  void AttachDisplay(T * obj);
  T *  DetachDisplay();
  T * getCurrentPage() { return DisplayObj; }

  void ScrollUp(int offset);
  void ScrollDown(int offset);
  void ScrollRight(int offset);
  void ScrollLeft(int offset);  
  void Launch();


  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


} //EON
#endif // WINDOW_H

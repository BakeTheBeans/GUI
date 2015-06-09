#ifndef WINDOW_H
#define WINDOW_H
#include "interfaces.h"
#include "scroll.h"
#include "textbox.h"
//#include "menupage.h"
//#include "directorymenupage.h"


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
    T & DisplayObj;

public:
  ScrollableWindow(T & scrollableObj);
  virtual ~ScrollableWindow()  {}  

  void setScrollBarColor(sf::Color _color);
  void setScrollStoneColor(sf::Color _color);
  void setVerticalDisplaySize(unsigned int _dispSize);
  void setHorizontalDisplaySize(unsigned int _dispSize);
#if(NEW_DEBUG)
  void CreateVerticalPageSpace(int step);
  void CreateHorizontalPageSpace(int step);
  void Zoom(float scale);

#endif
  void ScrollUp(int offset);
  void ScrollDown(int offset);
  void ScrollRight(int offset);
  void ScrollLeft(int offset);  
  void Launch();


  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


} //EON
#endif // WINDOW_H

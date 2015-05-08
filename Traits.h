#ifndef TRAITS_H
#define TRAITS_H
//#include "button.h"

namespace GUI
{

template<typename T>
struct ScrollableEntityTrait
{
    static const bool CanAdaptToWindow = true;
};


template<typename T> class Button;

namespace internal {


template<typename T>
struct IsDerivedFromEnclosingBox
{
    static  const bool value = true;
};


template<typename T>
struct HasSetSize
{
    static const bool value = true;
};

template<typename T>
struct HasText
{
    static const bool value = false;
};


template<typename T>
struct HasSetFillColor
{
    static const bool value = true;
};


template<typename T>
struct HasSetSize< GUI::Button<T>>
{
    static const bool value = false;
};

template<typename T>
struct HasText<GUI::Button<T> >
{
    static const bool value = false;
};


template<typename T>
struct HasSetFillColor<GUI::Button<T> >
{
    static const bool value = false;
};


template<typename T>
struct IsDerivedFromEnclosingBox<GUI::Button<T>>
{
    static  const bool value = false;
};


}//EON


}//EON



#endif // TRAITS_H

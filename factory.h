#ifndef FACTORY_H
#define FACTORY_H
#include <map>
#include "button.h"
#include "Utility.h"





namespace GUI
{
/*
template<typename T, typename Trait=GUITrait<T> >
class Factory
{


private:
    typedef T * GuiPtr;
    typedef GuiPtr (Factory<T>::*FuncPtr)();
    Factory() {}
    static std::map<Trait::GUIType,FuncPtr> FactoryMap;


public:
static T * getGuiObject(GUITrait<T> & traitType);
static RegisterGuiObject(GUITrait<T> & traitType);
static void CreateObject();
};
*/

typedef IButton* ButtonPtr;

class ButtonFactory
{

public:
    typedef ButtonPtr (*FuncPtr)();


private:
    static std::map<BUTTON::ButtonType, FuncPtr> factoryMap;

    template<typename T>static ButtonPtr CreateButton()
    {
        return new Button<T>();
    }

public:
    template<typename T> static void RegisterButton()
    {
        std::cout << " Rgistering type : "  << T::type << std::endl;
        BUTTON::ButtonType _type = T::type;
        auto it = factoryMap.find(_type);
        if ( it == factoryMap.end()  )
        {
            factoryMap[_type] = &CreateButton<T>;
        }

    }

    template<typename T> static ButtonPtr getButton(double scaleX = 0.5, double scaleY = 0.5)
    {
     //   std::cout << " Map size = " << factoryMap.size() << std::endl;
       BUTTON::ButtonType _type = T::type;
       auto it = factoryMap.find(_type);
       if ( it == factoryMap.end() ) throw "Button type not Registered";
       ButtonPtr p =  (*(it->second))();
       p->scale(scaleX, scaleY);
       return p;
    }


};




namespace internal
{

    static std::map<BUTTON::ButtonType,ButtonFactory::FuncPtr> CreateButtonFactoryMap()
    {
        std::map<BUTTON::ButtonType,ButtonFactory::FuncPtr> factoryMap;
        return factoryMap;
    }

}




//This factory needs work.
class GuiFactory
{

   private:
    GuiFactory() {}

public:
    static GuiFactory & GetFactoryInstance();

    template<typename T>
    T * CreateObject()
    {
        return new T();

    }


};


















}
#endif // FACTORY_H

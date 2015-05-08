#include "factory.h"



namespace  GUI {


std::map<BUTTON::ButtonType,ButtonFactory::FuncPtr> ButtonFactory::factoryMap = internal::CreateButtonFactoryMap();


GuiFactory & GuiFactory :: GetFactoryInstance()
{
    static GuiFactory object;
    return object;
}


EON

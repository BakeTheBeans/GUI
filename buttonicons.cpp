#include "buttonicons.h"
#include "define.h"
namespace GUI {

const char *ButtonIcons::ImageFiles[] =
{
        "button_icons_1.png",
        "button_icons_2.jpg"
};

ButtonIcons :: ButtonIcons(int imageIndex) : _icon(0)
{

#if(TEXTURE_2)
    TextureManager::RegisterGuiComponent(buttonIcons, ImageFiles[imageIndex]);
    _icon = TextureManager::getTexture(buttonIcons);
#else
    _icon = ResourceManager::getTexture("ButtonIcons");
    this->setTexture(*_icon);
#endif

    this->setTexture(*_icon);

}


EON

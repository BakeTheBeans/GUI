#include "buttontypes.h"
#include "Utility.h"

namespace GUI {

#if(BUTTON_4)

ButtonTexture :: ButtonTexture() :  ImageFileNameMap() {}


std::string ButtonTexture :: getImageName(BUTTON::ImageId id)
{
    auto it = ImageFileNameMap.find(id);
    if ( it != ImageFileNameMap.end() )
    {
        return it->second;
    }

    else throw "No Button Image File name exists for the requested enumeration type.";

}

sf::Texture * ButtonTexture :: getButtonTexture()
{
     return ResourceManager::getResource<GUI::Texture>(getImageName(BUTTON::BUTTON_IMAGE_NAME).c_str() );

}

sf::Texture * ButtonTexture :: getPressedButtonTexture()
{
     return ResourceManager::getResource<GUI::Texture>(getImageName(BUTTON::PRESSED_BUTTON_IMAGE_NAME).c_str() );

}

sf::Texture * ButtonTexture :: getHoverButtonTexture()
{
     return ResourceManager::getResource<GUI::Texture>(getImageName(BUTTON::HOVER_BUTTON_IMAGE_NAME).c_str() );
}


PlainTexture :: PlainTexture()
{
    //type = BUTTON::Plain;
    ImageFileNameMap[BUTTON::BUTTON_IMAGE_NAME] = "ButtonImage_2";
    ImageFileNameMap[BUTTON::PRESSED_BUTTON_IMAGE_NAME] = "ButtonImage_3";
    ImageFileNameMap[BUTTON::HOVER_BUTTON_IMAGE_NAME] = "ButtonImage_4";
}

FileTexture :: FileTexture()
{
    //type = BUTTON::File;
    ImageFileNameMap[BUTTON::BUTTON_IMAGE_NAME] = "ButtonImage_5";
    ImageFileNameMap[BUTTON::PRESSED_BUTTON_IMAGE_NAME] = "ButtonImage_6";
    ImageFileNameMap[BUTTON::HOVER_BUTTON_IMAGE_NAME] = "ButtonImage_7";
}


CancelTexture :: CancelTexture()
{
    //type = BUTTON::Cancel;
    ImageFileNameMap[BUTTON::BUTTON_IMAGE_NAME] = "ButtonImage_8";
    ImageFileNameMap[BUTTON::PRESSED_BUTTON_IMAGE_NAME] = "ButtonImage_9";
    ImageFileNameMap[BUTTON::HOVER_BUTTON_IMAGE_NAME] = "ButtonImage_10";
}

EditTexture :: EditTexture()
{
    //type = BUTTON::Edit;
    ImageFileNameMap[BUTTON::BUTTON_IMAGE_NAME] = "ButtonImage_11";
    ImageFileNameMap[BUTTON::PRESSED_BUTTON_IMAGE_NAME] = "ButtonImage_12";
    ImageFileNameMap[BUTTON::HOVER_BUTTON_IMAGE_NAME] = "ButtonImage_13";
}



MenuTexture :: MenuTexture()
{
    //type = BUTTON::Menu;
    ImageFileNameMap[BUTTON::BUTTON_IMAGE_NAME] = "ButtonImage_14";
    ImageFileNameMap[BUTTON::PRESSED_BUTTON_IMAGE_NAME] = "ButtonImage_15";
    ImageFileNameMap[BUTTON::HOVER_BUTTON_IMAGE_NAME] = "ButtonImage_16";
}

/*
NavigateTexture :: NavigateTexture()
{
    //type = BUTTON::Navigate;
    ImageFileNameMap[BUTTON::BUTTON_IMAGE_NAME] = "ButtonImage_17";
    ImageFileNameMap[BUTTON::PRESSED_BUTTON_IMAGE_NAME] = "ButtonImage_18";
    ImageFileNameMap[BUTTON::HOVER_BUTTON_IMAGE_NAME] = "ButtonImage_19";
}

NextTexture :: NextTexture()
{
    //type = BUTTON::Next;
    ImageFileNameMap[BUTTON::BUTTON_IMAGE_NAME] = "ButtonImage_20";
    ImageFileNameMap[BUTTON::PRESSED_BUTTON_IMAGE_NAME] = "ButtonImage_21";
    ImageFileNameMap[BUTTON::HOVER_BUTTON_IMAGE_NAME] = "ButtonImage_22";
}

SaveTexture :: SaveTexture()
{
    //type = BUTTON::Save;
    ImageFileNameMap[BUTTON::BUTTON_IMAGE_NAME] = "ButtonImage_23";
    ImageFileNameMap[BUTTON::PRESSED_BUTTON_IMAGE_NAME] = "ButtonImage_24";
    ImageFileNameMap[BUTTON::HOVER_BUTTON_IMAGE_NAME] = "ButtonImage_25";
}

SettingsTexture :: SettingsTexture()
{
    //type = BUTTON::Settings;
    ImageFileNameMap[BUTTON::BUTTON_IMAGE_NAME] = "ButtonImage_26";
    ImageFileNameMap[BUTTON::PRESSED_BUTTON_IMAGE_NAME] = "ButtonImage_27";
    ImageFileNameMap[BUTTON::HOVER_BUTTON_IMAGE_NAME] = "ButtonImage_28";
}

StopTexture :: StopTexture()
{
    //type = BUTTON::Stop;
    ImageFileNameMap[BUTTON::BUTTON_IMAGE_NAME] = "ButtonImage_29";
    ImageFileNameMap[BUTTON::PRESSED_BUTTON_IMAGE_NAME] = "ButtonImage_30";
    ImageFileNameMap[BUTTON::HOVER_BUTTON_IMAGE_NAME] = "ButtonImage_31";
}

ToolsTexture :: ToolsTexture()
{
    //type = BUTTON::Tools;
    ImageFileNameMap[BUTTON::BUTTON_IMAGE_NAME] = "ButtonImage_32";
    ImageFileNameMap[BUTTON::PRESSED_BUTTON_IMAGE_NAME] = "ButtonImage_33";
    ImageFileNameMap[BUTTON::HOVER_BUTTON_IMAGE_NAME] = "ButtonImage_34";
}


BackTexture :: BackTexture()
{
    //type = BUTTON::Back;
    ImageFileNameMap[BUTTON::BUTTON_IMAGE_NAME] = "ButtonImage_35";
    ImageFileNameMap[BUTTON::PRESSED_BUTTON_IMAGE_NAME] = "ButtonImage_36";
    ImageFileNameMap[BUTTON::HOVER_BUTTON_IMAGE_NAME] = "ButtonImage_37";
}
*/

#else
ButtonTexture :: ButtonTexture() : type(BUTTON::None), ImageFileNameMap() {}


std::string ButtonTexture :: getImageName(BUTTON::ImageId id)
{
    auto it = ImageFileNameMap.find(id);
    if ( it != ImageFileNameMap.end() )
    {
        return it->second;
    }

    else throw "No Button Image File name exists for the requested enumeration type";

}

PlainTexture :: PlainTexture()
{
    type = BUTTON::Plain;
    ImageFileNameMap[BUTTON::BUTTON_IMAGE_NAME] = "ButtonImage_2";
    ImageFileNameMap[BUTTON::PRESSED_BUTTON_IMAGE_NAME] = "ButtonImage_3";
    ImageFileNameMap[BUTTON::HOVER_BUTTON_IMAGE_NAME] = "ButtonImage_4";
}



template<typename T>
xButton<T> :: xButton() : textureProp()
{
    ButtonTexture * check = static_cast<T*>(0);

    sf::Texture *pTexture = 0;
    pTexture = ResourceManager::getTexture( textureProp.getImageName( BUTTON::BUTTON_IMAGE_NAME).c_str() );
    LoadButtonTexture(pTexture);

    pTexture = ResourceManager::getTexture( textureProp.getImageName( BUTTON::PRESSED_BUTTON_IMAGE_NAME).c_str() );
    LoadPressedButtonTexture(pTexture);

    this->setTexture(*_button);
    this->setTextureRect(sf::IntRect(0,0,204,74));
}


template class xButton<PlainTexture>;

template<typename Icon>
xIconButton<Icon> :: xIconButton() : xPlainButton(),  icon(0)
{
    //Throw compiler error if Icon is not derived from ButtonIcons
    //ButtonIcons * p = static_cast<Icon>(0);

    //LoadButtonTexture(ResourceManager::getTexture("ButtonIcons"));
    //LoadPressedButtonTexture(ResourceManager::getTexture("ButtonIcons"));

    this->setTexture(*_button);
    //this->setTextureRect(BUTTON_RELEASE);

    icon = new Icon();
    icon->Load();
    setIcon = false;

}

template<typename Icon>
xIconButton<Icon> :: ~xIconButton()
{
    if ( icon != 0 ) delete icon;
}

template<typename Icon>
void xIconButton<Icon> :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    auto ConfigureIcon = [&] () -> void
    {
            auto buttonbounds = this->getGlobalBounds();
            auto iconBounds = icon->getGlobalBounds();
            float x = buttonbounds.width/(3*iconBounds.width);
            float y = buttonbounds.height/iconBounds.height;

            auto pos = this->getPosition();
            icon->setPosition(pos.x + buttonbounds.width/3 , pos.y + 2);
            sf::Color buttonColor = this->getColor();
            icon->setColor(sf::Color(buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a+100));
            icon->scale(0.88*x,0.88*y);

    };


    if (!setIcon)
    {
        ConfigureIcon();
        setIcon = !setIcon;
    }


    sf::Sprite p = static_cast<sf::Sprite>(*this);
    target.draw(p);
    target.draw(*icon);

}

template class xIconButton<ArcIcon>;
#endif
EON

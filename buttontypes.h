#ifndef BUTTONTYPES_H
#define BUTTONTYPES_H
#include "define.h"
#include "Utility.h"
#include <map>
#include <string>

//#include "InteractiveFeatures.h"
#if(BUTTON_TEST_3)
#include "button.h"
#include "buttonicons.h"
#endif


namespace sf {
class Texture;
}


namespace GUI
{

#if(BUTTON_4)
namespace BUTTON
{

enum ButtonType
{
    None,
    Plain,
    File,
    Cancel,
    Stop,
    Edit,
    Settings,
    Menu,
    Tools,
    Navigate,
    Save,
    Next,
    Back
};

enum ImageId
{
    BUTTON_IMAGE_NAME = 0,
    PRESSED_BUTTON_IMAGE_NAME = 1,
    HOVER_BUTTON_IMAGE_NAME = 2
};

EON //end of BUTTON namepsace


typedef const char * STRING;

class ButtonTexture
{

protected:
    BUTTON::ButtonType type;
    std::map<BUTTON::ImageId,std::string> ImageFileNameMap;

    ButtonTexture();

public:
    virtual ~ButtonTexture() {}
    std::string getImageName(BUTTON::ImageId id);
    virtual sf::Texture * getButtonTexture();
    virtual sf::Texture * getPressedButtonTexture();
    virtual sf::Texture * getHoverButtonTexture();
};


struct PlainTexture : public ButtonTexture
{
    PlainTexture();
};

struct FileTexture : public ButtonTexture
{
    FileTexture();
};

struct CancelTexture : public ButtonTexture
{
    CancelTexture();
};

struct EditTexture : public ButtonTexture
{
    EditTexture();
};

struct MenuTexture : public ButtonTexture
{
    MenuTexture();
};

struct NavigateTexture : public ButtonTexture
{
    NavigateTexture();
};

struct NextTexture : public ButtonTexture
{
    NextTexture();
};

struct SaveTexture : public ButtonTexture
{
    SaveTexture();
};

struct SettingsTexture : public ButtonTexture
{
    SettingsTexture();
};

struct StopTexture : public ButtonTexture
{
    StopTexture();
};


struct ToolsTexture : public ButtonTexture
{
    ToolsTexture();
};

struct BackTexture : public ButtonTexture
{
    BackTexture();
};


#else


namespace BUTTON
{

enum ButtonType
{
    None,
    Plain,
    File,
    Cancel,
    Stop,
    Edit,
    Settings,
    Menu,
    Tools,
    Navigate,
    Save,
    Next,
    Back
};

enum ImageId
{
    BUTTON_IMAGE_NAME = 0,
    PRESSED_BUTTON_IMAGE_NAME = 1,
    HOVER_BUTTON_IMAGE_NAME = 2
};

EON

typedef const char * STRING;
class ButtonTexture
{

protected:
    BUTTON::ButtonType type;
    std::map<BUTTON::ImageId,std::string> ImageFileNameMap;

    ButtonTexture();

public:
    virtual ~ButtonTexture() {}
    std::string getImageName(BUTTON::ImageId id);

};

struct PlainTexture : public ButtonTexture
{
    PlainTexture();
};


//Add Interfaces along the way
template<typename T>
class xButton : public IButton
{
private:
    T textureProp;

public:
    xButton();
    void ButtonPress() {}
    void ButtonRelease() {}

};

typedef xButton<PlainTexture> xPlainButton;

template<typename Icon>
class xIconButton : public xPlainButton
{
private:
    Icon * icon;

    mutable bool setIcon;


protected:
    /*
     * Set the texture rectangle to focus on the presed-button
     */
    //virtual void ButtonPress();
    //Set the texture rectangle to focus on the released-button
    //virtual void ButtonRelease();
    //Adjust icon to fit correctly on button
    //virtual void setIconPosition();

public:
    xIconButton();
    ~xIconButton();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif

EON
#endif // BUTTONTYPES_H

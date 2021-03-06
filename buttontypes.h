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
    Back,
    Shapes,
    Line,
    Rectangle,
    Circle,
    Triangle,
    Rhombus,
    Pentagon,
    Hexagon,
    Octagon,
    Block,
    WireFrame,
    Quad

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
public:
    //static BUTTON::ButtonType type;
    static const bool isPressable = true;
    static const bool isHoverable = true;

protected:
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
    static const BUTTON::ButtonType type = BUTTON::Plain;
    PlainTexture();

};

struct FileTexture : public ButtonTexture
{
    static const BUTTON::ButtonType type = BUTTON::File;
    FileTexture();

};


struct CancelTexture : public ButtonTexture
{
    static const BUTTON::ButtonType type = BUTTON::Cancel;
    CancelTexture();

};

struct EditTexture : public ButtonTexture
{
    static const BUTTON::ButtonType type = BUTTON::Edit;
    EditTexture();

};

struct MenuTexture : public ButtonTexture
{
    static const BUTTON::ButtonType type = BUTTON::Menu;
    MenuTexture();

};

struct ShapeTexture : public ButtonTexture
{
    static const BUTTON::ButtonType type = BUTTON::Shapes;
    ShapeTexture();

};

struct LineTexture : public ButtonTexture
{
    static const BUTTON::ButtonType type = BUTTON::Line;
    LineTexture();

};


struct RectangleTexture : public ButtonTexture
{
    static const BUTTON::ButtonType type = BUTTON::Rectangle;
    RectangleTexture();

};

struct CircleTexture : public ButtonTexture
{
    static const BUTTON::ButtonType type = BUTTON::Circle;
    CircleTexture();

};


struct TriangleTexture : public ButtonTexture
{
    static const BUTTON::ButtonType type = BUTTON::Triangle;
    TriangleTexture();

};



struct RhombusTexture : public ButtonTexture
{
    static const BUTTON::ButtonType type = BUTTON::Rhombus;
    RhombusTexture();

};

struct PentagonTexture : public ButtonTexture
{
    static const BUTTON::ButtonType type = BUTTON::Pentagon;
    PentagonTexture();

};


struct HexagonTexture : public ButtonTexture
{
    static const BUTTON::ButtonType type = BUTTON::Hexagon;
    HexagonTexture();

};


struct OctagonTexture : public ButtonTexture
{
    static const BUTTON::ButtonType type = BUTTON::Octagon;
    OctagonTexture();

};


struct BlockTexture : public ButtonTexture
{
    static const BUTTON::ButtonType type = BUTTON::Block;
    BlockTexture();

};


struct WireFrameTexture : public ButtonTexture
{
    static const BUTTON::ButtonType type = BUTTON::WireFrame;
    WireFrameTexture();

};


struct QuadTexture : public ButtonTexture
{
    static const BUTTON::ButtonType type = BUTTON::Quad;
    QuadTexture();

};



/*
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


class ButtonText : public ButtonTexture
{
    static const bool isPressable = true;
    static const bool isHoverable = true;



};
*/


EON
#endif // BUTTONTYPES_H

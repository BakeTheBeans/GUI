#ifndef BUTTONICONS_H
#define BUTTONICONS_H
#include "Utility.h"
#include <SFML/Graphics.hpp>
#include "define.h"


namespace GUI {


class ButtonIcons : public sf::Sprite
{
private:
   static const char* ImageFiles[];
   sf::Texture * _icon;

   virtual void setTextureRegion()=0;

public:
   //ImageIndex points to the texture to be used.
   //Add more textures to the ImageFile
    ButtonIcons(int ImageIndex = 1);
    virtual ~ButtonIcons() {}
    void Load()
    {
        setTextureRegion();
    }
};



struct ArcIcon : public ButtonIcons
{
    ArcIcon() : ButtonIcons(0) {}
    void setTextureRegion()
    {
        this->setTextureRect( ARC_ICON );
    }
};

struct AttachmentIcon : public ButtonIcons
{
    AttachmentIcon() : ButtonIcons(0) {}
    void setTextureRegion()
    {
        this->setTextureRect(ATTACHMENT_ICON );
    }
};

struct BoldIcon : public ButtonIcons
{
    BoldIcon() : ButtonIcons(0) {}
    void setTextureRegion()
    {
        this->setTextureRect(BOLD_ICON );
    }
};

struct CircleIcon : public ButtonIcons
{
    CircleIcon() : ButtonIcons(0) {}
    void setTextureRegion()
    {
        this->setTextureRect(CIRCLE_ICON);
    }
};

struct FileIcon : public ButtonIcons
{
    FileIcon() : ButtonIcons(0) {}
    void setTextureRegion()
    {
        this->setTextureRect(FILE_ICON);
    }
};

struct FontIcon : public ButtonIcons
{
    FontIcon() : ButtonIcons(0) {}
    void setTextureRegion()
    {
        this->setTextureRect(FONT_ICON);
    }
};

struct HomeIcon : public ButtonIcons
{
    HomeIcon() : ButtonIcons(0) {}
    void setTextureRegion()
    {
        this->setTextureRect(HOME_ICON);
    }
};


struct ItalicIcon : public ButtonIcons
{
    ItalicIcon() : ButtonIcons(0) {}
    void setTextureRegion()
    {
        this->setTextureRect(ITALIC_ICON);
    }
};

struct LineIcon : public ButtonIcons
{
    LineIcon() : ButtonIcons(0) {}
    void setTextureRegion()
    {
        this->setTextureRect(LINE_ICON);
    }
};

struct PencilIcon : public ButtonIcons
{
    PencilIcon() : ButtonIcons(0) {}
    void setTextureRegion()
    {
        this->setTextureRect(PENCIL_ICON);
    }
};

struct PickColorIcon : public ButtonIcons
{
    PickColorIcon() : ButtonIcons(0) {}
    void setTextureRegion()
    {
        this->setTextureRect(PICK_COLOR_ICON);
    }
};

struct PolygonIcon : public ButtonIcons
{
    PolygonIcon() : ButtonIcons(0) {}
    void setTextureRegion()
    {
        this->setTextureRect(POLYGON_ICON);
    }
};


struct PowerIcon : public ButtonIcons
{
    PowerIcon() : ButtonIcons(0) {}
    void setTextureRegion()
    {
        this->setTextureRect(POWER_ICON);
    }
};


struct RefreshIcon : public ButtonIcons
{
    RefreshIcon() : ButtonIcons(0) {}
    void setTextureRegion()
    {
        this->setTextureRect(REFRESH_ICON);
    }
};


struct SearchIcon : public ButtonIcons
{
    SearchIcon() : ButtonIcons(0) {}
    void setTextureRegion()
    {
        this->setTextureRect(SEARCH_ICON);
    }
};

struct SquareIcon : public ButtonIcons
{
    SquareIcon() : ButtonIcons(0) {}
    void setTextureRegion()
    {
        this->setTextureRect(SQUARE_ICON);
    }
};

struct TrashIcon : public ButtonIcons
{
    TrashIcon() : ButtonIcons(0) {}
    void setTextureRegion()
    {
        this->setTextureRect(TRASH_ICON);
    }
};

EON

#endif // BUTTONICONS_H

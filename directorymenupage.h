#ifndef DIRECTORYMENUPAGE_H
#define DIRECTORYMENUPAGE_H
#include "define.h"

#include "menupage.h"
#include "window.h"
#include "tools.h"
#include "Traits.h"
#include "buttonevent.h"

namespace  GUI {

class DirectoryMenuPage : public  MenuPage
{
    static const int MaxDisplayTiles;
    //static const float DefaultSlabHeight;

    std::vector<DirectoryInfo> infoList;
    bool isDirectoryChanged;
    std::string curDir;


private:
 void SetUpNewDirectory();


public:
    DirectoryMenuPage();
    ~DirectoryMenuPage() {}
    bool MoveUpDirectory();
    bool MoveIntoDirectory(std::string folder);
    void ChangeDirectory(std::string newPath);
    const std::string & getCurrentDirectoryName() { return curDir; }    
    bool InteractWithMouse(sf::Window * window);

    bool ActionOnPressingReturn();
    void ActionOnPressingDownArrow();
    void ActionOnPressingUpArrow();

};


template<>
struct ScrollableEntityTrait<DirectoryMenuPage>
{
    static const bool CanAdaptToWindow = false;
};



}//EON

#endif // DIRECTORYMENUPAGE_H

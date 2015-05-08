#ifndef DIRECTORYMENUPAGE_H
#define DIRECTORYMENUPAGE_H
#include "define.h"

#include "menupage.h"
#include "window.h"
#include "tools.h"
#include "Traits.h"

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
    const std::string & getCurrentDirectoryName() { return curDir; }
};


template<>
struct ScrollableEntityTrait<DirectoryMenuPage>
{
    static const bool CanAdaptToWindow = false;
};



}//EON

#endif // DIRECTORYMENUPAGE_H

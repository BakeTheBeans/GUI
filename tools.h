#ifndef TOOLS_H
#define TOOLS_H

#include "define.h"
#include "scroll.h"
#include "interfaces.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <vector>


struct stat;

namespace GUI {

struct DirectoryInfo
{
    enum FileType
    {
        File,
        Directory,
        IDC             //I don't care
    };

    std::string basePath;
    FileType type;
    std::string fileName;
    std::string lastAccessTime;
    std::string lastModTime;
    std::string size;
 };


class Directory
{

private:
    //static bool EnterSubDirectory(std::string dirName);
    static std::string getTimeStamp(time_t & t );
    static DirectoryInfo::FileType getFileType(struct stat * bufStat);
public:

    static std::string getCurrentDirectoryPath(const int LIMIT= 1000);
    static std::vector<DirectoryInfo> getDirectoryContents(std::string _path);
    static std::string getFullPath( DirectoryInfo & info);

};


EON
#endif // TOOLS_H

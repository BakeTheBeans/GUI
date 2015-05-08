#include "tools.h"
#include <algorithm>
#include "string.h"
#include <sstream>
#include <utility>
#include "scroll.h"
#include <dirent.h>
#include <unistd.h>
#include "time.h"
#include <sys/stat.h>


namespace GUI {


std::string Directory :: getCurrentDirectoryPath(const int LIMIT)
{
  //  const int LIMIT = 1000;
    int _size = 20;
    int count = 1;
    char * buf = new char[_size*count];

    while( getcwd(buf,count*_size) == NULL )
    {
        count++;
        delete [] buf;
        if ( count*_size > LIMIT ) throw "Could not fetch curent directory name. Eiother directory cannot be accessed or name is too long";
        buf = new char[count*_size];
    }

    //currentDirPath = std::string(buf);
    return std::string(buf);
}


DirectoryInfo::FileType Directory :: getFileType(struct stat * bufStat)
{
    DirectoryInfo::FileType flag;
    switch (bufStat->st_mode & S_IFMT)
    {
    case S_IFBLK:  flag = DirectoryInfo::IDC; break;
    case S_IFCHR:  flag = DirectoryInfo::IDC; break;
    case S_IFDIR:  flag = DirectoryInfo::Directory; break;
    case S_IFIFO:  flag = DirectoryInfo::IDC; break;
    case S_IFLNK:  flag = DirectoryInfo::IDC; break;
    case S_IFREG:  flag = DirectoryInfo::File; break;
    case S_IFSOCK: flag = DirectoryInfo::IDC; break;
    default: flag = DirectoryInfo::IDC; break;

    };
    return flag;
}

std::string Directory :: getTimeStamp(time_t & t )
{
    std::stringstream ss;
    //time_t t  =  bufStat.st_ctim.tv_sec;
    struct tm * timeInfo = localtime(&t);

    ss << timeInfo->tm_mday << " ";

    switch(timeInfo->tm_mon)
    {
        case 0: ss << "Jan" << " "; break;
        case 1: ss << "Feb" << " "; break;
        case 2: ss << "Mar" << " "; break;
        case 3: ss << "Apr" << " "; break;
        case 4: ss << "May" << " "; break;
        case 5: ss << "Jun" << " "; break;
        case 6: ss << "Jul" << " "; break;
        case 7: ss << "Aug" << " "; break;
        case 8: ss << "Sep" << " "; break;
        case 9: ss << "Oct" << " "; break;
        case 10: ss << "Nov" << " "; break;
        case 11: ss << "Dec" << " "; break;
    }

        ss << (timeInfo->tm_year + 1900);
        return ss.str();
}


std::string Directory :: getFullPath( DirectoryInfo & info)
{
    std::string subPath = info.basePath + "/" + std::string(info.fileName);
    return subPath;
}

std::vector<DirectoryInfo> Directory :: getDirectoryContents(std::string _path)
{
    dirent * directoryStruct = 0;
    std::vector<DirectoryInfo> infoList;
    DIR * curDir = opendir(_path.c_str());
    if ( curDir == 0)  throw "Could not open the directory";


    while( (directoryStruct = readdir(curDir)) )
    {
        infoList.push_back(DirectoryInfo());
        DirectoryInfo & info = infoList[infoList.size()-1];
        info.fileName = std::string(directoryStruct->d_name);
        info.basePath = _path;
        std::string subPath = _path + "/" + std::string(info.fileName);

        struct stat bufStat;
        lstat( subPath.c_str(), &bufStat );

        info.size = bufStat.st_size;
        info.type = getFileType(&bufStat);

        info.lastAccessTime = getTimeStamp( bufStat.st_atim.tv_sec );
        info.lastModTime = getTimeStamp(( bufStat.st_mtim.tv_sec));

    }

    return infoList;
}

}//EON

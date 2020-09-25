#include "../headers/FileSys.h"

FileSys::FileSys()
{
    actualDir.name = "/";
    actualDir.parentPath = "";
    actualDir.path = "/";
    entriesInDir = getAllInPath(actualDir.path);
}

bool FileSys::createFolder(std::string nameFol)
{
    std::string createCommand = "mkdir '"+ actualDir.path+"/"+nameFol+"'";
    int status = system(createCommand.c_str());
    if(!status)
    {
        return true;
    }
    return false;
}

bool FileSys::createFile(std::string nameFil)
{
    std::string createCommand = "touch '"+ actualDir.path+"/"+nameFil+"'";
    int status = system(createCommand.c_str());
    if(!status)
    {
        return true;
    }
    return false;
}

void FileSys::openFile(int posInVectorFiles)
{
    std::string file = "gio open '"+ entriesInDir[posInVectorFiles].path+"/"+entriesInDir[posInVectorFiles].name+"'";
    int status = system(file.c_str());
}

void FileSys::updateActualDirEntries()
{
    entriesInDir = getAllInPath(actualDir.path);
}

bool FileSys::deleteFileFolder(std::string name)
{
    std::string createCommand = "rm -rf '"+ actualDir.path+"/"+name+"'";
    int status = system(createCommand.c_str());
    if(!status)
    {
        return true;
    }
    return false;
}

bool FileSys::copyFileFolder(std::string name, std::string copyName)
{
    std::string createCommand = "cp '"+ actualDir.path+"/"+name+"' '"+ actualDir.path+"/"+copyName+"' ";
    int status = system(createCommand.c_str());
    if(!status)
    {
        return true;
    }
    createCommand = "cp -r '"+ actualDir.path+"/"+name+"' '"+ actualDir.path+"/"+copyName+"' ";
    status = system(createCommand.c_str());
    if(!status)
    {
        return true;
    }
    return false;
}

bool FileSys::createLn(std::string name,bool isH)
{
    std::string createCommand = "ln -s '"+ actualDir.path+"/"+name+"' '"+ actualDir.path+"/Link to "+name+"' ";
    if(isH)
    {
        createCommand = "ln '"+ actualDir.path+"/"+name+"' '"+ actualDir.path+"/HLink to "+name+"' ";
    }
    int status = system(createCommand.c_str());
    if(!status)
    {
        return true;
    }
    return false;
}

bool FileSys::moveFileFolder(std::string oldPath, std::string newPath)
{
    std::string createCommand = "mv '"+oldPath+"' '"+newPath+"' ";
    int status = system(createCommand.c_str());
    if(!status)
    {
        return true;
    }
    return false;
}

std::vector<struct entry> FileSys::getAllInPath(std::string path)
{
    DIR *dirp;
    struct dirent *directory;
    std::vector<struct entry> data;
    dirp = opendir(path.c_str());
    if (dirp)
    {
        while ((directory = readdir(dirp)) != NULL)
        {
            struct entry tmp;
            tmp.name = directory->d_name;
            tmp.path = path;
            tmp.isDir = directory->d_type != DT_REG? true: false;
            
            if(tmp.name.substr(0,1) != ".")
            {
                data.push_back(tmp);
            }
        }

        closedir(dirp);
    }
    return data;
}
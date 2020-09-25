#ifndef FILESYS_H
#define FILESYS_H


#include <iostream>
#include <vector>
#include <fstream>
#include <dirent.h>
#include <stdio.h>
#include "Utilities.h"
#include <thread>

struct Mount {
    std::string device;
    std::string destination;
    std::string fstype;
    std::string options;
    int dump;
    int pass;
};

struct entry{
    std::string name = "";
    std::string path;
    std::string parentPath;
    bool isDir;
};

class FileSys
{
    public:
        FileSys();
        void openFile(int posInVectorFiles);
        bool createFolder(std::string nameFol);
        bool createFile(std::string nameFil);
        bool deleteFileFolder(std::string name);
        bool createLn(std::string name,bool isH);
        bool copyFileFolder(std::string name, std::string copyName);
        bool moveFileFolder(std::string oldPath, std::string newPath);
        void updateActualDirEntries();
        void changeDir(std::string nameDir);
        void changePartition(std::string partitionName);
        std::vector<struct Mount> partitions;
        struct entry actualDir;
        struct entry getEntryByName(std::string name);
        std::vector<struct entry> entriesInDir;

    private:
        std::vector<struct entry> getAllInPath(std::string path);
        std::vector<struct Mount> getPartitionsName();

        


};

#endif
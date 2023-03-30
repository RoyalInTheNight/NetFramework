//
// Created by MikoG on 30.03.2023.
//

#ifndef NETFRAMEWORK_IFS_H
#define NETFRAMEWORK_IFS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "../Core.h"

class IFileSystem {
    static std::string     filename;
    static std::fstream file_stream;

public:
    IFileSystem(const IFileSystem&);

    #ifdef WIN64
        core::fs::fs_path AppData();
    #endif

    core::fs::fs_path Temp(); // for cache
    core::fs::fs_path Home();

    std::streampos GetFileSize(std::string& = filename);

    std::string & ReadFile(std::string& = filename);
    void WriteFile(std::string& = filename);

    void WriteCache(std::string&, std::string& = filename);
    std::string &ReadCache();

    ~IFileSystem();
};

#endif //NETFRAMEWORK_IFS_H

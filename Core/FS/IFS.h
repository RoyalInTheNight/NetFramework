#ifndef NETFRAMEWORK_IFS_H
#define NETFRAMEWORK_IFS_H

#import <vector>
#import <string>
#import <thread>
#import <fstream>
#import <iostream>

#import "../Core.h"

class IFileSystem {
    static std::string     filename;
    static std::fstream file_stream;

public:
    IFileSystem(const IFileSystem&);
    IFileSystem(const std::string&);

    #ifdef WIN64
        core::fs::fs_path AppData();
    #endif

    core::fs::fs_path Temp(); // for cache
    core::fs::fs_path Home();

    std::streampos GetFileSize(std::string& = filename);

    std::vector<core::word>& ReadFile(std::string& = filename);
    core::empty_type WriteFile(std::string&, std::string& = filename);
    core::empty_type WriteFile(std::vector<std::string>&, std::string& = filename);

    void WriteCache(std::string&, std::string& = filename);
    std::vector<core::word>& ReadCache();

    ~IFileSystem();
};

#endif //NETFRAMEWORK_IFS_H

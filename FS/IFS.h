#ifndef NETFRAMEWORK_IFS_H
#define NETFRAMEWORK_IFS_H

#include <fstream>
#include <filesystem>
#include "../ISPtr.h"
#include "../Core.h"

namespace fs = std::filesystem;
namespace sptr     = core::ptr;

class IFileSystem {
private:
    std::ifstream     out_file;
    std::ofstream      in_file;

public:
    std::streampos GetFileSize(const fs::path&);

    std::string       ReadFile(const fs::path&);
    core::empty_type WriteFile(const fs::path&, const std::string&);
    core::empty_type WriteFile(const fs::path&, const std::vector<std::string>&);

    core::comparsion RemoveFile(const fs::path&);

    ~IFileSystem();
};

#endif //NETFRAMEWORK_IFS_H

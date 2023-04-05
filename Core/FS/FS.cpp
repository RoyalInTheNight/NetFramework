//
// Created by MikoG on 30.03.2023.
//
#include "IFS.h"

IFileSystem::IFileSystem(const IFileSystem &fs_copy) {
    *this = std::move(fs_copy);

    this->file_stream.open(this->filename);
}

IFileSystem::IFileSystem(const std::string &filename) {
    this->filename = std::move(filename);
}

#ifdef WIN64
    core::fs::fs_path IFileSystem::AppData() {
        return std::getenv((const core::fs::fs_path)"APPDATA");
    }
#endif

core::fs::fs_path IFileSystem::Home() {
    return std::getenv((const core::fs::fs_path)"HOME");
}

core::fs::fs_path IFileSystem::Temp() {
    return std::getenv((const core::fs::fs_path)"TEMP");
}

std::streampos IFileSystem::GetFileSize(std::string &filename) {
    std::streampos file_size = 0;

    if (this->filename == filename) {
        this->file_stream.seekg(0, std::ios_base::end);
        file_size = std::move(this->file_stream.tellg());
    }

    else {
        this->file_stream.close();
        this->file_stream.open(filename, std::ios_base::binary);

        this->file_stream.seekg(0, std::ios_base::end);
        file_size = std::move(this->file_stream.tellg());
        this->file_stream.close();
        this->file_stream.open(this->filename, std::ios_base::binary);
    }

    return file_size;
}

std::vector<core::word>& IFileSystem::ReadFile(std::string &filename) {
    std::vector<core::word> *buffer_v = new std::vector<core::word>(GetFileSize(filename));

    if (this->filename == filename) {
        this->file_stream.read(buffer_v->data(), std::move(GetFileSize()));
    }

    else {
        this->file_stream.close();
        this->file_stream.open(filename, std::ios_base::binary);
        this->file_stream.read(buffer_v->data(), std::move(GetFileSize()));
        this->file_stream.close();
        this->file_stream.open(this->filename, std::ios_base::binary);
    }

    return *buffer_v;
}

IFileSystem::~IFileSystem() {
    this->file_stream.close();
}
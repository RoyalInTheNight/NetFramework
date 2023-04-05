//
// Created by MikoG on 30.03.2023.
//
#include "IFS.h"

IFileSystem::IFileSystem(const IFileSystem &fs_copy) {
    *this = fs_copy;

    this->file_stream.open(this->filename);
}

core::fs::fs_path IFileSystem::AppData() {
    return std::getenv((const core::fs::fs_path)"APPDATA");
}

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
        file_size = this->file_stream.tellg();
    }

    else {
        this->file_stream.close();
        this->file_stream.open(filename, std::ios_base::binary);

        this->file_stream.seekg(0, std::ios_base::end);
        file_size = this->file_stream.tellg();
        this->file_stream.close();
        this->file_stream.open(this->filename, std::ios_base::binary);
    }

    return file_size;
}

std::string& IFileSystem::ReadFile(std::string &filename) {


    if (this->filename == filename) {
        core::fs::fs_path buffer = new core::word[GetFileSize()];
        this->file_stream.read(buffer, GetFileSize());
    }

    else {
        this->file_stream.close();
        this->file_stream.open(filename, std::ios_base::binary);

        core::fs::fs_path buffer = new core::word[GetFileSize()];

        this->file_stream.read(buffer, GetFileSize());
        this->file_stream.close();
        this->file_stream.open(this->filename, std::ios_base::binary);
    }
}

IFileSystem::~IFileSystem() {
    this->file_stream.close();
}
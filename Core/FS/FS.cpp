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

core::empty_type IFileSystem::WriteFile(std::string &data, std::string &filename) {
    if(filename == this -> filename)
        this -> file_stream.write(data.c_str(), data.size());
    else {
        this -> file_stream.close();
        this -> file_stream.open(filename, std::ios_base::binary);

        this -> file_stream.write(data.c_str(), data.size());

        this -> file_stream.close();
        this -> file_stream.open(this -> filename, std::ios_base::binary);
    }
}

core::empty_type IFileSystem::WriteFile(std::vector<std::string>&data, std::string &filename) {
    if(filename == this -> filename) {
        int mn1 = 0, mn2 = 10;
        for (int i = 0; i < data.size() % 10; i++) {
            int mn3 = 0;
            std::vector<std::string> *strings = new std::vector<std::string>();
            for (int y = mn1; y < mn2; y++) {
                strings->at(mn3) = data[y];
                mn3++;
            }
            mn1 += 10;
            mn2 += 10;
            std::thread([&]() {
                for (std::string msg: *strings)
                    this->file_stream.write(msg.c_str(), msg.size());
            }).join();
        }
        for (int i = (data.size() % 10 * 10); i < data.size(); i++)
            this->file_stream.write(data[i].c_str(), data[i].size());
    }
    else {
        this -> file_stream.close();
        this -> file_stream.open(filename, std::ios_base::binary);

        int mn1 = 0, mn2 = 10;
        for (int i = 0; i < data.size() % 10; i++) {
            int mn3 = 0;
            std::vector<std::string> *strings = new std::vector<std::string>();
            for (int y = mn1; y < mn2; y++) {
                strings->at(mn3) = data[y];
                mn3++;
            }
            mn1 += 10;
            mn2 += 10;
            std::thread([&]() {
                for (std::string msg: *strings)
                    this->file_stream.write(msg.c_str(), msg.size());
            }).join();
        }
        for (int i = (data.size() % 10 * 10); i < data.size(); i++)
            this->file_stream.write(data[i].c_str(), data[i].size());

        this -> file_stream.close();
        this -> file_stream.open(this -> filename, std::ios_base::binary);
    }
}

IFileSystem::~IFileSystem() {
    this->file_stream.close();
}
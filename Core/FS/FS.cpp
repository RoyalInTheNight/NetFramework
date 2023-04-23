//
// Created by MikoG on 30.03.2023.
//
#include "IFS.h"
#include <exception>

std::streampos IFileSystem::GetFileSize(const fs::path& path) {
    std::streampos file_size = 0;

    out_file.open(path, std::ios_base::binary);

    if (out_file.fail())
        throw std::runtime_error("Error get size\n");

    else {
        file_size = out_file.tellg();
        out_file.seekg(0, std::ios::end);
        file_size = out_file.tellg() - file_size;

        out_file.close();
    }

    return file_size;
}

std::string IFileSystem::ReadFile(const fs::path &path) {
    ISPtr<core::int8_t> buffer((sptr::size_t)GetFileSize(path));

    out_file.open(path, std::ios_base::binary);

    if (out_file.fail())
        throw std::runtime_error("File open error\n");

    else {
        out_file.read(buffer.memory(), buffer.size());
        out_file.close();
    }

    std::string return_buffer = buffer.memory();

    return return_buffer;
}

core::empty_type IFileSystem::WriteFile(const fs::path &path, const std::string& data) {
    in_file.open(path, std::ios_base::binary);

    if (in_file.is_open()) {
        in_file.write(data.c_str(), data.size());
        in_file.close();
    }

    else
        throw std::runtime_error("Error open file\n");
}

core::empty_type IFileSystem::WriteFile(const fs::path &path, const std::vector<std::string> &data) {
    in_file.open(path, std::ios_base::binary);

    if (in_file.is_open()) {
        for (const auto& str : data)
            in_file.write(str.c_str(), str.size());
        in_file.close();
    }
    else
        throw std::runtime_error("Error open file\n");
}

core::empty_type WriteFile(const fs::path &path, const std::vector<std::vector<core::blob::_8bits>> &data {
    in_file.open(path, std::ios_base::binary);

    if (in_file.is_open()) {
        for(int i=0; i < data.size(); i++)
            for(auto &str : data.at(i))
                in_file.write(str.to_string(), str.size());
        in_file.close();
    }
    else
        throw std::runtime_error("Error open file\n");
}

core::comparsion IFileSystem::RemoveFile(const fs::path &path) {
    return fs::remove(path);
}

IFileSystem::~IFileSystem() {
    if (out_file.is_open())
        out_file.close();

    if (in_file.is_open())
        in_file.close();
}

/*core::empty_type IFileSystem::WriteFile(std::vector<std::string>&data, std::string &filename) {
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
}*/
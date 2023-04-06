//
// Created by MikoG on 06.04.2023.
//

#ifndef NETFRAMEWORK_ISPTR_H
#define NETFRAMEWORK_ISPTR_H
//
#include "Core.h"
#include <iostream>

template<class pointer_t> class ISPtr {
private:
    pointer_t            *ptr;
    core::uint64_t size_alloc;

public:
    ISPtr(ISPtr<pointer_t> &copy) {
        *this = std::move(copy);

        std::cout << "Constructor input" << std::endl;
    }

    ISPtr(core::uint64_t size) : size_alloc(size) {
        if (this->size_alloc > 1)
            this->ptr = new pointer_t[size];

        else
            this->ptr = new pointer_t;

        std::cout << "Constructor input" << std::endl;
    }

    ISPtr() : size_alloc(1) {
        this->ptr = new pointer_t;

        std::cout << "Constructor input" << std::endl;
    }

    pointer_t& operator*() {
        return *this->ptr;
    }

    pointer_t& operator[](core::uint64_t pos) {
        if (pos >= this->size_alloc) {
            std::cerr << "out of range - pos: " << pos << " >= size_alloc: " << this->size_alloc << std::endl;
            exit(-1);
        }

        else
            return this->ptr[pos];
    }

    void add_memory() {
        this->ptr = new pointer_t[1];
        this->size_alloc++;
    }

    void add_memory(core::uint64_t size) {
        this->ptr = new pointer_t[size];
        this->size_alloc += size;
    }

    inline core::uint64_t size() {
        return this->size_alloc;
    }

    inline core::uint64_t bytes_size() {
        return sizeof(pointer_t) * this->size_alloc;
    }

    ~ISPtr() {
        if (size_alloc > 1)
            delete[] this->ptr;

        else
            delete this->ptr;

        std::cout << "Destructor input" << std::endl;
    }
};

#endif //NETFRAMEWORK_ISPTR_H

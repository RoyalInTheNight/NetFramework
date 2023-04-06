//
// Created by MikoG on 06.04.2023.
//

#ifndef NETFRAMEWORK_ISPTR_H
#define NETFRAMEWORK_ISPTR_H
//
#include "Core.h"
#include <iostream>

namespace ptr {
    core::int32_t user_type = 0;
}

template<class pointer_t> class ISPtr {
private:
    pointer_t            *ptr;
    core::uint64_t size_alloc;

public:
    ISPtr(ISPtr<pointer_t> &copy) {
        *this = std::move(copy);
    }

    ISPtr(core::uint64_t size) : size_alloc(size) {
        this->ptr = new pointer_t[size];
    }

    ISPtr() : size_alloc(1) {
        this->ptr = new pointer_t;
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
    }
};

#endif //NETFRAMEWORK_ISPTR_H

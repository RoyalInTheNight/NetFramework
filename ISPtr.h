//
// Created by MikoG on 06.04.2023.
//

#ifndef NETFRAMEWORK_ISPTR_H
#define NETFRAMEWORK_ISPTR_H
//
#include "Core.h"
#include <iostream>
#include <exception>

namespace sptr = core::ptr;

template<class ptr_t> class ISPtr {
private:
    ptr_t              *ptr;
    sptr::size_t size_alloc;

public:
    ISPtr(sptr::size_t size) : size_alloc(size) {
        ptr = new ptr_t[size_alloc];
    }

    ISPtr(const ISPtr<ptr_t> &isPtr) {
        ptr        = isPtr.ptr;
        size_alloc = isPtr.size_alloc;
    }

    ISPtr() : size_alloc(1) {
        ptr = new ptr_t();
    }

    ptr_t& data() {
        return *ptr;
    }

    ptr_t* memory() {
        return ptr;
    }

    ptr_t& operator[](sptr::size_t size) {
        if (size_alloc <= size)
            throw std::runtime_error("out of range - pos: " + std::to_string(size) + " >= size_alloc: " + std::to_string(size_alloc) + "\n");

        return *(ptr + size);
    }

    sptr::size_t size() {
        return size_alloc;
    }

    sptr::size_t length() {
        return size_alloc - 1;
    }

    ~ISPtr() {
        if (size_alloc > 1)
            delete[] ptr;

        else
            delete ptr;
    }
};


#endif //NETFRAMEWORK_ISPTR_H

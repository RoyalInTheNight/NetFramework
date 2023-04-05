//
// Created by MikoG on 06.04.2023.
//
#include "ISPtr.h"

template<class pointer_t> ISPtr<pointer_t>::ISPtr(const ISPtr<pointer_t> &pointer) {
    *this = std::move(pointer);
}

template<class pointer_t> ISPtr<pointer_t>::ISPtr(const core::uint64_t size_alloc) {
    this->ptr        = std::move(new pointer_t[size_alloc]);
    this->size_alloc = std::move(size_alloc);
}

template<class pointer_t> ISPtr<pointer_t>::ISPtr() {
    this->ptr        = std::move(new pointer_t());
    this->size_alloc = std::move(1);
}

template<class pointer_t> pointer_t &ISPtr<pointer_t>::get_data() {
    return *this->ptr;
}

template<class pointer_t> pointer_t ISPtr<pointer_t>::operator[](core::uint64_t pos) {
    if (this->size_alloc > 1)
        return *(this->ptr + pos);

    else {
        std::cerr << "pointer size == 1: you size == " << pos << std::endl;
        ~ISPtr<pointer_t>();
    }
}

template<class pointer_t> ISPtr<pointer_t>& ISPtr<pointer_t>::operator=(ISPtr<pointer_t> &obj) {
    *this = std::move(obj);

    return *this;
}

template<class pointer_t> ISPtr<pointer_t>& ISPtr<pointer_t>::operator+(ISPtr<pointer_t> &obj) {
    if (*this == obj) {
        this->ptr = new pointer_t[obj.size_alloc];

        for (core::uint64_t i = this->size_alloc + 1; i < this->size_alloc + obj.size_alloc; i++)
            *(this->ptr + i) = std::move(*(obj.ptr + i - this->size_alloc));
    }

    else {
        std::cerr << "pointers types !=" << std::endl;
        ~ISPtr<pointer_t>();
    }

    return *this;
}

template<class pointer_t> core::comparison ISPtr<pointer_t>::operator==(ISPtr<pointer_t> &obj) {
    if ((uintptr_t)this->ptr % sizeof(decltype(*obj.ptr)) != 0)
        return 0;

    return 1;
}

template<class pointer_t> ISPtr<pointer_t>::~ISPtr() {
    if (this->size_alloc == 1)
        delete this->ptr;

    else
        delete[] this->ptr;
}
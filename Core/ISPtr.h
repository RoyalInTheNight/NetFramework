//
// Created by MikoG on 06.04.2023.
//

#ifndef NETFRAMEWORK_ISPTR_H
#define NETFRAMEWORK_ISPTR_H

#include "Core.h"
#include <iostream>

template<class pointer_t> class ISPtr {
private:
    pointer_t            *ptr;
    core::uint64_t size_alloc;

public:
    ISPtr(const core::uint64_t);
    ISPtr(const ISPtr<pointer_t>&);
    ISPtr();

    pointer_t& get_data();

    ISPtr<pointer_t>& operator+(ISPtr<pointer_t>&);
    ISPtr<pointer_t>& operator=(ISPtr<pointer_t>&);
    core::comparison operator==(ISPtr<pointer_t>&);
    pointer_t operator[](core::uint64_t);

    ~ISPtr();
};

#endif //NETFRAMEWORK_ISPTR_H

//
// Created by MikoG on 06.04.2023.
//

#include "ISPtr.h"
#include <thread>
//
core::int32_t main() {
    ISPtr<core::int32_t> pointer(3423123);

    uintptr_t begin_address_decimal = (uintptr_t)&pointer[0];
    uintptr_t end_address_decimal   = (uintptr_t)&pointer[pointer.size() - 1];

    std::cout << "begin address: " << &pointer[0] <<
                 "\nend address: " << &pointer[pointer.size() - 1] <<
                 "\nsize pointer: " << pointer.size() << std::endl; // test size output and alloc size

    std::cout << "size according to calculations: " << (end_address_decimal - begin_address_decimal) / sizeof(core::int32_t) << std::endl;

    // add_memory() test
    pointer.add_memory();

    begin_address_decimal = (uintptr_t)&pointer[0];
    end_address_decimal   = (uintptr_t)&pointer[pointer.size() - 1];

    std::cout << "begin address: " << &pointer[0] <<
                 "\nend address: " << &pointer[pointer.size() - 1] <<
                 "\nsize pointer: " << pointer.size() << std::endl; // test size output and alloc size

    std::cout << "size according to calculations: " << (end_address_decimal - begin_address_decimal) / sizeof(core::int32_t) << std::endl;

    // add_memory(core::uint64_t) test
    pointer.add_memory(1000000);

    begin_address_decimal = (uintptr_t)&pointer[0];
    end_address_decimal   = (uintptr_t)&pointer[pointer.size() - 1];

    std::cout << "begin address: " << &pointer[0] <<
                 "\nend address: " << &pointer[pointer.size() - 1] <<
                 "\nsize pointer: " << pointer.size() << std::endl; // test size output and alloc size

    std::cout << "size according to calculations: " << (end_address_decimal - begin_address_decimal) / sizeof(core::int32_t) << std::endl;

    // test of writing a number to a memory area
    for (core::uint64_t i = 0; i < pointer.size() - 1; i++)
        pointer[i] = i;

    std::cout << "begin index: " << pointer[0] << "\nend index: " << pointer[pointer.size() - 1] << std::endl;
}
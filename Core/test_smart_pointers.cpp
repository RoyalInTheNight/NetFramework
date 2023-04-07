//
// Created by MikoG on 06.04.2023.
//

#include "ISPtr.h"
#include <iostream>

core::int32_t main() {
    ISPtr<core::int32_t> array(2147483646);

    for (core::int32_t i = 0; i < array.size(); i++)
        array[i] = i;

    for (core::int32_t i = 2147000000; i < array.size(); i++)
        std::cout << array[i] << std::endl;
}
//
// Created by MikoG on 30.03.2023.
//

#ifndef NETFRAMEWORK_CORE_H
#define NETFRAMEWORK_CORE_H

namespace core {
    typedef signed char          int8_t;
    typedef char                   word;
    typedef unsigned char       uint8_t;
    typedef short               int16_t;
    typedef unsigned short     uint16_t;
    typedef int                 int32_t;
    typedef unsigned int       uint32_t;
    typedef long long           int64_t;
    typedef unsigned long long uint64_t;

    namespace fs {
        typedef core::word *  fs_path;
    }
}

#endif //NETFRAMEWORK_CORE_H

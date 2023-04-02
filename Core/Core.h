//
// Created by MikoG on 30.03.2023.
//

#ifndef NETFRAMEWORK_CORE_H
#define NETFRAMEWORK_CORE_H

namespace core {
    // переопределение основных типов данных
    typedef signed char          int8_t;
    typedef char                   word;
    typedef unsigned char       uint8_t;
    typedef short               int16_t;
    typedef unsigned short     uint16_t;
    typedef int                 int32_t;
    typedef unsigned int       uint32_t;
    typedef long long           int64_t;
    typedef unsigned long long uint64_t;

    // замена типа void, void *
    typedef void                 empty_type;
    typedef core::empty_type *memory_buffer;

    // замена типа, для библиотеки fs
    namespace fs {
        typedef core::word *  fs_path;
    }

    // замена типов и инициализация констант для библиотеки net
    namespace net {
        typedef core::word *winsock_buffer_type;

        const std::string &tcp = "tcp:pick";
        const std::string &udp = "udp:pick";

        // enumeration удобное представление чисел, чтобы не запутаться и сделать код читаемым
        enum net_treatment_part {
            connect = 0, // 0
            bind, // 1
            accept // 2
        };

        #ifndef WIN64 // linux const's
            const static core::int64_t  INVALID_SOCKET = (-1);
            const static core::int32_t  SOCKET_ERROR   = (-1);
        #endif // WIN64
    }
}

#endif //NETFRAMEWORK_CORE_H

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

   namespace net {
        typedef core::word *                winsock_buffer_t;
        typedef std::string::size_type size_winsock_buffer_t;

        const std::string tcp = "tcp";
        const std::string udp = "udp";

        enum isocket {
            connect = 0x0,
            bind,
            accept
        };

        enum linux_errs {
            init_err = 0x21,
            socket_err,
            bind_err,
            connect_err,
            listen_err,
            accept_err,
            send_err,
            recv_err,
            sendto_err,
            recvfrom_err
        };
   }
}

#endif //NETFRAMEWORK_CORE_H

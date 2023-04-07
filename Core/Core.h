//
// Created by MikoG on 30.03.2023.
//

#ifndef NETFRAMEWORK_CORE_H
#define NETFRAMEWORK_CORE_H

#include <string>

namespace core {
    // переопределение основных типов данных
    typedef char                 int8_t;
    typedef char                   word;
    typedef unsigned char       uint8_t;
    typedef short               int16_t;
    typedef unsigned short     uint16_t;
    typedef int                 int32_t;
    typedef unsigned int       uint32_t;
    typedef long long           int64_t;
    typedef unsigned long long uint64_t;

    typedef bool             comparsion;

    // замена типа void, void *
    typedef void                 empty_type;
    typedef core::empty_type *memory_buffer;

    // замена типа, для библиотеки fs
    namespace fs {
        typedef core::word *  fs_path;
    }

    namespace ptr {
        typedef core::int32_t size_t;
    }

   namespace net {
        typedef core::word *                winsock_buffer_t;
        typedef std::string::size_type size_winsock_buffer_t;

        const static std::string tcp = "tcp";
        const static std::string udp = "udp";

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

   namespace http {
        const static std::string post           = "POST";
        const static std::string get            = "GET";
        const static std::string head           = "HEAD";
        const static std::string put            = "PUT";
        const static std::string delete_http    = "DELETE";
        const static std::string options        = "OPTIONS";
        const static std::string patch          = "PATCH";

        enum http_err {
            error_hook_ip = 0x31
        };
   }
}

#endif //NETFRAMEWORK_CORE_H

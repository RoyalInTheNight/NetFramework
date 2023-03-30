// Nelya commit
#ifndef NETFRAMEWORK_INET_H
#define NETFRAMEWORK_INET_H

#ifdef WIN64 // Windows
#import <WinSock2.h>

#else // Linux
#import <sys/socket.h>
#import <arpa/inet.h>
#import <netinet/in.h>

#endif

#import <iostream>
#import "../Core.h"

class ISocket {
private:
    struct sin_addr {
        core::uint32_t S_addr;
    };

    typedef struct sock_in {
        sin_addr            S_un;
        core::uint16_t  sin_port;
        core::int32_t sin_family;
        core::word   sin_zero[8];
    } pkt_t, *_pkt_t;

    typedef struct sock {
        core::uint8_t    sa_len;
        core::uint8_t sa_family;
        core::word  sa_data[14];
    } _raw_pkt_t, *__raw_pkt_t;

    typedef struct net_conf {
        std::vector<SOCKET> socks;
        std::vector<_pkt_t> headr;
        std::vector<core::word>
                      data_buffer;

        std::vector<core::int32_t>
                     error_buffer;
    } pkt_conf_t, *_pkt_conf_t;

    _pkt_conf_t              conf;

public:
    #ifdef WIN64
        typedef SOCKET            SOCKET;
        typedef core::int32_t *socklen_t;
    #else
        typedef core::uint64_t    SOCKET;
        typedef socklen_t      socklen_t;
    #endif // WIN64

    struct user_settings {
        std::string  ip_addr;
        core::uint16_t  port;

        std::string l4_proto;

        std::vector<std::string>
                   log_cache;
    };

    ISocket(const ISocket&);


    ~ISocket(); //closesocket
};

#endif //NETFRAMEWORK_INET_H

// end Nelya commit

// Nelya commit
#ifndef NETFRAMEWORK_INET_H
#define NETFRAMEWORK_INET_H

#ifdef WIN64 // Windows
#  import <WinSock2.h>
#  import <ws2tcpip.h>
#else // Linux
#  import <sys/socket.h>
#  import <arpa/inet.h>
#  import <netinet/in.h>
#endif // WIN64
#  import <iostream>
#  import <vector>
#  import <thread>
#  import "../Core.h"

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

    #ifdef WIN64
        typedef SOCKET            SOCKET;
        typedef core::int32_t  socklen_t;
    #else
        typedef core::int64_t     SOCKET;
        typedef socklen_t      socklen_t;
    #endif // WIN64

    std::string &_inet_ntoa(sin_addr);

    core::empty_type _bind(core::int32_t);
    core::empty_type _connect();
    core::empty_type _send(std::string &, core::int32_t);
    core::empty_type _recv(core::net::winsock_buffer_type, std::string::size_type, core::int32_t);
    SOCKET           _accept();

public:
    struct user_settings {
        std::string    ip_addr;
        core::uint16_t    port;

        std::string   l4_proto;
        std::string cache_file;

        std::vector<std::string>
                     log_cache;
    };

    user_settings *settings;

    ISocket(const ISocket&);
    ISocket(const std::string&, core::uint16_t, const std::string&, const std::string&);

    core::empty_type ConnectTCP();
    core::empty_type ListenConnect();

    core::empty_type Send(std::string &);
    core::empty_type Recv(std::vector<core::word> *);

    ~ISocket(); //closesocket
};

#endif //NETFRAMEWORK_INET_H

// end Nelya commit

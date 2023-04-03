// Nelya commit
#ifndef NETFRAMEWORK_INET_H
#define NETFRAMEWORK_INET_H

#ifdef WIN64 // Windows
#  include <WinSock2.h>
#  include <ws2tcpip.h>
#else // Linux
#  include <sys/socket.h>
#  include <arpa/inet.h>
#  include <netinet/in.h>
#endif // WIN64
#  include <iostream>
#  include <vector>
#  include <thread>
#  include "../Core.h"

class ISocket {
private:
    #ifdef WIN64 // замена типов данных для кросплатформенности
        typedef SOCKET            SOCKET;
        typedef core::int32_t  socklen_t;
    #else
        typedef core::int32_t     SOCKET;
        typedef socklen_t      socklen_t;
    #endif // WIN64

    struct sin_addr { // аналог in_addr, сюда записывается ip адресс
        core::uint32_t S_addr;
    };

    typedef struct sock_in { // аналог sockaddr_in
        sin_addr             S_un;
        core::uint16_t   sin_port;
        core::int16_t  sin_family;
        core::word    sin_zero[8];
    } pkt_t, *_pkt_t; // замена типов данных

    typedef struct sock { // аналог sockaddr
        core::uint16_t sa_family;
        core::word   sa_data[14];
    } _raw_pkt_t, *__raw_pkt_t; // замена типов данных

    typedef struct net_conf {
        std::vector<SOCKET> socks;
        std::vector<_pkt_t> headr;
        std::vector<core::word>
                      data_buffer;

        core::int32_t size_headr;

        std::vector<core::int32_t>
                     error_buffer;

        std::vector<std::string>
           exception_error_buffer;
    } pkt_conf_t, *_pkt_conf_t; // структура для надстройки функций начиная с 59 по 63 строку

    _pkt_conf_t              conf;

    std::string _inet_ntoa(sin_addr); // перевод ip адреса из числа в строку

    core::empty_type _bind();
    core::empty_type _connect();
    core::empty_type _send(std::string &, core::int32_t);
    core::empty_type _send(std::vector<std::string> &, core::int32_t);
    core::empty_type _recv(core::net::winsock_buffer_t, core::net::size_winsock_buffer_t, core::int32_t);
    SOCKET           _accept(core::int32_t);

public:
    struct user_settings {
        std::string    ip_addr;
        core::uint16_t    port;

        std::string   l4_proto;
        std::string cache_file;

        std::vector<std::string>
                     log_cache; // массив, который будет кэшироваться в tmp папке
    }; // настройки пользователя

    user_settings *settings;

    ISocket(const ISocket&);
    ISocket(const std::string&, core::uint16_t, const std::string&, const std::string&);

    // основные методы для работы с упрощенными сокетами

    core::empty_type ConnectTCP();
    core::empty_type ListenConnect();

    core::empty_type Send(std::string &);
    core::empty_type Recv(std::vector<core::word> *);

    core::empty_type start();

    ~ISocket(); //closesocket
};

#endif //NETFRAMEWORK_INET_H

// end Nelya commit

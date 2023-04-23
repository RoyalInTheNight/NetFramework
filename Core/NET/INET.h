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
#  import <unistd.h>
# import "../Core.h"
# import "../ISPtr.h"
//# import "../BLOB/IBLOB.h"


class ISocket {
protected:
    #ifdef WIN64 // замена типов данных для кросплатформенности
        typedef SOCKET            SOCKET;
        typedef core::int32_t  socklen_t;
    #else
        typedef core::int32_t     SOCKET;
        typedef socklen_t      socklen_t;
    #endif // WIN64

    struct sin_addr { // аналог in_addr, сюда записывается ip адресс
        union {
            struct { u_char  s_b1, s_b2, s_b3, s_b4; } S_un_b;
            struct { u_short s_w1, s_w2; } S_un_w;
            core::uint32_t S_addr;
        } S_un;
    };

    struct user_settings {
        std::string    ip_addr;
        core::uint16_t    port;

        std::string   l4_proto;
        std::string cache_file;

        std::vector<std::string>
                log_cache; // массив, который будет кэшироваться в tmp папке
    }; // настройки пользователя

    ISPtr<user_settings> settings;

    /*typedef struct sock_in { // аналог sockaddr_in
        sin_addr         sin_addr;
        core::uint16_t   sin_port;
        core::int16_t  sin_family;
        core::word    sin_zero[8];
    } pkt_t, *_pkt_t; // замена типов данных

    typedef struct sock { // аналог sockaddr
        core::uint16_t sa_family;
        core::word   sa_data[14];
    } _raw_pkt_t, *__raw_pkt_t; */ // замена типов данных

    typedef sockaddr_in pkt_t, *_pkt_t;

    typedef struct net_conf {
        std::vector<SOCKET> socks;
        std::vector<_pkt_t> headr;
        std::vector<core::word>
                      data_buffer;

        ISocket::socklen_t
                       size_headr; //

        std::vector<core::int32_t>
                     error_buffer;

        std::vector<std::string>
           exception_error_buffer;
    } pkt_conf_t, *_pkt_conf_t; // структура для надстройки функций начиная с 59 по 63 строку

    ISPtr<pkt_conf_t> conf;

    core::empty_type _bind();
    core::empty_type _connect();
    core::empty_type _send(std::string &, core::int32_t);
    core::empty_type _send(std::vector<std::string> &, core::int32_t); // multi thread send
    core::empty_type _recv(core::net::winsock_buffer_t, core::int32_t);
    ISocket::SOCKET  _accept(core::int32_t); // bug

    virtual ~ISocket(); //closesocket
};

class INetWork : public ISocket {
public:
    std::string _inet_ntoa(in_addr); // перевод ip адреса из числа в строку

    INetWork(const INetWork&);
    INetWork(const std::string&, core::uint16_t, const std::string&, const std::string&);

    // основные методы для работы с упрощенными сокетами

    core::empty_type ConnectTCP(); // подключение только с помощью tcp
    core::empty_type ListenConnect(); // принятие соединения
    core::empty_type Send(std::string &, core::int32_t); // отправка пакета tcp либо udp
    core::empty_type Send(std::vector<std::string> &, core::int32_t); // многопоточная отправка нескольких сообщений через tcp либо udp
    core::empty_type Recv(std::vector<core::word> *, core::int32_t); // получить по tcp либо udp
    core::empty_type start(); // test method

};

class INetErrors : public ISocket {
public:
    std::vector<core::int32_t> GetLastErrors(); // получить последние ошибки
    core::empty_type OutputLastErrors(); // вывести ошибки или же можно реализовать exceptions
};

#endif //NETFRAMEWORK_INET_H

// end Nelya commit

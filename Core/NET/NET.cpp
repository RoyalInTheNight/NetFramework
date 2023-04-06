#include "INET.h"

ISocket::ISocket(const ISocket& copy_settings) {
    *this = copy_settings;
}

ISocket::ISocket(const std::string &ip_address, core::uint16_t port, const std::string &transport_protocol, const std::string &cache_filename) {
    settings[ptr::user_type].ip_addr    = ip_address;
    settings[ptr::user_type].port       = port;
    settings[ptr::user_type].l4_proto   = transport_protocol;
    settings[ptr::user_type].cache_file = cache_filename;

    conf[ptr::user_type].socks.resize(3);
    conf[ptr::user_type].headr.resize(3);

    for (core::int32_t i = 0; i < 3; i++)
        conf[ptr::user_type].headr.at(i) = new pkt_t();

    conf[ptr::user_type].size_headr = sizeof(pkt_t);

    #ifdef WIN64
        WSADATA wsa;

        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            conf[ptr::user_type].error_buffer.push_back(WSAGetLastError());

            static core::word __thread buffer[128];

            snprintf(buffer, sizeof(buffer), "error create wsadata: %d\n",
                     conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));

            conf[ptr::user_type].exception_error_buffer.push_back((std::string)buffer);
        }
    #endif
}

std::string ISocket::_inet_ntoa(in_addr in) {
    static core::word __thread buffer[18];
    core::fs::fs_path bytes = (core::fs::fs_path)&in;

    snprintf(buffer, sizeof(buffer), "%d.%d.%d.%d", *bytes, *(bytes + 1), *(bytes + 2), *(bytes + 3));

    std::string return_buffer = buffer;

    return return_buffer;
}

core::empty_type ISocket::_connect() {
    #ifdef WIN64
        conf[ptr::user_type].headr.at(core::net::isocket::connect)->sin_addr.S_un.S_addr = inet_addr(settings[ptr::user_type].ip_addr.c_str());
    #else
        conf[ptr::user_type].headr.at(core::net::isocket::connect)->sin_addr.s_addr = inet_addr(settings[ptr::user_type].ip_addr.c_str());
    #endif

    conf[ptr::user_type].headr.at(core::net::isocket::connect)->sin_port             = htons(settings[ptr::user_type].port);
    conf[ptr::user_type].headr.at(core::net::isocket::connect)->sin_family           = AF_INET;

    if (settings[ptr::user_type].l4_proto == core::net::tcp) {
        conf[ptr::user_type].socks.at(core::net::isocket::connect) = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        #ifdef WIN64
            if (conf[ptr::user_type].socks.at(core::net::isocket::connect) == INVALID_SOCKET) {
                conf[ptr::user_type].error_buffer.push_back(WSAGetLastError());

                static core::word __thread buffer[128];

                snprintf(buffer, sizeof(buffer), "error create socket: %d\n",
                         conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));

                conf[ptr::user_type].exception_error_buffer.push_back((std::string)buffer);
            }
        #else
            if (conf[ptr::user_type].socks.at(core::net::isocket::connect) != 0) {
                conf[ptr::user_type].error_buffer.push_back(core::net::linux_errs::socket_err);

                static core::word __thread buffer[128];

                snprintf(buffer, sizeof(buffer), "error create socket: %d\n",
                         conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));

                conf[ptr::user_type].exception_error_buffer.push_back((std::string)buffer);
            }
        #endif // WIN64 // //

        #ifdef WIN64
            if (connect(conf[ptr::user_type].socks.at(core::net::isocket::connect),
                        (sockaddr *)conf[ptr::user_type].headr.at(core::net::isocket::connect),
                        conf[ptr::user_type].size_headr) == SOCKET_ERROR) {
                conf[ptr::user_type].error_buffer.push_back(WSAGetLastError());

                static core::word __thread buffer[128];

                snprintf(buffer, sizeof(buffer), "error connection: %d\n", conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));

                conf[ptr::user_type].exception_error_buffer.push_back((std::string)buffer);
            }
        #else
            if (connect(conf[ptr::user_type].socks.at(core::net::isocket::connect),
                        (sockaddr *)conf[ptr::user_type].headr.at(core::net::isocket::connect),
                        conf[ptr::user_type].size_headr) == core::net::linux_errs::connect_err) {
                conf[ptr::user_type].error_buffer.push_back(core::net::linux_errs::connect_err);

                static core::word __thread buffer[128];

                snprintf(buffer, sizeof(buffer), "error connection: %d\n",
                         conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));

                conf[ptr::user_type].exception_error_buffer.push_back((std::string)buffer);
            }
        #endif // WIN64
    }

    else if (settings[ptr::user_type].l4_proto == core::net::udp) {
        conf[ptr::user_type].socks.at(core::net::isocket::connect) = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        #ifdef WIN64
            if (conf[ptr::user_type].socks.at(core::net::isocket::connect) == INVALID_SOCKET) {
                conf[ptr::user_type].error_buffer.push_back(WSAGetLastError());

                static core::word __thread buffer[128];

                snprintf(buffer, sizeof(buffer), "error create socket: %d\n",
                         conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));

                conf[ptr::user_type].exception_error_buffer.push_back((std::string)buffer);
            }
        #else
            if (conf[ptr::user_type].socks.at(core::net::isocket::connect) == core::net::linux_errs::socket_err) {
                conf[ptr::user_type].error_buffer.push_back(core::net::linux_errs::socket_err);

                static core::word __thread buffer[128];

                snprintf(buffer, sizeof(buffer), "error create socket: %d\n",
                         conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));

                conf[ptr::user_type].exception_error_buffer.push_back((std::string)buffer);
            }
        #endif // WIN64
    }
}

core::empty_type ISocket::_bind() {
    #ifdef WIN64
        conf[ptr::user_type].headr.at(core::net::isocket::connect)->sin_addr.S_un.S_addr = inet_addr(settings[ptr::user_type].ip_addr.c_str());
    #else
        conf[ptr::user_type].headr.at(core::net::isocket::connect)->sin_addr.s_addr = inet_addr(settings[ptr::user_type].ip_addr.c_str());
    #endif

    conf[ptr::user_type].headr.at(core::net::isocket::bind)->sin_port             = htons(settings[ptr::user_type].port);
    conf[ptr::user_type].headr.at(core::net::isocket::bind)->sin_family           = AF_INET;

    if(settings[ptr::user_type].l4_proto == core::net::tcp)
        conf[ptr::user_type].socks.at(core::net::isocket::bind) = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(settings[ptr::user_type].l4_proto == core::net::udp)
        conf[ptr::user_type].socks.at(core::net::isocket::bind) = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    #ifdef WIN64
    if (conf[ptr::user_type].socks.at(core::net::isocket::bind) == INVALID_SOCKET) {
        conf[ptr::user_type].error_buffer.push_back(WSAGetLastError());

        static core::word __thread buffer[128];

        snprintf(buffer, sizeof(buffer), "error create socket: %d\n",
                 conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));

        conf[ptr::user_type].exception_error_buffer.push_back((std::string)buffer);
    }
    #else
        if (conf[ptr::user_type].socks.at(core::net::isocket::bind) != 0) {
            conf[ptr::user_type].error_buffer.push_back(core::net::linux_errs::socket_err);

            static core::word __thread buffer[128];

            snprintf(buffer, sizeof(buffer), "error create socket: %d\n",
                     conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));

            conf[ptr::user_type].exception_error_buffer.push_back((std::string)buffer);
        }
    #endif

    #ifdef WIN64
        if(::bind(conf[ptr::user_type].socks.at(core::net::isocket::bind),
                (sockaddr *)conf[ptr::user_type].headr.at(core::net::isocket::bind),
                  conf[ptr::user_type].size_headr) != 0) {
            conf[ptr::user_type].error_buffer.push_back(WSAGetLastError());

            static core::word __thread buffer[128];

            snprintf(buffer, sizeof(buffer), "error bind: %d\n",
                     conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));

            conf[ptr::user_type].exception_error_buffer.push_back((std::string)buffer);
        }
    #else
        if(::bind(conf[ptr::user_type].socks.at(core::net::isocket::bind),
                  (sockaddr *)conf[ptr::user_type].headr.at(core::net::isocket::bind),
                  conf[ptr::user_type].size_headr) != 0) {
            conf[ptr::user_type].error_buffer.push_back(core::net::linux_errs::bind_err);

            static core::word __thread buffer[128];
            snprintf(buffer, sizeof(buffer), "error bind: %d\n",
                     conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));

            conf[ptr::user_type].exception_error_buffer.push_back((std::string)buffer);
        }
    #endif
}

core::empty_type ISocket::_send(std::string &message, core::int32_t flag) {
    if(settings[ptr::user_type].l4_proto == core::net::tcp) {
        if(send(conf[ptr::user_type].socks.at(flag), (core::net::winsock_buffer_t)message.c_str(), (core::int32_t)message.size(), flag) != 0) {

        #ifdef WIN64
            conf[ptr::user_type].error_buffer.push_back(WSAGetLastError());
        #else
            conf[ptr::user_type].error_buffer.push_back(core::net::linux_errs::send_err);
        #endif

            static core::word __thread buffer[128];
            snprintf(buffer, sizeof(buffer), "error send message: %d\n", conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));
            conf[ptr::user_type].exception_error_buffer.push_back((std::string)buffer);
        }
    }

    else if(settings[ptr::user_type].l4_proto == core::net::udp) {
        if(sendto(conf[ptr::user_type].socks.at(flag), (core::net::winsock_buffer_t)message.c_str(), (core::int32_t)message.size(), flag,
                  (sockaddr *)conf[ptr::user_type].headr.at(core::net::isocket::connect),
                  conf[ptr::user_type].size_headr) != 0) {

            #ifdef WIN64
                conf[ptr::user_type].error_buffer.push_back(WSAGetLastError());
            #else
                conf[ptr::user_type].error_buffer.push_back(core::net::linux_errs::sendto_err);
            #endif

            static core::word __thread buffer[128];
            snprintf(buffer, sizeof(buffer), "error send message: %d\n",
                     conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));
            conf[ptr::user_type].exception_error_buffer.push_back((std::string) buffer);
        }
    }
}

core::empty_type ISocket::_send(std::vector<std::string> &messages, core::int32_t flag) { // bug segfault

    int mn1 = 0, mn2 = 10;
    for(int i = 0; i < messages.size() % 10; i++) {
        int mn3 = 0;
        std::vector<std::string> *stream = new std::vector<std::string>();
        for(int y = mn1; y < mn2; y++) {
            stream->at(mn3) = messages[y];
            mn3++;
        }

        mn1 += 10; mn2 += 10;

        std::thread([&]() {
            if(settings[ptr::user_type].l4_proto == core::net::tcp) {
                for(std::string msg : *stream)
                    if(send(conf[ptr::user_type].socks.at(flag), (core::net::winsock_buffer_t)msg.c_str(), msg.size(), flag) != 0) {
                        #ifdef WIN64
                            conf[ptr::user_type].error_buffer.push_back(WSAGetLastError());
                        #else
                            conf[ptr::user_type].error_buffer.push_back(core::net::linux_errs::send_err);
                        #endif

                        static core::word __thread buffer[128];
                        snprintf(buffer, sizeof(buffer), "error send messages: %d\n",
                                 conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));
                        conf[ptr::user_type].exception_error_buffer.push_back((std::string)buffer);
                    }
            }
            else if(settings[ptr::user_type].l4_proto == core::net::udp) {
                for(std::string msg : *stream)
                    if(sendto(conf[ptr::user_type].socks.at(flag), (core::net::winsock_buffer_t)msg.c_str(), msg.size(), flag,
                              (sockaddr *)conf[ptr::user_type].headr.at(core::net::isocket::connect),
                              conf[ptr::user_type].size_headr) != 0) {
                        #ifdef WIN64
                            conf[ptr::user_type].error_buffer.push_back(WSAGetLastError());
                        #else
                            conf[ptr::user_type].error_buffer.push_back(core::net::linux_errs::sendto_err);
                        #endif

                        static core::word __thread buffer[128];
                        snprintf(buffer, sizeof(buffer), "error send messages: %d\n",
                                 conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));
                        conf[ptr::user_type].exception_error_buffer.push_back((std::string) buffer);
                    }
                }
        }).join();
    }
    for(int i = (messages.size()%10*10); i < messages.size(); i++)
        if(settings[ptr::user_type].l4_proto == core::net::tcp) {
                if(send(conf[ptr::user_type].socks.at(flag), (core::net::winsock_buffer_t)messages[i].c_str(), messages[i].size(), flag) != 0) {

                    #ifdef WIN64
                        conf[ptr::user_type].error_buffer.push_back(WSAGetLastError());
                    #else
                        conf[ptr::user_type].error_buffer.push_back(core::net::linux_errs::send_err);
                    #endif

                    static core::word __thread buffer[128];
                    snprintf(buffer, sizeof(buffer), "error send messages: %d\n", conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));
                    conf[ptr::user_type].exception_error_buffer.push_back((std::string)buffer);
                }
        }

        else if(settings[ptr::user_type].l4_proto == core::net::udp) {
                if(sendto(conf[ptr::user_type].socks.at(flag), (core::net::winsock_buffer_t)messages[i].c_str(), messages[i].size(), flag,
                          (sockaddr *)conf[ptr::user_type].headr.at(core::net::isocket::connect),
                          conf[ptr::user_type].size_headr) != 0) {

                    #ifdef WIN64
                        conf[ptr::user_type].error_buffer.push_back(WSAGetLastError());
                    #else
                        conf[ptr::user_type].error_buffer.push_back(core::net::linux_errs::sendto_err);
                    #endif

                    static core::word __thread buffer[128];
                    snprintf(buffer, sizeof(buffer), "error send messages: %d\n",
                             conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));
                    conf[ptr::user_type].exception_error_buffer.push_back((std::string) buffer);
                }
        }
}

ISocket::SOCKET ISocket::_accept(core::int32_t queue) {
    if (::listen(conf[ptr::user_type].socks.at(core::net::isocket::bind), queue) != 0) {
        #ifdef WIN64
            conf[ptr::user_type].error_buffer.push_back(WSAGetLastError());
        #else
            conf[ptr::user_type].error_buffer.push_back(core::net::linux_errs::listen_err);
        #endif
    }

    #ifdef WIN64
        if((conf[ptr::user_type].socks.at(core::net::isocket::accept) = accept(conf[ptr::user_type].socks.at(core::net::isocket::bind),
                                                                   (sockaddr*)conf[ptr::user_type].headr.at(core::net::isocket::accept),
                                                                   &conf[ptr::user_type].size_headr)) == INVALID_SOCKET) {
            conf[ptr::user_type].error_buffer.push_back(WSAGetLastError());

            static core::word __thread buffer[128];
            snprintf(buffer, sizeof(buffer), "error accept socket: %d\n",
                     conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));
            conf[ptr::user_type].exception_error_buffer.push_back((std::string)buffer);

            return INVALID_SOCKET;
        }
    #else //
        if((conf[ptr::user_type].socks.at(core::net::isocket::accept) = accept(conf[ptr::user_type].socks.at(core::net::isocket::bind),
                                                                          (sockaddr*)conf[ptr::user_type].headr.at(core::net::isocket::accept),
                                                                          &conf[ptr::user_type].size_headr)) < 0) {
            conf[ptr::user_type].error_buffer.push_back(core::net::linux_errs::accept_err);
            static core::word __thread buffer[128];
            snprintf(buffer, sizeof(buffer), "error accept socket: %d\n",
                     conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));
            conf[ptr::user_type].exception_error_buffer.push_back((std::string)buffer);
        }
    #endif

    return conf[ptr::user_type].socks.at(core::net::isocket::accept);
}

core::empty_type ISocket::_recv(core::net::winsock_buffer_t buffer, core::int32_t flag) {
    if(recv(conf[ptr::user_type].socks.at(flag), buffer, (core::int32_t)SO_SNDBUF, 0) <= 0) {
        #ifdef WIN64
            conf[ptr::user_type].error_buffer.push_back(WSAGetLastError());
        #else
            conf[ptr::user_type].error_buffer.push_back(core::net::linux_errs::recv_err);
        #endif

        static core::word __thread buffer[128];
        snprintf(buffer, sizeof(buffer), "error get message: %d\n",
                 conf[ptr::user_type].error_buffer.at(conf[ptr::user_type].error_buffer.size() - 1));
        conf[ptr::user_type].exception_error_buffer.push_back((std::string)buffer);
    }
}

std::vector<core::int32_t> ISocket::GetLastErrors() {
    return conf[ptr::user_type].error_buffer;
}

core::empty_type ISocket::OutputLastErrors() {
    for (std::string msg_err : conf[ptr::user_type].exception_error_buffer)
        std::cout << msg_err << std::endl;
}

core::empty_type ISocket::ConnectTCP() {
    if(settings[ptr::user_type].l4_proto == core::net::tcp) {
        this->_connect();
    }
}

core::empty_type ISocket::ListenConnect() {
    _bind();
    if(settings[ptr::user_type].l4_proto == core::net::tcp)
        _accept(SOMAXCONN);
}

core::empty_type ISocket::Send(std::string &message, core::int32_t flag) {
    this -> _send(message, flag);
}
core::empty_type ISocket::Send(std::vector<std::string> &messages, core::int32_t flag) {
    this ->_send(messages, flag);
}

core::empty_type ISocket::Recv(std::vector<core::word> *buffer, core::int32_t flag) {
    this -> _recv((core::net::winsock_buffer_t)buffer, flag);
}

ISocket::~ISocket() {
    for (SOCKET fd : conf[ptr::user_type].socks) {
        #ifdef WIN64
            closesocket(fd);
        #else
            close(fd);
        #endif // WIN64
    }
}
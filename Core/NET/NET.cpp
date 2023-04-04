#include "INET.h"

ISocket::ISocket(const ISocket& copy_settings) {
    *this = copy_settings;
}

ISocket::ISocket(const std::string &ip_address, core::uint16_t port, const std::string &transport_protocol, const std::string &cache_filename) {
    settings = new user_settings();
    conf     = new pkt_conf_t();

    settings->ip_addr    = ip_address;
    settings->port       = port;
    settings->l4_proto   = transport_protocol;
    settings->cache_file = cache_filename;

    conf->socks.resize(3);
    conf->headr.resize(3);

    for (core::int32_t i = 0; i < 3; i++)
        conf->headr.at(i) = new pkt_t();

    conf->size_headr = sizeof(pkt_t);

    #ifdef WIN64
        WSADATA wsa;

        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            conf->error_buffer.push_back(WSAGetLastError());

            static core::word __thread buffer[128];

            snprintf(buffer, sizeof(buffer), "error create wsadata: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

            conf->exception_error_buffer.push_back((std::string)buffer);
        }
    #endif
}

std::string ISocket::_inet_ntoa(sin_addr in) {
    static core::word __thread buffer[18];
    core::fs::fs_path bytes = (core::fs::fs_path)&in;

    snprintf(buffer, sizeof(buffer), "%d.%d.%d.%d", *bytes, *(bytes + 1), *(bytes + 2), *(bytes + 3));

    std::string return_buffer = buffer;

    return return_buffer;
}

core::empty_type ISocket::_connect() {
    conf->headr.at(core::net::isocket::connect)->sin_addr.S_un.S_addr = inet_addr(settings->ip_addr.c_str());
    conf->headr.at(core::net::isocket::connect)->sin_port             = htons(settings->port);
    conf->headr.at(core::net::isocket::connect)->sin_family           = AF_INET;

    if (settings->l4_proto == core::net::tcp) {
        conf->socks.at(core::net::isocket::connect) = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        #ifdef WIN64
            if (conf->socks.at(core::net::isocket::connect) == INVALID_SOCKET) {
                conf->error_buffer.push_back(WSAGetLastError());

                static core::word __thread buffer[128];

                snprintf(buffer, sizeof(buffer), "error create socket: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

                conf->exception_error_buffer.push_back((std::string)buffer);
            }
        #else
            if (conf->socks.at(core::net::net_treatment_part::connect) != 0) {
                conf->error_buffer.push_back(core::net::linux_errs::socket_err);

                static core::word __thread buffer[128];

                snprintf(buffer, sizeof(buffer), "error create socket: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

                conf->exception_error_buffer.push_back((std::string)buffer);
            }
        #endif // WIN64 // //

        #ifdef WIN64
            if (connect(conf->socks.at(core::net::isocket::connect),
                        (sockaddr *)conf->headr.at(core::net::isocket::connect),
                        conf->size_headr) == SOCKET_ERROR) {
                conf->error_buffer.push_back(WSAGetLastError());

                static core::word __thread buffer[128];

                snprintf(buffer, sizeof(buffer), "error connection: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

                conf->exception_error_buffer.push_back((std::string)buffer);
            }
        #else
            if (connect(conf->socks.at(core::net::net_treatment_part::connect),
                        (sockaddr *)conf->headr.at(core::net::net_treatment_part::connect),
                        conf->size_headr) == core::net::SOCKET_ERROR) {
                conf->error_buffer.push_back(core::net::SOCKET_ERROR);

                static core::word __thread buffer[128];

                snprintf(buffer, sizeof(buffer), "error connection: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

                conf->exception_error_buffer.push_back((std::string)buffer);
            }
        #endif // WIN64
    }

    else if (settings->l4_proto == core::net::udp) {
        conf->socks.at(core::net::isocket::connect) = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        #ifdef WIN64
            if (conf->socks.at(core::net::isocket::connect) == INVALID_SOCKET) {
                conf->error_buffer.push_back(WSAGetLastError());

                static core::word __thread buffer[128];

                snprintf(buffer, sizeof(buffer), "error create socket: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

                conf->exception_error_buffer.push_back((std::string)buffer);
            }
        #else
            if (conf->socks.at(core::net::net_treatment_part::connect) == core::net::linux_errs::socket_err) {
                conf->error_buffer.push_back(core::net::linux_errs::socket_err);

                static core::word __thread buffer[128];

                snprintf(buffer, sizeof(buffer), "error create socket: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

                conf->exception_error_buffer.push_back((std::string)buffer);
            }
        #endif // WIN64
    }
}

core::empty_type ISocket::_bind() {
    conf->headr.at(core::net::isocket::bind)->sin_addr.S_un.S_addr = inet_addr(settings->ip_addr.c_str());
    conf->headr.at(core::net::isocket::bind)->sin_port             = htons(settings->port);
    conf->headr.at(core::net::isocket::bind)->sin_family           = AF_INET;

    if(settings->l4_proto == core::net::tcp)
        conf->socks.at(core::net::isocket::bind) = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(settings->l4_proto == core::net::udp)
        conf->socks.at(core::net::isocket::bind) = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    #ifdef WIN64
    if (conf->socks.at(core::net::isocket::bind) == INVALID_SOCKET) {
        conf->error_buffer.push_back(WSAGetLastError());

        static core::word __thread buffer[128];

        snprintf(buffer, sizeof(buffer), "error create socket: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

        conf->exception_error_buffer.push_back((std::string)buffer);
    }
    #else
    if (conf->socks.at(core::net::net_treatment_part::bind) != 0) {
            conf->error_buffer.push_back(core::net::linux_errs::socket_err);

            static core::word __thread buffer[128];

            snprintf(buffer, sizeof(buffer), "error create socket: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

            conf->exception_error_buffer.push_back((std::string)buffer);
        }
    #endif

    #ifdef WIN64
        if(::bind(conf->socks.at(core::net::isocket::bind),
                (sockaddr *)conf->headr.at(core::net::isocket::bind),
                conf->size_headr) != 0) {
            conf->error_buffer.push_back(WSAGetLastError());

            static core::word __thread buffer[128];

            snprintf(buffer, sizeof(buffer), "error bind: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

            conf->exception_error_buffer.push_back((std::string)buffer);
        }
    #else
    if(::bind(conf->socks.at(core::net::net_treatment_part::bind),
            (sockaddr *)conf->headr.at(core::net::net_treatment_part::bind),
            conf->size_headr) != 0) {
        conf->error_buffer.push_back(core::net::linux_errs::bind_err));

        static core::word __thread buffer[128];

        snprintf(buffer, sizeof(buffer), "error bind: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

        conf->exception_error_buffer.push_back((std::string)buffer);
    }
    #endif
}

core::empty_type ISocket::_send(std::string &message, core::int32_t flag) {
    if(settings->l4_proto == core::net::tcp) {
        if(send(conf->socks.at(flag), (core::net::winsock_buffer_t)message.c_str(), (core::int32_t)message.size(), flag) == SOCKET_ERROR) {

        #ifdef WIN64
            conf->error_buffer.push_back(WSAGetLastError());
        #else
            conf->error_buffer.push_back(core::net::linux_errs::send_err);
        #endif

            static core::word __thread buffer[128];
            snprintf(buffer, sizeof(buffer), "error send message: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));
            conf->exception_error_buffer.push_back((std::string)buffer);
        }
    }
    else if(settings->l4_proto == core::net::udp) {
        if(sendto(conf->socks.at(flag), (core::net::winsock_buffer_t)message.c_str(), (core::int32_t)message.size(), flag,
                  (sockaddr *)conf->headr.at(core::net::isocket::connect),
                  conf->size_headr) == INVALID_SOCKET) {

            #ifdef WIN64
                conf->error_buffer.push_back(WSAGetLastError());
            #else
                conf->error_buffer.push_back(core::net::linux_errs::sendto_err);
            #endif

            static core::word __thread buffer[128];
            snprintf(buffer, sizeof(buffer), "error send message: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));
            conf->exception_error_buffer.push_back((std::string) buffer);
        }
    }
}

core::empty_type ISocket::_send(std::vector<std::string> &messages, core::int32_t flag) { // bug segfault

    int mn1 = 0, mn2 = 10;

    for(int i = 0; i < messages.size() % 10; i++) {
        int mn3 = 0;
        std::vector<std::string> stream;

        for(int y = mn1; y < mn2; y++) {
            stream.at(mn3) = messages[y];
            mn3++;
        }

        mn1 += 10; mn2 += 10;

        std::thread([&]() {
            if(settings->l4_proto == core::net::tcp) {
                for(std::string msg : stream)
                    if(send(conf->socks.at(flag), (core::net::winsock_buffer_t)msg.c_str(), msg.size(), flag) == SOCKET_ERROR) {
                        conf->error_buffer.push_back(WSAGetLastError());
                        static core::word __thread buffer[128];
                        snprintf(buffer, sizeof(buffer), "error send messages: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));
                        conf->exception_error_buffer.push_back((std::string)buffer);
                    }
            }
            else if(settings->l4_proto == core::net::udp) {
                for(std::string msg : stream)
                    if(sendto(conf->socks.at(flag), (core::net::winsock_buffer_t)msg.c_str(), msg.size(), flag,
                              (sockaddr *)conf->headr.at(core::net::isocket::connect),
                              sizeof(conf->headr.at(core::net::isocket::connect))) == INVALID_SOCKET) {
                        conf->error_buffer.push_back(WSAGetLastError());
                        static core::word __thread buffer[128];
                        snprintf(buffer, sizeof(buffer), "error send messages: %d\n",
                                 conf->error_buffer.at(conf->error_buffer.size() - 1));
                        conf->exception_error_buffer.push_back((std::string) buffer);
                    }
                }
        }).join();
    }
    core::int32_t cont = messages.size()%10*10;
    for(int i = cont; i < messages.size(); i++)
        if(settings->l4_proto == core::net::tcp) {
                if(send(conf->socks.at(flag), (core::net::winsock_buffer_t)messages[i].c_str(), messages[i].size(), flag) == SOCKET_ERROR) {
                    conf->error_buffer.push_back(WSAGetLastError());
                    static core::word __thread buffer[128];
                    snprintf(buffer, sizeof(buffer), "error send messages: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));
                    conf->exception_error_buffer.push_back((std::string)buffer);
                }
        }
        else if(settings->l4_proto == core::net::udp) {
                if(sendto(conf->socks.at(flag), (core::net::winsock_buffer_t)messages[i].c_str(), messages[i].size(), flag,
                          (sockaddr *)conf->headr.at(core::net::isocket::connect),
                          conf->size_headr) == INVALID_SOCKET) {
                    conf->error_buffer.push_back(WSAGetLastError());
                    static core::word __thread buffer[128];
                    snprintf(buffer, sizeof(buffer), "error send messages: %d\n",
                             conf->error_buffer.at(conf->error_buffer.size() - 1));
                    conf->exception_error_buffer.push_back((std::string) buffer);
                }
            }
}

SOCKET ISocket::_accept(core::int32_t queue) {
    if (::listen(conf->socks.at(core::net::isocket::bind), queue) != 0) {
        #ifdef WIN64
            conf->error_buffer.push_back(WSAGetLastError());
        #else
            conf->error_buffer.push_back(core::net::linux_errs::listen_err);
        #endif
    }

    #ifdef WIN64
        if((conf->socks.at(core::net::isocket::accept) = accept(conf->socks.at(core::net::isocket::bind),
                                                                   (sockaddr*)conf->headr.at(core::net::isocket::accept),
                                                                   &conf->size_headr)) == INVALID_SOCKET) {
            conf->error_buffer.push_back(WSAGetLastError());

            static core::word __thread buffer[128];
            snprintf(buffer, sizeof(buffer), "error accept socket: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));
            conf->exception_error_buffer.push_back((std::string)buffer);

            return INVALID_SOCKET;
        }
    #else
        if((conf->socks.at(core::net::net_treatment_part::accept) = accept(conf->socks.at(core::net::net_treatment_part::bind),
                                                                          (sockaddr*)conf->headr.at(core::net::net_treatment_part::accept),
                                                                          &conf->size_headr)) < 0) {
            conf->error_buffer.push_back(core::net::linux_errs::accept_err);
            static core::word __thread buffer[128];
            snprintf(buffer, sizeof(buffer), "error accept socket: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));
            conf->exception_error_buffer.push_back((std::string)buffer);
        }
    #endif

    return conf->socks.at(core::net::isocket::accept);
}

core::empty_type ISocket::_recv(core::net::winsock_buffer_t buffer, core::net::size_winsock_buffer_t size_res, core::int32_t flag) {
    if(recv(conf->socks.at(flag), buffer, (core::int32_t)size_res, 0) <= 0) {
        #ifdef WIN64
            conf->error_buffer.push_back(WSAGetLastError());
        #else
            conf->error_buffer.push_back(core::net::linux_errs::recv_err);
        #endif

        static core::word __thread buffer[128];
        snprintf(buffer, sizeof(buffer), "error get message: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));
        conf->exception_error_buffer.push_back((std::string)buffer);
    }
}

std::vector<core::int32_t> ISocket::GetLastErrors() {
    return conf->error_buffer;
}

core::empty_type ISocket::OutputLastErrors() {
    for (std::string msg_err : conf->exception_error_buffer)
        std::cout << msg_err << std::endl;
}

core::empty_type ISocket::ConnectTCP() {
    if(settings->l4_proto == core::net::tcp) {
        this->_connect();
    }
}

ISocket::~ISocket() {
    for (SOCKET fd : conf->socks) {
        #ifdef WIN64
            closesocket(fd);
        #else
            close(fd);
        #endif // WIN64
    }

    delete(conf);
}
#import "INET.h"

ISocket::ISocket(const ISocket& copy_settings) {
    *this = copy_settings;
}

ISocket::ISocket(const std::string &ip_address, core::uint16_t port, const std::string &transport_protocol, const std::string &cache_filename) {
    settings = new user_settings();

    settings->ip_addr    = ip_address;
    settings->port       = port;
    settings->l4_proto   = transport_protocol;
    settings->cache_file = cache_filename;

    conf->socks.resize(3);
    conf->headr.resize(3);

    conf->size_headr = sizeof(pkt_t);
}

std::string& ISocket::_inet_ntoa(sin_addr in) {
    static core::word __thread buffer[18];
    core::fs::fs_path bytes = (core::fs::fs_path)&in;

    snprintf(buffer, sizeof(buffer), "%d.%d.%d.%d", *bytes, *(bytes + 1), *(bytes + 2), *(bytes + 3));

    std::string return_buffer = buffer;

    return (std::string &)return_buffer;
}

core::empty_type ISocket::_connect() {
    conf->headr.at(core::net::net_treatment_part::connect)->S_un.S_addr = inet_addr(settings->ip_addr.c_str());
    conf->headr.at(core::net::net_treatment_part::connect)->sin_port    = htons(settings->port);
    conf->headr.at(core::net::net_treatment_part::connect)->sin_family  = AF_INET;

    if (settings->l4_proto == core::net::tcp) {
        conf->socks.at(core::net::net_treatment_part::connect) = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        #ifdef WIN64
            if (conf->socks.at(core::net::net_treatment_part::connect) == INVALID_SOCKET) {
                conf->error_buffer.push_back(WSAGetLastError());

                static core::word __thread buffer[128];

                snprintf(buffer, sizeof(buffer), "error create socket: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

                conf->exception_error_buffer.push_back((std::string)buffer);
            }
        #else
            if (conf->socks.at(core::net::net_treatment_part::connect) == core::net::INVALID_SOCKET) {
                conf->error_buffer.push_back(core::net::INVALID_SOCKET);

                static core::word __thread buffer[128];

                snprintf(buffer, sizeof(buffer), "error create socket: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

                conf->exception_error_buffer.push_back((std::string)buffer);
            }
        #endif // WIN64

        #ifdef WIN64
            if (connect(conf->socks.at(core::net::net_treatment_part::connect),
                        (sockaddr *)conf->headr.at(core::net::net_treatment_part::connect),
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
        conf->socks.at(core::net::net_treatment_part::connect) = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        #ifdef WIN64
            if (conf->socks.at(core::net::net_treatment_part::connect) == INVALID_SOCKET) {
                conf->error_buffer.push_back(WSAGetLastError());

                static core::word __thread buffer[128];

                snprintf(buffer, sizeof(buffer), "error create socket: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

                conf->exception_error_buffer.push_back((std::string)buffer);
            }
        #else
            if (conf->socks.at(core::net::net_treatment_part::connect) == core::net::INVALID_SOCKET) {
                conf->error_buffer.push_back(core::net::INVALID_SOCKET);

                static core::word __thread buffer[128];

                snprintf(buffer, sizeof(buffer), "error create socket: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

                conf->exception_error_buffer.push_back((std::string)buffer);
            }
        #endif // WIN64
    }
}

core::empty_type ISocket::_bind() {
    conf->headr.at(core::net::net_treatment_part::bind)->S_un.S_addr = inet_addr(settings->ip_addr.c_str());
    conf->headr.at(core::net::net_treatment_part::bind)->sin_port    = htons(settings->port);
    conf->headr.at(core::net::net_treatment_part::bind)->sin_family  = AF_INET;

    if(settings->l4_proto == core::net::tcp)
        conf->socks.at(core::net::net_treatment_part::bind) = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(settings->l4_proto == core::net::udp)
        conf->socks.at(core::net::net_treatment_part::bind) = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    #ifdef WIN64
    if (conf->socks.at(core::net::net_treatment_part::bind) == INVALID_SOCKET) {
        conf->error_buffer.push_back(WSAGetLastError());

        static core::word __thread buffer[128];

        snprintf(buffer, sizeof(buffer), "error create socket: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

        conf->exception_error_buffer.push_back((std::string)buffer);
    }
    #else
    if (conf->socks.at(core::net::net_treatment_part::bind) == core::net::INVALID_SOCKET) {
            conf->error_buffer.push_back(core::net::INVALID_SOCKET);

            static core::word __thread buffer[128];

            snprintf(buffer, sizeof(buffer), "error create socket: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

            conf->exception_error_buffer.push_back((std::string)buffer);
        }
    #endif

    #ifdef WIN64
    if(bind(conf->socks.at(core::net::net_treatment_part::bind),
            (sockaddr *)conf->headr.at(core::net::net_treatment_part::bind),
            sizeof(*conf->headr.at(core::net::net_treatment_part::bind))) != 0) {
        conf->error_buffer.push_back(WSAGetLastError());

        static core::word __thread buffer[128];

        snprintf(buffer, sizeof(buffer), "error connection: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

        conf->exception_error_buffer.push_back((std::string)buffer);
    }
    #else
    if(bind(conf->socks.at(core::net::net_treatment_part::bind),
            (sockaddr *)conf->headr.at(core::net::net_treatment_part::bind),
            sizeof(*conf->headr.at(core::net::net_treatment_part::bind))) != 0) {
        conf->error_buffer.push_back(WSAGetLastError());

        static core::word __thread buffer[128];

        snprintf(buffer, sizeof(buffer), "error connection: %d\n", conf->error_buffer.at(conf->error_buffer.size() - 1));

        conf->exception_error_buffer.push_back((std::string)buffer);
    }
    #endif
}

core::empty_type ISocket::_send(std::string &message, core::int32_t flags) {

}

core::empty_type ISocket::_send(std::vector<std::string> &messages, core::int32_t flags) {

}

ISocket::SOCKET ISocket::_accept() {
    //if (conf->socks.at(core::net::net_treatment_part::accept) = accept(conf->socks.at(core::net::net_treatment_part::bind), (sockaddr*)))
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
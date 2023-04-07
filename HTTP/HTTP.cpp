//
// Created by MikoG on 30.03.2023.
//
#include "IHTTP.h"

IHTTP::IHTTP(const IHTTP &resp) {
    *this = resp;
}

IHTTP::IHTTP(const std::string &url, const std::string &http_method, const core::uint16_t port) {
    http = new http_t();

    this->http->host        = url;
    this->http->http_method = http_method;
    this->http->port        = port;
}

std::string IHTTP::GetIpServer() {
    addrinfo *get_addr, *result;

    get_addr = new addrinfo();

    if (getaddrinfo(this->http->host.c_str(), std::to_string(this->http->port).c_str(), get_addr, &result)) {
        this->http->error_buffer.push_back(core::http::http_err::error_hook_ip);

        static core::word __thread buffer[128];

        snprintf(buffer, sizeof(buffer), "error get ip from url: %s\r\nerrcode: %d\r\n", this->http->host.c_str(), core::http::http_err::error_hook_ip);

        this->http->exception_buffer.push_back((std::string)buffer);
    }

    sockaddr_in *addr = new sockaddr_in();

    memcpy(addr, result->ai_addr, sizeof(*result->ai_addr));

    return this->http->sock->_inet_ntoa(addr->sin_addr);
}
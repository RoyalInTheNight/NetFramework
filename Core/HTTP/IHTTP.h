//
// Created by MikoG on 30.03.2023.
//

#ifndef NETFRAMEWORK_IHTTP_H
#define NETFRAMEWORK_IHTTP_H

#include "../NET/INET.h"

class IHTTP {
private:
    typedef struct http_conf {
        std::string host;
        std::string http_method;

        ISocket *sock;

        core::uint16_t port;

        std::vector<core::int32_t> error_buffer;
        std::vector<std::string> exception_buffer;
    } http_t;

    http_t *http;

    std::string GetIpServer();
public:
    IHTTP(const IHTTP&);
    IHTTP(const std::string&, const std::string& = core::http::get, const core::uint16_t = 80); // url and http_method

    std::string RandomUserAgent();

    virtual core::empty_type Request(const std::string&, const std::string&); // user agent, 2 - arg if http_method is POST
    virtual core::empty_type ServerInfo();
    virtual core::empty_type new_res();
    virtual core::empty_type Patch(const std::string&); // patch line

    virtual ~IHTTP();
};

class IHTTPResponce : public IHTTP {

};

#endif //NETFRAMEWORK_IHTTP_H

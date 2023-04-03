#include "Core\NET\INET.h"

core::empty_type ISocket::start() {
    _bind();

    if (_accept(0xf) == INVALID_SOCKET)
        exit(-1);

    core::net::winsock_buffer_t h = new core::word[1024];
    _recv(h, 1024, core::net::isocket::accept);
    std::cout << "msg: " << h << std::endl;

}

int main () {
    ISocket test("0.0.0.0", 4444, "tcp", "cache.ch");

    test.start();

}
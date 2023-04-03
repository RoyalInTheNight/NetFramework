#include "Core\NET\INET.h"

core::empty_type ISocket::start() {
    _connect();
    std::string mes = "RAEASDASDWADSAD";
    _send(mes, core::net::isocket::connect);
}

int main () {
    ISocket test("127.0.0.1", 4444, "tcp", "cache2.ch");

    test.start();
}
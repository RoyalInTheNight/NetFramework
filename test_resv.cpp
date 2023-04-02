#include "Core\NET\INET.h"

core::empty_type ISocket::start() {
    _bind();
    core::net::winsock_buffer_type h = new core::word[1024];
    _recv(h, 1024, core::net::net_treatment_part::bind);
    std::cout << h << "  suka nah!!!!!!!!!!!!!!!!!!!!!!!!!!!!";

}

int main () {
    ISocket test("192.168.0.1", 4444, "tcp:pick", "fuck");

    test.start();

}
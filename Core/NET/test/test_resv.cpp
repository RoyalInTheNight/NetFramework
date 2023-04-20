#ifdef WIN64
#include "..\INET.h"
#else
#include "../INET.h"
#endif

core::empty_type INetWork::start() {
    _bind();

    if (_accept(SOMAXCONN) < 0)
        exit(-1);

    core::net::winsock_buffer_t h = new core::word[1024];
    _recv(h, core::net::isocket::accept);
    std::cout << "msg: " << h << std::endl;

}

int main () {
    INetWork text("0.0.0.0", 4445, "tcp", "cache.ch");
    INetErrors test;
    text.start();

    std::vector<core::int32_t> error_buffer = test.GetLastErrors();

    for (core::int32_t err : error_buffer)
        std::cout << "error: " << err << std::endl;
}
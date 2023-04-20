#ifdef WIN64
#include "..\INET.h"
#else
#include "../INET.h"
#endif

core::empty_type INetWork::start() {
    _connect();

    std::string mes;
    std::vector<decltype(mes)> mes2 = {"raw", "wae", "rawsd", "ewa", "raw", "wae", "rawsd", "ewa","raw", "wae", "rawsd", "ewa",
                                       "raw", "wae", "rawsd", "ewa","raw", "wae", "rawsd", "ewa","raw", "wae", "rawsd", "ewa",
                                       "raw", "wae", "rawsd", "ewa","raw", "wae", "rawsd", "ewa","raw", "wae", "rawsd", "ewa",
                                       "raw", "wae", "rawsd", "ewa"};
    _send(mes2, core::net::isocket::connect);
}

int main () {
    INetWork text("127.0.0.1", 4445, "tcp", "cache2.ch");
    INetErrors test;
    text.start(); //

    std::vector<core::int32_t> error_buffer = test.GetLastErrors();
}
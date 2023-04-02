#include "INET.h"

core::empty_type ISocket::start() {
    _connect();
    std::string mes = "ээээээээээээээээээээээээээ";
    _send(mes, core::net::net_treatment_part::connect);
}

int main () {
    ISocket test("192.168.0.1", 4444, "tcp:pick", "fuck");

    test.start();

}
#import "INET.h"

ISocket::ISocket(const ISocket& copy_settings) {
    *this = copy_settings;
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
#ifndef NETFRAMEWORK_INET_H
#define NETFRAMEWORK_INET_H

#ifdef WIN64 // Windows
#import <WinSock2.h>

#else // Linux
#import <sys/socket.h>
#import <arpa/inet.h>
#import <netinet/in.h>

#endif

#import <iostream>

class Interface {



    ~Interface(); //closesocket
};

#endif //NETFRAMEWORK_INET_H

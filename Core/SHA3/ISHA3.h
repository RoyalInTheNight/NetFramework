#ifndef NETFRAMEWORK_SHA3_H
#define NETFRAMEWORK_SHA3_H
#import <iostream>
#import "../Core.h"
#import "../BLOB/IBLOB.h"

class sha3 {
private:
    const core::int32_t     rounds = 24;
    const core::int32_t         asl = 6;
    const core::int32_t    state = 1600;
    const core::int32_t    length = 512;
    const core::int32_t      rate = 576; // размер блока
    const core::int32_t capacity = 1024; // вместимость
    core::blob::_32bits            data;
public:
    sha3(core::blob::_32bits address);
    core::blob::_32bits hashing();
};
#endif


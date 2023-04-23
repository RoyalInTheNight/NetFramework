#ifndef NETFRAMEWORK_IBLOB_H
#define NETFRAMEWORK_IBLOB_H

#import "../Core.h"
//#import "../ISPtr.h"
#import "../FS/IFS.h"
#import <iostream>
#import <thread>
#import "IDatabase.h"


class IBLOB {
private:
    std::vector<std::vector<core::blob::_8bits>> binaryBase;
public:
    IBLOB(IDatabase &);
    std::vector<std::vector<core::blob::_8bits>> getBinaryBase();
    void addDataToBLOB(const fs::path &);
};


#endif //NETFRAMEWORK_IBLOB_H

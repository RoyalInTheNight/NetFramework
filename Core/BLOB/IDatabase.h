#ifndef NETFRAMEWORK_IDATABASE_H
#define NETFRAMEWORK_IDATABASE_H
#import "../Core.h"
#import <vector>
class IDatabase {
private:
    std::vector<std::string> base_of_addresses;
public:
   void addDataLine(std::string &, std::vector<std::string> &);
   std::vector<std::string> getBase();
};

#endif //NETFRAMEWORK_IDATABASE_H

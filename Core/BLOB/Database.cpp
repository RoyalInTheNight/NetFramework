#import "IDatabase.h"

void IDatabase::addDataLine(std::string &tunneling_address, std::vector<std::string> &local_addresses) {
    std::string a;
    a.push_back(tunneling_address);
    for(int i=0; i < local_addresses.size(); i++) {
        a.push_back('[');
        a.push_back(local_addresses.at(i));
        a.push_back(']');
    }
    base_of_addresses.push_back(a);
}

std::vector<std::string> IDatabase::getBase() {
    return base_of_addresses;
}
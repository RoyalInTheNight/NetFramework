#import "IBLOB.h"
// 01011011->[ 01011101->]
IBLOB::IBLOB(IDatabase &data) {
    std::vector<std::string> base = data.getBase();
    std::vector<std::vector<core::blob::_8bits>> binaryBase;
    for(int i=0; i < base.size(); i++) {
        for(auto &c : base.at(i))
            (binaryBase.at(i)).push_back(core::blob::_8bits(c));
    }

}

std::vector<std::vector<core::blob::_8bits>> IBLOB::getBinaryBase() {
    return binaryBase;
}

void IBLOB::addDataToBLOB(const fs::path &path) {
    IFileSystem imgoingto;
    imgoingto.WriteFile(const &path, const &this->getBinaryBase());
}

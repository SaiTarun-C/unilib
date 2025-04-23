#include "data/xml.hpp"
#include <sstream>

namespace unilib::data {

bool XmlWrapper::parseFromString(const std::string& xmlStr) {
    doc_.Reset();
    tinyxml2::XMLError err = doc_.Parse(xmlStr.c_str());
    lastError_.clear();
    if (err != tinyxml2::XML_SUCCESS) {
        lastError_ = doc_.ErrorStr();
        return false;
    }
    return true;
}

bool XmlWrapper::parseFromFile(const std::string& filename) {
    doc_.Reset();
    tinyxml2::XMLError err = doc_.LoadFile(filename.c_str());
    lastError_.clear();
    if (err != tinyxml2::XML_SUCCESS) {
        lastError_ = doc_.ErrorStr();
        return false;
    }
    return true;
}

std::string XmlWrapper::stringify(bool compact) const {
    tinyxml2::XMLPrinter printer(nullptr, !compact);
    doc_.Print(&printer);
    return std::string(printer.CStr());
}

bool XmlWrapper::saveToFile(const std::string& filename, bool compact) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        return false;
    }
    out << stringify(compact);
    return true;
}

tinyxml2::XMLDocument& XmlWrapper::doc() {
    return doc_;
}

const std::string& XmlWrapper::lastError() const {
    return lastError_;
}

} // namespace unilib::data

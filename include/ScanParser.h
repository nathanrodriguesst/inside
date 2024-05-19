#ifndef INSIDE_SCANPARSER_H
#define INSIDE_SCANPARSER_H

#include <string>
#include <vector>
#include <tuple>

struct ScanResult {
    std::string port;
    std::string protocol;
    std::string status;
    std::string service;
    std::string version;
};

class ScanParser {
public:
    explicit ScanParser();
    static std::vector<ScanResult> parseScanResult(std::string &scanResult);
};

#endif //INSIDE_SCANPARSER_H
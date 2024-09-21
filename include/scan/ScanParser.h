#ifndef INSIDE_SCANPARSER_H
#define INSIDE_SCANPARSER_H

#include <string>
#include <vector>

struct ScanResult {
    int port;
    std::string protocol;
    std::string status;
    std::string service;
    std::string version;
};

class ScanParser {
public:
    explicit ScanParser();
    static std::vector<ScanResult> parseScanResult(std::string &scanResult);\
};

#endif
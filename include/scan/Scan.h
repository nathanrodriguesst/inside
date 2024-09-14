#ifndef INSIDE_SCAN_H
#define INSIDE_SCAN_H

#include<string>

class Scan {
public:
    explicit Scan();
    static std::string prepareNmapScan(const std::string &ip, const std::string &args);
};

#endif
#ifndef INSIDE_SCAN_H
#define INSIDE_SCAN_H

#include<string>

class Scan {
public:
    explicit Scan();
    static std::string prepareNmapScan(const std::string &ip, const std::string &args);
    static std::string PrepareDirectoryBruteForce(const std::string &target, const std::string &args);

private:
    static std::string execute(const char* cmd);
};

#endif //INSIDE_SCAN_H

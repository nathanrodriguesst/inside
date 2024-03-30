#ifndef INSIDE_SCAN_H
#define INSIDE_SCAN_H
#include <string>

std::string nmapScan (const std::string& ip, const std::string& args);

std::string feroxbusterScan(const std::string& target, const std::string& args);

#endif //INSIDE_SCAN_H
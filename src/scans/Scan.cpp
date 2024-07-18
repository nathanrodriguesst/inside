#include <iostream>
#include <memory>
#include <cstdio>
#include <array>
#include <string>
#include "../../include/scan/Scan.h"

Scan::Scan() = default;

std::string Scan::execute(const char* cmd) {
    std::array<char, 128> buffer{};
    std::string result;

    std::unique_ptr<FILE, decltype(&pclose)> pipe (popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("Scan execution failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result.append(buffer.data());
    }

    return result;
}

std::string Scan::prepareNmapScan(const std::string &ip, const std::string &args) {
    std::string scan = "nmap ";
    std::string cmd = scan.append(args).append(" ").append(ip);

    std::string result = execute(cmd.c_str());

    return result;
}

std::string Scan::PrepareDirectoryBruteForce(const std::string &target, const std::string &args) {
    std::string feroxBinPath = "../resources/feroxbuster ";
    std::string targetCmd = " --url http://" + target + " ";
    std::string wordListPath = " --wordlist ../resources/wordlists/directory-list-2.3-small.txt";
    std::string cmd = feroxBinPath.append(targetCmd);

    std::string result = execute(cmd.c_str());

    return result;
}
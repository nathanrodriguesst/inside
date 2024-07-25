
#include <string>
#include "../../include/scan/Scan.h"
#include "utils/CommandLineExecute.h"

Scan::Scan() = default;

std::string Scan::prepareNmapScan(const std::string &ip, const std::string &args) {
    std::string scan = "nmap ";
    std::string cmd = scan.append(args).append(" ").append(ip);

    std::string result = CommandLineExecute::executeCommand(cmd.c_str());
    return result;
}

std::string Scan::PrepareDirectoryBruteForce(const std::string &target, const std::string &args) {
    std::string feroxBinPath = "../resources/feroxbuster ";
    std::string targetCmd = " --url http://" + target + " ";
    std::string wordListPath = " --wordlist ../resources/wordlists/directory-list-2.3-small.txt";
    std::string cmd = feroxBinPath.append(targetCmd);

    std::string result = CommandLineExecute::executeCommand(cmd.c_str());

    return result;
}
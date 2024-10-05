
#include <string>
#include <iostream>
#include "../../include/scan/Scan.h"
#include "utils/CommandLineExecute.h"
#include "data/DBConnector.h"
#include "data/ExploitScanRepository.h"

Scan::Scan() = default;

std::string Scan::prepareNmapScan(const std::string &ip, const std::string &args) {
    std::string scan = "nmap ";
    std::string cmd = scan.append(args).append(" ").append(ip);

    std::cout << "[*] Running nmap scan..." << std::endl;
    std::string result = CommandLineExecute::executeCommand(cmd.c_str());

    auto conn = DBConnector::generateDatabaseConnectionInstance();

    // Result will be stored in the database after exploit running, successfully or not.
    if (conn) {
        std::string activityType = "Scan";
        bool scanSuccess = true; //Always true since nmap will give some output on the target nonetheless.

        ExploitScanRepository::createExploitScanRegister(
                conn,
                const_cast<std::string &>(ip),
                activityType, scanSuccess
        );
    }
    return result;
}

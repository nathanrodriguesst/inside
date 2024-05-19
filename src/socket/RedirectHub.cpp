#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <tuple>
#include <string>
#include "RedirectHub.h"
#include "../../include/Scan.h"
#include "../include/ScanParser.h"

std::string RedirectHub::redirect(const char *buffer) {
    try {
        // Attempt to parse JSON
        std::cout << "Parsing JSON...\n";
        nlohmann::json socketData = nlohmann::json::parse(buffer);

        if (socketData.is_object()) {
            std::string action = socketData["action"];

            if (action == "nmap-scan") {
                std::cout << "Initializing nmap scan...\n";
                // Extract IP and args from JSON
                std::string ip = socketData["ip"];
                std::string args = socketData["args"];

                return Scan::prepareNmapScan(ip, args);
            } else if (action == "feroxbuster-scan") {
                std::cout << "Initializing feroxbuster scan...\n";
                std::string url = socketData["url"];
                std::string args = socketData["args"];

                std::cout << "ferox";
                return Scan::PrepareDirectoryBruteForce(url, args);
            } else if (action == "internal-net-analysis") {
                std::cout << "Initializing internal network analysis...\n";
                std::string ip = socketData["ip"];
                std::string args = "-sV -Pn";

                std::string scanResult = Scan::prepareNmapScan(ip, args);
                if (scanResult.empty()) {
                    return "No results for open ports";
                }

                std::vector<ScanResult> parsedScanVector = ScanParser::parseScanResult(scanResult);

                //move to mapping class
                for (const auto &result:parsedScanVector) {
                    const std::string resultScanPort = result.port;
                    const std::string resultScanProtocol = result.protocol;
                    const std::string resultScanStatus = result.status;
                    const std::string resultScanService = result.service;
                    const std::string resultScanVersion = result.version;


                    std::string concatenatedResult;
                    concatenatedResult.append(" port:")
                            .append(resultScanPort)
                            .append(" protocol:")
                            .append(resultScanProtocol)
                            .append("status")
                            .append(resultScanStatus)
                            .append(" service:")
                            .append(resultScanService)
                            .append(" version:")
                            .append(resultScanVersion);

                    return concatenatedResult;
                }
            }
        }
    } catch (const std::exception& e) {
        return "json error";
    }
    return "";
}
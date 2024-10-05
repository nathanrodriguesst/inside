#include "scan/ScanParser.h"
#include <regex>
#include <vector>
#include <iostream>
#include "utils/TrimUtils.h"

ScanParser::ScanParser() = default;

std::vector<ScanResult> ScanParser::parseScanResult(std::string &scanResult) {
    std::regex mappingRegex((R"((\d+)(?:\/(tcp|udp|icmp))(\s+open\s+)(\S+)(\s+.*))"));
    std::smatch match;
    std::vector<ScanResult> resultsVector;

    std::cout << "[*] Parsing services string..." << std::endl;
    for (auto it = std::sregex_iterator(scanResult.begin(),
                                        scanResult.end(),
                                        mappingRegex);
                                        it != std::sregex_iterator();
                                        ++it) {
        resultsVector.emplace_back(
            ScanResult{ std::stoi(TrimUtils::trim((*it)[1].str())),
                TrimUtils::trim((*it)[2].str()),
                TrimUtils::trim((*it)[3].str()),
                TrimUtils::trim((*it)[4].str()),
                TrimUtils::trim((*it)[5].str())
            }
        );
    }

    return resultsVector;
}

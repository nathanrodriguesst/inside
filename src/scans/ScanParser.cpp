#include "../../include/ScanParser.h"
#include <regex>
#include <vector>

ScanParser::ScanParser() = default;

std::vector<ScanResult> ScanParser::parseScanResult(std::string &scanResult) {
    std::regex portProtocolServiceVersionRegex((R"((\d+)(?:\/(tcp|udp|icmp))(\s+open\s+)(\S+)(\s+.*))"));
    std::smatch match;
    std::vector<ScanResult> resultsVector;

    for (auto it = std::sregex_iterator(scanResult.begin(),scanResult.end(),portProtocolServiceVersionRegex);
            it != std::sregex_iterator();
            ++it) {
        resultsVector.emplace_back(ScanResult{(*it)[1].str(), (*it)[2].str(),
                                              (*it)[3].str(),(*it)[4].str(),
                                              (*it)[5].str()});
    }

    return resultsVector;
}

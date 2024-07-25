#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include "restAPI/Routes.h"
#include "scan/Scan.h"
#include "scan/ScanParser.h"
#include "../vendor/http/httplib.h"
#include "exploit/Exploit.h"
#include "mapping/VulnerabilityMapping.h"

using json = nlohmann::json;

void setCORSHeaders(httplib::Response &res) {
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
}

void Routes::handleNmapScan(const httplib::Request &req, httplib::Response &res) {
    json data;
    std::string errs;

    try {
        data = json::parse(req.body);
        std::cout << "Initializing nmap scan...\n";

        std::string ip = data["ip"];
        std::string args = data["args"];

        std::string scanOutput = Scan::prepareNmapScan(ip, args);

        data["response"] = scanOutput;
        setCORSHeaders(res);
        res.set_content(data.dump(), "application/json");
    } catch (const std::exception &e) {
        setCORSHeaders(res);
        res.status = 400;
        res.set_content("Invalid JSON", "text/plain");
    }
}

void Routes::handleFeroxBusterScan(const httplib::Request &req, httplib::Response &res) {
    json data;
    std::string errs;

    try {
        data = json::parse(req.body);

        std::cout << "Initializing feroxbuster scan...\n";

        std::string url = data["url"];
        std::string args = data["args"];

        std::string scanOutput = Scan::PrepareDirectoryBruteForce(url, args);

        data["response"] = scanOutput;
        setCORSHeaders(res);
        res.set_content(data.dump(), "application/json");
    } catch (const std::exception &e) {
        setCORSHeaders(res);
        res.status = 400;
        res.set_content("Invalid JSON", "text/plain");
    }
}

void Routes::handleInternalNetworkAnalysis(const httplib::Request &req, httplib::Response &res) {
    json data;
    std::string errs;

    try {
        data = json::parse(req.body);

        std::cout << "Initializing Internal Network Analysis...\n";

        std::string ip = data["ip"];
        std::string nmapArgs = "-sV";

        // Processing scans and attacks
        std::string scanOutput = Scan::prepareNmapScan(ip, nmapArgs);

        std::vector<ScanResult> parsedScanVector = ScanParser::parseScanResult(scanOutput);

        VulnerabilityMapping vm;
        std::vector<std::string> vulnerableServices = vm.findVulnerableServices(parsedScanVector);

        std::string exploitationResult = Exploit::exploitVulnerableServices(vulnerableServices, ip);

        data["response"] = exploitationResult;

        setCORSHeaders(res);
        res.set_content(data.dump(), "application/json");
    } catch (const std::exception &e) {
        setCORSHeaders(res);
        res.status = 400;
        res.set_content("Invalid JSON", "text/plain");
    }
}

void Routes::setupRoutes(httplib::Server &svr) {
    svr.Post("/nmap-scan", [](const httplib::Request &req, httplib::Response &res) {
        handleNmapScan(req, res);
    });

    svr.Post("/feroxbuster-scan", [](const httplib::Request &req, httplib::Response &res) {
        handleFeroxBusterScan(req, res);
    });

    svr.Post("/internal-net-analysis", [](const httplib::Request &req, httplib::Response &res) {
        handleInternalNetworkAnalysis(req, res);
    });
}
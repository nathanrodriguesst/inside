#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include "restAPI/Routes.h"
#include "scan/Scan.h"
#include "scan/ScanParser.h"
#include "exploit/Exploit.h"
#include "mapping/VulnerabilityMapping.h"
#include "reports/ReportManager.h"

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
        std::vector<std::string> vulnerableServices = vm.findVulnerableServices(parsedScanVector, ip);

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

void Routes::handleHomeDetails(const httplib::Request &req, httplib::Response &res) {
    nlohmann::json data;

    try {
        //data = nlohmann::json::parse(req.body);
        std::cout << "Setting up home data...\n";

        std::vector<VulnerableService> vulnerableServicesRegisters = ReportManager::getVulnerabilitiesRecords();
        std::vector<ExploitScan> recentActivities = ReportManager::getRecentActivities();
        int exploitCount = ReportManager::countExploits();
        int scanCount = ReportManager::countScans();
        int vulnerabilitiesCount = ReportManager::countVulnerabilities();

        // Create a JSON object for the response
        nlohmann::json response;
        response["vulnerableServicesRegisters"] = vulnerableServicesRegisters;
        response["recentActivities"] = recentActivities;
        response["exploitCount"] = exploitCount;
        response["scanCount"] = scanCount;
        response["vulnerabilitiesCount"] = vulnerabilitiesCount;

        // Assign it to the "response" field of the main JSON object
        data["response"] = response;

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

    svr.Post("/internal-net-analysis", [](const httplib::Request &req, httplib::Response &res) {
        handleInternalNetworkAnalysis(req, res);
    });

    svr.Get("/home-details", [](const httplib::Request &req, httplib::Response &res) {
        handleHomeDetails(req, res);
    });
}
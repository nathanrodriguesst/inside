#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include "socket/Routes.h"
#include "scan/Scan.h"
#include "scan/ScanParser.h"
#include "../vendor/http/httplib.h"
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
        //std::string scanOutput = Scan::prepareNmapScan(ip, nmapArgs);

        std::string scanOutput =
            "Starting Nmap 7.80 ( https://nmap.org ) at 2024-07-13 12:34 UTC\n"
            "Nmap scan report for example.com (192.0.2.1)\n"
            "Host is up (0.023s latency).\n"
            "Not shown: 995 closed ports\n"
            "PORT     STATE    SERVICE      VERSION\n"
            "22/tcp   open     ssh          OpenSSH 7.6p1 Ubuntu 4ubuntu0.3 (Ubuntu Linux; protocol 2.0)\n"
            "80/tcp   open     http         Apache httpd 2.4.29 ((Ubuntu))\n"
            "443/tcp  open     ssl/https    Apache httpd 2.4.29\n"
            "3306/tcp open     mysql        MySQL 5.7.25-0ubuntu0.16.04.2\n"
            "8080/tcp open     http-proxy   Squid http proxy 3.5.27\n"
            "\n"
            "Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .\n"
            "Nmap done: 1 IP address (1 host up) scanned in 12.34 seconds\n";

        std::vector<ScanResult> parsedScanVector = ScanParser::parseScanResult(scanOutput);

        VulnerabilityMapping vm;
        std::vector<std::string> vulnerableServices = vm.findVulnerableServices(parsedScanVector);

        std::cout << std::endl << "Vulnerable Services:" << std::endl;
        for (const auto& service : vulnerableServices) {
            std::cout << service << std::endl;
        }

        data["response"] = scanOutput;

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
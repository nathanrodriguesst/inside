#ifndef INSIDE_REPORTMANAGER_H
#define INSIDE_REPORTMANAGER_H

#include <vector>
#include <string>
#include "data/VulnerabilityRepository.h"
#include "data/ExploitScanRepository.h"

class ReportManager {
public:
    static std::vector<VulnerableService> getVulnerabilitiesRecords();
    static std::vector<ExploitScan> getRecentActivities();
    static int countVulnerabilities();
    static int countExploits();
    static int countScans();

    static std::vector<ExploitScan> getRecentActivitiesByTypeAndDate(
            const std::string &startDate, const std::string &endDate, const std::string &type);

    static std::vector<VulnerableService> getVulnerableServicesByDate(
            const std::string &startDate, const std::string &endDate);
};

#endif
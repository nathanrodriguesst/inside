#include "reports/ReportManager.h"
#include "data/DBConnector.h"

std::vector<VulnerableService> ReportManager::getVulnerabilitiesRecords() {
    const auto conn = DBConnector::generateDatabaseConnectionInstance();

    if (conn) {
        return VulnerabilityRepository::selectFromVulnerableServices(conn);
    }

    return {};
}

std::vector<ExploitScan> ReportManager::getRecentActivities() {
    const auto conn = DBConnector::generateDatabaseConnectionInstance();

    if (conn) {
        return ExploitScanRepository::selectFromActivitiesTable(conn);
    }

    return {};
}

int ReportManager::countVulnerabilities() {
    const auto conn = DBConnector::generateDatabaseConnectionInstance();

    if (conn) {
        return VulnerabilityRepository::selectCountVulnerabilities(conn);
    }

    return 0;
}

int ReportManager::countExploits() {
    const auto conn = DBConnector::generateDatabaseConnectionInstance();

    if (conn) {
        return ExploitScanRepository::selectCountExploits(conn);
    }

    return 0;
}

int ReportManager::countScans() {
    const auto conn = DBConnector::generateDatabaseConnectionInstance();

    if (conn) {
        return ExploitScanRepository::selectCountScans(conn);
    }

    return 0;
}
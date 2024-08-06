cmake_minimum_required(VERSION 3.27)
project(inside)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        ${CMAKE_SOURCE_DIR}/include
        /usr/include/mariadb
)

# FetchContent module to download and include nlohmann/json
include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2  # Use the desired version
)

FetchContent_MakeAvailable(json)

add_executable(inside
        src/main.cpp
        src/restAPI/RestfulServer.cpp
        src/scans/Scan.cpp
        src/exploits/Exploit.cpp
        src/scans/ScanParser.cpp
        src/restAPI/Routes.cpp
        src/mapping/VulnerabilityMapping.cpp
        src/utils/TrimUtils.cpp
        src/utils/CommandLineExecute.cpp
        src/data/DBConnector.cpp
        src/reports/ReportManager.cpp
        include/reports/ReportManager.h
        src/data/VulnerabilityRepository.cpp
        include/data/VulnerabilityRepository.h
)

# Link against MariaDB C++ library
target_link_libraries(inside PRIVATE nlohmann_json::nlohmann_json /usr/lib/libmariadbcpp.so)

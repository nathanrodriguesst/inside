cmake_minimum_required(VERSION 3.27)
project(inside)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        ${CMAKE_SOURCE_DIR}/include
)

set(JSON_Install OFF CACHE INTERNAL "")

add_subdirectory(vendor/json)

add_executable(inside
        src/main.cpp
        src/socket/RestfullServer.cpp
        src/scans/Scan.cpp
        src/exploits/Exploit.cpp
        include/exploit/Exploit.h
        src/scans/ScanParser.cpp
        include/scan/ScanParser.h
        src/socket/Routes.cpp
        include/socket/Routes.h
        src/mapping/VulnerabilityMapping.cpp
        include/mapping/VulnerabilityMapping.h
        vendor/http/httplib.h
        src/utils/TrimUtils.cpp
        include/utils/TrimUtils.h
)

target_link_libraries(inside PRIVATE nlohmann_json::nlohmann_json)
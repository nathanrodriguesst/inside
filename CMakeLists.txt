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
        src/socket/SocketServer.cpp
        src/scans/Scan.cpp)

target_link_libraries(inside PRIVATE nlohmann_json::nlohmann_json)
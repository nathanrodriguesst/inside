#include "../../include/utils/CommandLineExecute.h"
#include <iostream>
#include <memory>
#include <cstdio>
#include <array>

std::string CommandLineExecute::executeCommand(const char* cmd) {
    std::array<char, 128> buffer{};
    std::string result;

    std::unique_ptr<FILE, decltype(&pclose)> pipe (popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("Execution failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result.append(buffer.data());
    }

    return result;
}

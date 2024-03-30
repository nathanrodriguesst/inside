#include "../../include/exec.h"
#include <string>

std::string nmapScan(const std::string &ip, const std::string &args) {
  std::string scan = "nmap ";
  std::string cmd = scan + args + " " + ip;
  std::string result = exec(cmd.c_str());

  return result;
}

std::string feroxbusterScan(const std::string &target, const std::string &args) {
    std::string feroxBinPath = "../resources/feroxbuster ";
    std::string targetCmd = " --url http://" + target + " ";
    //std::string wordListPath = " --wordlist ../resources/wordlists/directory-list-2.3-small.txt";
    std::string cmd = feroxBinPath + targetCmd;

    std::string result = exec(cmd.c_str());

    return result;
}

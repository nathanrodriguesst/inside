#include <iostream>
#include <string>
#include "../../include/exec.h"

std::string nmapScan(const std::string& ip, const std::string& args) {
  std::string scan = "nmap ";
  std::string cmd = scan + args + " " + ip;
  std::string result = exec(cmd.c_str());

  return result;
}
#ifndef INSIDE_ANALYSIS_H
#define INSIDE_ANALYSIS_H

#include <vector>
#include <tuple>
#include <string>

class Analysis {
public:
    static std::vector<std::tuple<std::string, std::string, std::string>> compareResults(std::string &scanResult);
};


#endif //INSIDE_ANALYSIS_H

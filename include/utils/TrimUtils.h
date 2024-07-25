#ifndef TRIMUTILS_H
#define TRIMUTILS_H

#include <string>

class TrimUtils {

private:
    static std::string rtrim(std::string s);
    static std::string ltrim(std::string s);

public:
    explicit TrimUtils();
    static std::string trim(std::string s);
};

#endif
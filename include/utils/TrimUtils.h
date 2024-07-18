#ifndef TRIMUTILS_H
#define TRIMUTILS_H

#include <locale>
#include <string>

class TrimUtils {
private:
    static inline std::string rtrim(std::string s);
    static inline std::string ltrim(std::string s);

public:
    explicit TrimUtils();
    static std::string trim(std::string s);
};

#endif
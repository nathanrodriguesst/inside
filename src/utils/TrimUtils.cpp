#include "../include/utils/TrimUtils.h"
#include <algorithm>
#include <cctype>
#include <locale>

TrimUtils::TrimUtils() = default;

inline std::string TrimUtils::ltrim(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    return s;
}

inline std::string TrimUtils::rtrim(std::string s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}

std::string TrimUtils::trim(std::string s) {
    return ltrim(rtrim(s));
}
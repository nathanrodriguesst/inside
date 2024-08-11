#include "utils/TimeUtils.h"

std::string TimeUtils::getCurrentDateTime() {
    time_t now = time(nullptr);
    struct tm timeStruct{};
    char buf[80];
    timeStruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%d%m%Y%H%M%S", &timeStruct);

    return buf;
}

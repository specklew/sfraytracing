#ifndef SF_RAYTRACING_LOGGERHELPER_H
#define SF_RAYTRACING_LOGGERHELPER_H

#include <string>

class LoggerHelper{
public:
    static void addNewRecord(std::string record);
    static std::string getLastTenRecords();

private:
    static const std::string LogPath_;
};

#endif //SF_RAYTRACING_LOGGERHELPER_H

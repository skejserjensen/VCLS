#ifndef LOGFILEHANDLER_H
#define LOGFILEHANDLER_H

#include <string>
#include <vector>
#include <memory>

#include "log.hpp"

class LogFileHandler 
{

    public:
        std::string getLogFilePath();
        std::shared_ptr<Log> getLogData();

        LogFileHandler(std::string logFilePath);
        ~LogFileHandler();

    private:
        std::string logFilePath;
        std::shared_ptr<Log> logData;

        bool readLogFile();


};

#endif /* end of include guard: LOGFILEHANDLER_H */

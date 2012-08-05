#ifndef LOGFILEHANDLER_H
#define LOGFILEHANDLER_H

#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <fstream>
#include <boost/regex.hpp>


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
        bool readSvnVerbose(boost::sregex_token_iterator itr, boost::sregex_token_iterator end);
};

#endif /* end of include guard: LOGFILEHANDLER_H */

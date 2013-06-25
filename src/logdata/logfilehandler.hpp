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
        void readSvnVerbose(std::string& file);
        void readSvnNormal(std::string& file);
        void readGitWhatchanged(std::string& file);
        void readGitNormal(std::string& file);
        void readMercurialStat(std::string& file);
        void readMercurialNormal(std::string& file);
};

#endif /* end of include guard: LOGFILEHANDLER_H */

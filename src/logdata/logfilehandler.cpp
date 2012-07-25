#include "logfilehandler.hpp"

/** Using namespaces **/
using std::string;
using std::cerr;
using std::endl;
using std::shared_ptr;
using std::make_shared;

/** Public methods **/
string LogFileHandler::getLogFilePath() 
{
    return logFilePath;
}

shared_ptr<Log> LogFileHandler::getLogData()
{
    return logData;
}

/** Constructor **/
LogFileHandler::LogFileHandler(string logFilePath)
{
    //The handler contains the path to the file, while the log only saves its name.
    this->logFilePath = logFilePath;
    int posOfLastSlash = logFilePath.find_last_of('/');

    if(posOfLastSlash == -1)
        this->logData = make_shared<Log>(logFilePath);
    else
        this->logData = make_shared<Log>(logFilePath.substr(posOfLastSlash));

    //All file managment is done by the handler as it is vcs specefic, while the log
    //can do data extraction on its own, as the data is saved in the format for all vcs.
    readLogFile();
}

/** Destructor **/
LogFileHandler::~LogFileHandler()
{
}

/** Private methods **/
bool LogFileHandler::readLogFile()
{
    //Using boost::regex as gcc don't have support for std::regex yet, while clang
    //using libc++ is having problem compiling other parts of the code base.
    //TODO: Rewrite the method to use std::regex when gcc supports the features needed
    boost::regex svnVerbose("-{2}");
    std::cout << boost::regex_match("--", svnVerbose) << std::endl;

    return true;
}

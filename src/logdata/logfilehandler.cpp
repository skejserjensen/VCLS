#include "logfilehandler.hpp"

/** Using namespaces **/
using std::string;
using std::cerr;
using std::endl;
using std::ifstream;
using std::shared_ptr;
using std::make_shared;
using std::stringstream;
using boost::regex;
using boost::regex_match;
using boost::sregex_token_iterator;

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
    
    //The file part does only consist of a name, if the file is called from current directory.
    if(posOfLastSlash == -1)
        this->logData = make_shared<Log>(logFilePath);
    else
        this->logData = make_shared<Log>(logFilePath.substr(posOfLastSlash));

    //All file managment is done by the handler as it is vcs specefic, while the log
    //can do data extraction on its own, as the data is saved in the same format for all vcs.
    readLogFile();
}

/** Destructor **/
LogFileHandler::~LogFileHandler()
{
}

/** Private methods **/
bool LogFileHandler::readLogFile()
{
    ifstream logfile;
    logfile.open(logFilePath);

    if(!logfile)
    {
        cerr << "ERROR: logfile could not be found" << endl;
        exit(-1);
    }

    //The file needs to be buffered before it can be used with boost::regex
    stringstream fileBufferStream;
    fileBufferStream << logfile.rdbuf();
    string fileBuffer = fileBufferStream.str();
    logfile.close();

    //Using boost::regex as gcc don't have support for std::regex yet, while clang
    //using libc++ is having problem compiling other parts of the code base.
    //TODO: Rewrite the method to use std::regex when gcc supports the features needed.

    //Regex and method call for svn log file created with the --verbose flag flag
    regex svnVerbose("-{72}\n(r\\d+.+?Changed\\spaths:\\n\\s{3}\\u.+?-{72}\\n)+");
    if(regex_match(fileBuffer, svnVerbose))
    {
        if(readSvnVerbose(fileBuffer))
                return true;
    }

    cerr << "ERROR: logfile was not recognized as a supported format" << endl;
    exit(-1);
}

bool LogFileHandler::readSvnVerbose(string& file)
{
    regex regularExpression(
            "r(\\d+)\\s\\|\\s(.+?)\\s\\|\\s(\\d{4}-\\d{2}-\\d{2})\\s(\\d{2}:\\d{2}:\\d{2}).+?"
            "(\\u\\s.+?)"
            "^$"
            "(.+?)\\n"
            "-{72}\\n"
            );

    boost::sregex_iterator reItStart(file.begin(), file.end(), regularExpression);
    boost::sregex_iterator reItEnd;

    //The outer loop iterates through each commit, while the inner iterates trough each 
    //sub group matched in the commit
    for(; reItStart != reItEnd; ++reItStart)
    {
        //TODO: begin()/end() returns an iterator, but could not find a description of what type
        auto subMatchListBegin = reItStart->begin();
   
        //1: Revision, 2: Author, 3: Date, 4: Time, 5: Actions, 6: Comment
        logData->addCommit((subMatchListBegin+1)->str(), (subMatchListBegin+2)->str(), (subMatchListBegin+4)->str(), (subMatchListBegin+3)->str(), (subMatchListBegin+6)->str());
    }

    return true;
}
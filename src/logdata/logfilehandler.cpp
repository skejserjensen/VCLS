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
using boost::sregex_iterator;

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
    int posOfLastSlash = logFilePath.find_last_of('/')+1;

    //The file part does only consist of a name, if the file is called from current directory.
    if(posOfLastSlash == -1)
        this->logData = make_shared<Log>(logFilePath);
    else
        this->logData = make_shared<Log>(logFilePath.substr(posOfLastSlash));

    //All file management is done by the handler as it is vcs specific, while the log
    //can do data extraction on its own, as the data is saved in the same format for all vcs.
    readLogFile();

    //Handler starts data extraction, as the log class have no information about when data is ready
    logData->extractDataFromCommits();
}

/** Private methods **/
bool LogFileHandler::readLogFile()
{
    ifstream logfile;
    logfile.open(logFilePath);

    if(!logfile)
    {
        throw "ERROR: logfile could not be found";
    }

    //The file needs to be buffered before it can be used with boost::regex
    stringstream fileBufferStream;
    fileBufferStream << logfile.rdbuf();
    string fileBuffer = fileBufferStream.str();
    logfile.close();

    //Using boost::regex as libstdc++ don't have complete support for std::regex yet.
    //TODO: Rewrite the method to use std::regex when libstdc++ supports the features needed.

    //Regex and method call for subversion log files created with the --verbose flag
    regex svnVerbose("-{72}\nr\\d+.+?Changed\\spaths:\\n\\s{3}\\u.+?-{72}\\n");
    if(regex_match(fileBuffer, svnVerbose))
    {
        readSvnVerbose(fileBuffer);
        return true;
    }

    //Regex and method call of subversion log files crated without any flags
    regex svnNormal("-{72}\nr\\d+.+?-{72}\\n");
    if(regex_match(fileBuffer, svnNormal))
    {
        readSvnNormal(fileBuffer);
        return true;
    }

    //Regex and method call of git log files crated with the whatchanged command 
    regex gitWhatchanged("commit\\s[[:alnum:]]{40}.+?\\:\\d{6}.+?");
    if(regex_match(fileBuffer, gitWhatchanged))
    {
        readGitWhatchanged(fileBuffer);
        return true;
    }

    //Regex and method call of git log files crated with the log command 
    regex gitNormal("commit\\s[[:alnum:]]{40}.+?");
    if(regex_match(fileBuffer, gitNormal))
    {
        readGitNormal(fileBuffer);
        return true;
    }

    //Regex and method call of mercurial log files crated with and without the no-merge flag
    regex mercurialStat("changeset:\\s+?\\d+?:[[:alnum:]]{12}.+?\\s\\d+?\\sfiles\\schanged,\\s\\d\\sinsertions.+?");
    if(regex_match(fileBuffer, mercurialStat))
    {
        readMercurialStat(fileBuffer);
        return true;
    }

    //Regex and method call of mercurial log files crated with the stats flag
    regex mercurialNormal("changeset:\\s+?\\d+?:[[:alnum:]]{12}\\n.+?");
    if(regex_match(fileBuffer, mercurialNormal))
    {
        readMercurialNormal(fileBuffer);
        return true;
    }


    throw "ERROR: logfile was not recognized as a supported format";
}

//Methods for handling subversion log files ordered in the same way as in LogFileHandler::readLogFile()
void LogFileHandler::readSvnVerbose(string& file)
{

    //Regex and iterators to extract Revision, Author, Date, Time, Actions and Comments from the various commits
    regex commitsRegex(
            "r(\\d+)\\s\\|\\s(.+?)\\s\\|\\s(\\d{4}-\\d{2}-\\d{2})\\s(\\d{2}:\\d{2}:\\d{2}).+?"
            "(\\u\\s.+?)"
            "^$\\n"
            "(.*?)\\n"
            "-{72}\\n"
            );

    sregex_iterator cmItStart(file.begin(), file.end(), commitsRegex);
    sregex_iterator cmItEnd;

    //Regex to extract Type and Filepath from the various actions contained in the commits
    regex actionsRegex(".*?(\\u)\\s(.+?)\\n");

    for(; cmItStart != cmItEnd; ++cmItStart)
    {
        auto subMatchCommit = cmItStart->begin();

        //1: Revision, 2: Author, 3: Date, 4: Time, 5: Actions, 6: Comment
        Commit& activeCommit = logData->addCommit(
                (subMatchCommit+1)->str(),
                (subMatchCommit+2)->str(),
                (subMatchCommit+4)->str(),
                (subMatchCommit+3)->str(),
                (subMatchCommit+6)->str()
                );

        string actions = (subMatchCommit+5)->str();
        sregex_iterator acItStart(actions.begin(), actions.end(), actionsRegex);
        sregex_iterator acItEnd;

        //1: Action Type, 2: Filepath
        for(; acItStart != acItEnd; ++acItStart)
        {
            //The first string does always only contain one char, which we save as such by extracting it
            auto subMatchAction = acItStart->begin();
            activeCommit.addAction((subMatchAction+1)->str().at(0), (subMatchAction+2)->str());
        }
    }
}

void LogFileHandler::readSvnNormal(string& file)
{
    //Regex and iterators to extract Revision, Author, Date, Time, Actions and Comments from the various commits
    regex commitsRegex(
            "r(\\d+)\\s\\|\\s(.+?)\\s\\|\\s(\\d{4}-\\d{2}-\\d{2})\\s(\\d{2}:\\d{2}:\\d{2}).+?"
            "^$\\n"
            "(.*?)\\n"
            "-{72}\\n"
            );

    sregex_iterator cmItStart(file.begin(), file.end(), commitsRegex);
    sregex_iterator cmItEnd;

    for(; cmItStart != cmItEnd; ++cmItStart)
    {
        auto subMatchCommit = cmItStart->begin();

        //1: Revision, 2: Author, 3: Date, 4: Time, 5: Comment
        logData->addCommit(
                (subMatchCommit+1)->str(),
                (subMatchCommit+2)->str(),
                (subMatchCommit+4)->str(),
                (subMatchCommit+3)->str(),
                (subMatchCommit+5)->str()
                );
    }
}

//Methods for handling git log files ordered in the same way as in LogFileHandler::readLogFile()
void LogFileHandler::readGitWhatchanged(string& file)
{
    //Regex and iterators to extract Revision, Author, Date, Time and Comments from the various commits
    regex commitsRegex(
            "commit\\s([[:alnum:]]{40})\\n"
            ".*?" //A git commit might contain a merge line, which for the program at the moment is irrelevant
            "Author:\\s(.+?)<.+?\\n"
            "Date:\\s\\s\\s\\u\\l\\l\\s(.+?)(\\d\\d:\\d\\d:\\d\\d)\\s(\\d\\d\\d\\d).+?\\n"
            ".+?([[:alnum:]].+?)\\n"
            "^$\\n"
            "(.+?)"
            "^$"
            ); 

    sregex_iterator cmItStart(file.begin(), file.end(), commitsRegex);
    sregex_iterator cmItEnd;

    //Regex to extract Type and Filepath from the various actions contained in the commits
    regex actionsRegex(".*?(\\u)\\t(.+?)\\n");

    for(; cmItStart != cmItEnd; ++cmItStart)
    {
        auto subMatchCommit = cmItStart->begin();

        //1: Revision, 2: Author, 3: Date, 4: Time, 5: Year, 6: Comment, 7: Actions
        Commit& activeCommit = logData->addCommit(
                (subMatchCommit+1)->str(), 
                (subMatchCommit+2)->str(), 
                (subMatchCommit+4)->str(), 
                (subMatchCommit+3)->str() + (subMatchCommit+5)->str(), 
                (subMatchCommit+6)->str()
                );

        string actions = (subMatchCommit+7)->str();
        sregex_iterator acItStart(actions.begin(), actions.end(), actionsRegex);
        sregex_iterator acItEnd;

        //1: Action Type, 2: Filepath
        for(; acItStart != acItEnd; ++acItStart)
        {
            //The first string does always only contain one char, which we save as such by extracting it
            auto subMatchAction = acItStart->begin();
            activeCommit.addAction((subMatchAction+1)->str().at(0), (subMatchAction+2)->str());
        }

    }
}

void LogFileHandler::readGitNormal(string& file)
{
    //Regex and iterators to extract Revision, Author, Date, Time and Comments from the various commits
    regex commitsRegex(
            "commit\\s([[:alnum:]]{40})\\n"
            ".*?" //A git commit might contain a merge line, which for the program at the moment is irrelevant
            "Author:\\s(.+?)<.+?\\n"
            "Date:\\s\\s\\s\\u\\l\\l\\s(.+?)(\\d\\d:\\d\\d:\\d\\d)\\s(\\d\\d\\d\\d).+?\\n"
            ".+?([[:alnum:]].+?)\\n"
            "^$"
            ); 

    sregex_iterator cmItStart(file.begin(), file.end(), commitsRegex);
    sregex_iterator cmItEnd;

    for(; cmItStart != cmItEnd; ++cmItStart)
    {
        auto subMatchCommit = cmItStart->begin();

        //1: Revision, 2: Author, 3: Date, 4: Time, 5: Year, 6: Comment
        logData->addCommit(
                (subMatchCommit+1)->str(), 
                (subMatchCommit+2)->str(), 
                (subMatchCommit+4)->str(), 
                (subMatchCommit+3)->str() + (subMatchCommit+5)->str(), 
                (subMatchCommit+6)->str()
                );
    }
}

//Methods for handling mercurial log files ordered in the same way as in LogFileHandler::readLogFile()
void LogFileHandler::readMercurialStat(string& file)
{
    //Regex and iterators to extract Revision, Author, Date, Time and Comments from the various commits
    regex commitsRegex(
            "changeset:\\s+?(\\d+?):[[:alnum:]]+?\\n"
            ".*?" //A mercurial commit might contain branch and merge lines, which for the program at the moment is irrelevant
            "user:\\s+?(.+?)\\n"
            "date:\\s+?\\u\\l\\l\\s(.+?)(\\d\\d:\\d\\d:\\d\\d)\\s(\\d\\d\\d\\d).+?\\n"
            "summary:\\s{5}(.+?)\\n"
            "^$\\n"
            "(.+?)"
            "^$"
            ); 

    sregex_iterator cmItStart(file.begin(), file.end(), commitsRegex);
    sregex_iterator cmItEnd;

    //Regex to extract Type and Filepath from the various actions contained in the commits
    regex actionsRegex(".*?([[:alnum:]].+?)\\|.+?\\n");

    for(; cmItStart != cmItEnd; ++cmItStart)
    {
        auto subMatchCommit = cmItStart->begin();

        //1: Revision, 2: Author, 3: Date, 4: Time, 5: Year, 6: Comment
        Commit& activeCommit = logData->addCommit(
                (subMatchCommit+1)->str(), 
                (subMatchCommit+2)->str(), 
                (subMatchCommit+4)->str(), 
                (subMatchCommit+3)->str() + (subMatchCommit+5)->str(), 
                (subMatchCommit+6)->str()
                );

        string actions = (subMatchCommit+7)->str();
        sregex_iterator acItStart(actions.begin(), actions.end(), actionsRegex);
        sregex_iterator acItEnd;


        //1: Filepath
        for(; acItStart != acItEnd; ++acItStart)
        {
            //Mercurial does not have a action indicater, so we treat everything a modification of a file
            auto subMatchAction = acItStart->begin();
            activeCommit.addAction('M', (subMatchAction+1)->str());
        }

    }
}

void LogFileHandler::readMercurialNormal(string& file)
{
    //Regex and iterators to extract Revision, Author, Date, Time and Comments from the various commits
    regex commitsRegex(
            "changeset:\\s+?(\\d+?):[[:alnum:]]+?\\n"
            ".*?" //A mercurial commit might contain branch and merge lines, which for the program at the moment is irrelevant
            "user:\\s+?(.+?)\\n"
            "date:\\s+?\\u\\l\\l\\s(.+?)(\\d\\d:\\d\\d:\\d\\d)\\s(\\d\\d\\d\\d).+?\\n"
            "summary:\\s{5}(.+?)\\n"
            "^$"
            ); 

    sregex_iterator cmItStart(file.begin(), file.end(), commitsRegex);
    sregex_iterator cmItEnd;

    for(; cmItStart != cmItEnd; ++cmItStart)
    {
        auto subMatchCommit = cmItStart->begin();

        //1: Revision, 2: Author, 3: Date, 4: Time, 5: Year, 6: Comment
        logData->addCommit(
                (subMatchCommit+1)->str(), 
                (subMatchCommit+2)->str(), 
                (subMatchCommit+4)->str(), 
                (subMatchCommit+3)->str() + (subMatchCommit+5)->str(), 
                (subMatchCommit+6)->str()
                );
    }
}

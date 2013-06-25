#include "maininterface.hpp"

/** Using namespaces **/
using std::string;
using std::shared_ptr;
using std::cout;
using std::endl;

/** Public methods **/
void MainInterface::printResult()
{
    //We grab the pointer to the log data
    shared_ptr<Log> log = logFileHandler->getLogData();


    //All general data is written
    cout << "General Information" << endl << "----------------------" << endl << "Filename: " << log->getFileName() << endl << "Commits: " << log->getCommitsSize() << endl << "Commiters: " << log->getUsersSize() << endl <<  "Average Comment Length: " << log->getAverageCommentLength() << endl << "Average Missing Comments: " << log->getAverageMissingComments() << endl;

    //The users most have done at average one change per commit, so zero means the data was unavailable
    if(log->getAverageChangesInCommits() != 0)
        cout << "Average Number Of Changes: " << log->getAverageChangesInCommits() << endl;


    //All user specific data is written 
    unsigned int counter = 0;
    unsigned int usersSize = log->getUsersSize();

    for(; counter < usersSize; counter++)
    {
        //General
        User& user = log->getUser(counter);
        cout << endl << endl << "User Information" << endl << "----------------------" << endl << "Username: " << user.getName() << endl << "Commits: " << user.getCommitsSize() << endl << "Missing Comments: " << user.getMissingComments() << endl << "Average Comment Length: " << user.getAverageCommentLength() << endl;

        if(user.getAverageChangesInCommits() != 0)
            cout << "Average Number Of Changes: " << user.getAverageChangesInCommits() << endl;


        //Work time
        WorkTimeHandler& wth= log->getUser(counter).getWorkTimeHandler();

        unsigned int wthCounter = 0;
        unsigned int workTimeIntervals = wth.getWorkTimeIntervals();

        //The loop is incremented by two as the output is written in two columns
        for(; wthCounter < workTimeIntervals; wthCounter += 2)
        {
            cout << endl << wth.getWorkTimeInterval(wthCounter) << "\t\t" << wth.getWorkTimeInterval(wthCounter+1) << endl << "Commits: " << wth.getWorkTimeIntervalCommits(wthCounter) << "\t\t\t" << "Commits: " << wth.getWorkTimeIntervalCommits(wthCounter+1) << endl << "Missing Comments: " << wth.getWorkTimeIntervalMissingComments(wthCounter) << "\t\t" << "Missing Comments: " << wth.getWorkTimeIntervalMissingComments(wthCounter+1) << endl << endl;
        }


        //Commited files
        CommittedFilesHandler& cfh = log->getUser(counter).getCommitedFilesHandler();

        unsigned int cfhCounter = 0;
        unsigned int mostCommitedFilesSize = cfh.getMostCommitedFilesSize();

        //Some log supported log files does contain information about committed files
        if(mostCommitedFilesSize == 0)
            cout << "The log file did not contain information about commited files." << endl;
        else
        {
            for(; cfhCounter < mostCommitedFilesSize; cfhCounter++)
            {
                cout << cfh.getMostCommitedFileName(cfhCounter) << ": " << cfh.getMostCommitedFileCommits(cfhCounter) << endl;
            }
        }
    }
}

/** Constructor **/
MainInterface::MainInterface(string logFilePath)
{
    //Pointers are set to nullptr to ensure they only are deleted if allocated
    logFileHandler = nullptr;

    try
    {
        logFileHandler = new LogFileHandler(logFilePath);
    }
    catch(char const* exception)
    {
        if(DEBUG)
            cout << exception << endl;

        cout << "ERROR: the specified file is of a type not supported by the program, exciting." << endl;
        exit(-1);
    }
}

/** Destructor **/
MainInterface::~MainInterface()
{
    if(logFileHandler != nullptr)
        delete logFileHandler;
}

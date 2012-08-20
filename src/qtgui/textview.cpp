#include "textview.hpp"

/** Using namespaces **/
using std::endl;
using std::vector;
using std::shared_ptr;
using std::stringstream;

/** Public methods **/
int TextView::getFormattedTextSize()
{
    return formattedText.size();
}

void TextView::setActiveText(unsigned int index)
{
    if(!formattedText.empty())
        setText(formattedText.at(index));
}

void TextView::formatTextGeneral(shared_ptr<Log> log)
{
    //The view needs to be empty if a new file is being loaded
    formattedText.clear();

    //The string is formated using a stream so the string isn't truncated
    stringstream formattedStream;
    formattedStream << "Filename: " << log->getFileName() << endl << "Commits: " << log->getCommitsSize() << endl << "Commiters: " << log->getUsersSize() << endl <<  "Average Comment Length: " << log->getAverageCommentLength() << endl << "Average Missing Comments: " << log->getAverageMissingComments() << endl;
       
    //The users most have done at average one change per commit, so zero means the data was unavailable
    if(log->getAverageChangesInCommits())
        formattedStream << "Average Number Of Changes: " << log->getAverageChangesInCommits() << endl;

    //The string needs to converted to a qstring before it can set, so it is saved as such 
    QString formattedQString = QString::fromStdString(formattedStream.str());
    formattedText.push_back(formattedQString);
}

void TextView::formatTextUsers(shared_ptr<Log> log)
{
    unsigned int counter = 0;
    unsigned int usersSize = log->getUsersSize();

    //The rows from the listview matches with a index in the vector, so it have to be empty before we start
    formattedText.clear();

    for(; counter < usersSize; counter++)
    {
        User& user = log->getUser(counter);

        //The string is formated using a stream so the string isn't truncated
        stringstream formattedStream;
        formattedStream << "Commits: " << user.getCommitsSize() << endl << "Missing Comments: " << user.getMissingComments() << endl << "Average Comment Length: " << user.getAverageCommentLength() << endl;
     
        //The user most have done at average one change per commit, so zero means the data was unavailable
        if(user.getAverageChangesInCommits() != 0)
            formattedStream << "Average Number Of Changes: " << user.getAverageChangesInCommits() << endl;

        //The string needs to converted to a qstring before it can set, so it is saved as such 
        QString formattedQString = QString::fromStdString(formattedStream.str());
        formattedText.push_back(formattedQString);
    }
}

void TextView::formatTextWorkTime(shared_ptr<Log> log)
{
    unsigned int counter = 0;
    unsigned int usersSize = log->getUsersSize();

    //The rows from the listview matches with a index in the vector, so it have to be empty before we start
    formattedText.clear();

    for(; counter < usersSize; counter++)
    {
        WorkTimeHandler& wth= log->getUser(counter).getWorkTimeHandler();

        unsigned int wthCounter = 0;
        unsigned int workTimeIntervals = wth.getWorkTimeIntervals();


        //The string is formated using a stream so the string isn't truncated
        stringstream formattedStream;

        //The loop is incremented by two as the out is written in two columns
        for(; wthCounter < workTimeIntervals; wthCounter += 2)
        {
            formattedStream << wth.getWorkTimeInterval(wthCounter) << "\t\t" << wth.getWorkTimeInterval(wthCounter+1) << endl << "Commits: " << wth.getWorkTimeIntervalCommits(wthCounter) << "\t\t\t" << "Commits:" << wth.getWorkTimeIntervalCommits(wthCounter+1) << endl << "Missing Comments: " << wth.getWorkTimeIntervalMissingComments(wthCounter) << "\t\t" << "Missing Comments: " << wth.getWorkTimeIntervalMissingComments(wthCounter+1) << endl << endl;
        }

        //The string needs to converted to a qstring before it can set, so it is saved as such 
        QString formattedQString = QString::fromStdString(formattedStream.str());
        formattedText.push_back(formattedQString);
    }
}

void TextView::formatTextCommitedFiles(shared_ptr<Log> log)
{
    unsigned int counter = 0;
    unsigned int usersSize = log->getUsersSize();

    //The rows from the listview matches with a index in the vector, so it have to be empty before we start
    formattedText.clear();

    for(; counter < usersSize; counter++)
    {
        CommittedFilesHandler& cfh = log->getUser(counter).getCommitedFilesHandler();

        unsigned int cfhCounter = 0;
        unsigned int mostCommitedFilesSize = cfh.getMostCommitedFilesSize();


        //The string is formated using a stream so the string isn't truncated
        stringstream formattedStream;

        //Some log supported log files does contain information about committed files
        if(mostCommitedFilesSize == 0)
            formattedStream << "The log file did not contain information about commited files." << std::endl;
        else
        {
            for(; cfhCounter < mostCommitedFilesSize; cfhCounter++)
            {
                formattedStream << cfh.getMostCommitedFileName(cfhCounter) << ": " << cfh.getMostCommitedFileCommits(cfhCounter) << std::endl;
            }
        }

        //The string needs to converted to a qstring before it can set, so it is saved as such 
        QString formattedQString = QString::fromStdString(formattedStream.str());
        formattedText.push_back(formattedQString);
    }
}

/** Constructor **/
TextView::TextView(QWidget *parent) : QTextEdit(parent)
{
    setReadOnly(true);
}

/** Destructor **/
TextView::~TextView()
{
}

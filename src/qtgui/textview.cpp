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
    formattedStream << "Filename: " << log->getFileName() << endl << "Commits: " << log->getCommitsSize() << endl << "Commiters: " << log->getUsersSize() << endl <<  "Average Comment Length: " << log->getAverageCommentLength() << endl << "Average Missing Comments: " << log->getAverageMissingComments() << endl << "Average Changes Per Commmit: " << log->getAverageChangesInCommits() << endl;

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
        formattedStream << "Commits: " << user.getCommitsSize() << endl << "Missing Comments: " << user.getMissingComments() << endl << "Average Comment Length: " << user.getAverageCommentLength() << endl << "Average Number Of Changes: " << user.getAverageChangesInCommits() << endl;

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

        for(; wthCounter < workTimeIntervals; wthCounter++)
        {
            formattedStream << wth.getWorkTimeInterval(wthCounter) << endl << "Commits: " << wth.getWorkTimeIntervalCommits(wthCounter) << endl << "Missing Comments: " << wth.getWorkTimeIntervalMissingComments(wthCounter) << endl << endl;
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

        for(; cfhCounter < mostCommitedFilesSize; cfhCounter++)
        {
            formattedStream << cfh.getMostCommitedFileName(cfhCounter) << ": " << cfh.getMostCommitedFileCommits(cfhCounter) << std::endl;
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

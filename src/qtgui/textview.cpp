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

void TextView::formatTextUsers(shared_ptr<Log> log)
{
    unsigned int counter = 0;
    unsigned int usersSize = log->getUsersSize();

    //The rows from the listview matches with a index in the vector, so it have to be empty before we start
    formattedText.clear();

    for(; counter < usersSize; counter++)
    {
        User& user = log->getUser(counter);

        //The string is formated using a stream so the string isen't truncated
        stringstream formattedStream;
        formattedStream << "Commits: " << user.getCommitsSize() << endl << "Missing Comments: " << user.getMissingComments() << endl << "Average Comment Length: " << user.getAverageCommentLength() << endl << "Average Number Of Changes: " << user.getAverageChangesInCommits() << endl;

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

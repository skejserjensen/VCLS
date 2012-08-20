#include "log.hpp"

/** Using namespaces **/
using std::string;
using std::vector;
using std::cerr;
using std::endl;

/** Public methods **/
string Log::getFileName()
{
    return filename;
}

unsigned int Log::getUsersSize()
{
    return users.size();
}

User& Log::addUser(string name)
{
    users.push_back(User(name));
    return users.back();
}

User& Log::getUser(unsigned int index)
{
    try
    {
        return users.at(index);
    }
    catch(...)
    {
        cerr << "ERROR: access to users was out of bounds" << endl;
        exit(-1);
    }
}

unsigned int Log::getCommitsSize()
{
    return commits.size();
}

unsigned int Log::getAverageCommentLength()
{
    return averageCommentLength;
}

unsigned int Log::getAverageMissingComments()
{
    return averageMissingComments;
}

unsigned int Log::getAverageChangesInCommits()
{
    return averageChangesInCommits; 
}

Commit& Log::addCommit(string revision, string author, string time, string date, string comment)
{
    commits.push_back(Commit(revision, author, time, date, comment));
    return commits.back();
}

Commit& Log::getCommit(unsigned int index)
{
    try
    {                                                                
        return commits.at(index);
    }
    catch(...)
    {
        cerr << "ERROR: access to commits was out of bounds" << endl;
        exit(-1);
    }
}

void Log::extractDataFromCommits()
{
    unsigned int commentLength = 0;
    unsigned int missingComments = 0;
    unsigned int changesInCommits = 0;

    //Extraction of general data from the log file 
    for(Commit& commit : commits)
    {
        if(commit.commentMissing())
            missingComments++;

        assignCommitToUser(commit);

        commentLength += commit.getCommentLength();
        changesInCommits += commit.getActionsSize();
    }

    //Computes average based on the number of commits
    unsigned int commitsSize = commits.size();
    averageCommentLength = (commentLength / commitsSize);
    averageChangesInCommits = (changesInCommits / commitsSize);

    //Computes average based on the number of users
    averageMissingComments = (missingComments / users.size()); 

    //Extraction of user specific data from the log file
    for(User& user : users)
        user.extractDataFromCommits();
}

/** Constructor **/
Log::Log(string filename)
{
    averageCommentLength = 0;
    averageMissingComments = 0;
    averageChangesInCommits = 0;

    this->filename = filename;
}

/** Destructor **/
Log::~Log()
{
}

/** Private methods **/
void Log::assignCommitToUser(Commit& commit)
{
    bool userExist;
    userExist = false;
    string userName = commit.getAuthor();

    for(User& user : users)
    {
        if(userName == user.getName())
        {
            user.addCommit(&commit);
            userExist = true;
            break;
        }
    }

    //If the user does not exist then a new one is created and the commited is stored
    if(!userExist)
    {
        User& user = addUser(userName);
        user.addCommit(&commit);
    }
}

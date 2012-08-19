#include "user.hpp"

/** Using namespaces **/
using std::string;
using std::cerr;
using std::endl;

/** Public methods **/
string User::getName()
{
    return name;
}

unsigned int User::getCommitsSize()
{
    return commits.size();
}

Commit& User::addCommit(Commit* commit)
{
    commits.push_back(commit);
    return (*commits.back());
}

Commit& User::getCommit(int index)
{
    try
    {
        Commit& ref = *commits.at(index);
        return ref;
    }
    catch(...)
    {
        cerr << "ERROR: access to commits is out of bounds" << endl;
        exit(-1);
    }
}

unsigned int User::getMissingComments()
{
    return missingComments;
}

unsigned int User::getAverageCommentLength()
{
    return averageCommentLength;
}

unsigned int User::getAverageChangesInCommits()
{
    return averageChangesInCommits; 
}

WorkTimeHandler& User::getWorkTimeHandler()
{
    return workTimeHandler;
}

CommittedFilesHandler& User::getCommitedFilesHandler()
{
    return commitedFilesHandler; 
}

void User::extractDataFromCommits()
{
    unsigned int commentLength = 0;        
    unsigned int changesInCommits = 0;

    for(Commit* commit : commits)
    {
        if(commit->commentMissing())
            missingComments++;

        commentLength += commit->getCommentLength();
        changesInCommits += commit->getActionsSize();

        workTimeHandler.addCommit(commit);
        commitedFilesHandler.addCommit(commit);
    }

    //The handler needs to know when all commits have been aded and data can be extracted
    commitedFilesHandler.extractDataFromCommits();

    unsigned int commitsSize = commits.size();
    averageCommentLength = (commentLength / commitsSize);
    averageChangesInCommits = (changesInCommits / commitsSize);
}

/** Constructor **/
User::User(string name)
{
    missingComments = 0;
    averageCommentLength = 0;

    this->name = name;
}

/** Destructor **/
User::~User()
{
}

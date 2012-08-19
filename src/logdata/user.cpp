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
        cerr << "ERROR: acces to commits is out of bounds" << endl;
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

void User::extractDataFromCommits()
{
    unsigned int commentLength = 0;        

    for(Commit* commit : commits)
    {
        if(commit->commentMissing())
            missingComments++;

        commentLength += commit->getCommentLength();
    }

    averageCommentLength = (commentLength / commits.size());
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

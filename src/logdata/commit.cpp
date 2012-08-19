#include "commit.hpp"

/** Using namespace **/
using std::string;
using std::cerr;
using std::endl;

/** Public methods **/
string Commit::getRevision()
{
    return revision;
}

string Commit::getAuthor()
{
    return author;
}

string Commit::getTime()
{
    return time;
}

string Commit::getDate()
{
    return date;
}

string Commit::getComment()
{
    return comment;
}

unsigned int Commit::getCommentLength()
{
    return comment.length();
}

Action& Commit::getAction(unsigned int index)
{
    try
    {
        return actions.at(index);
    }
    catch(...)
    {
        cerr << "ERROR: access to actions is out of bounds" << endl;;
        exit(-1);
    }
}

Action& Commit::addAction(char actionType, string filePath)
{
    actions.push_back(Action(actionType, filePath));
    return actions.back();
}

int Commit::getActionsSize()
{
    return actions.size();
}

bool Commit::commentMissing()
{
    //A missing comment has length of one, as it allways contains a newline
    //TODO: Trim white space from strings added in the regexses
    if(comment.length() == 1)
    {
        return true;
    }

    return false;
}

/** Constructor **/
Commit::Commit(string revision, string author, string time, string date, string comment)
{
    this->revision = revision;
    this->author = author;
    this->time = time;
    this->date = date;
    this->comment = comment;
}

/** Destructor **/
Commit::~Commit()
{
}

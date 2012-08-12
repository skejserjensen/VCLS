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

void Commit::addAction(Action action)
{
    actions.push_back(action);
}

int Commit::getActionsSize()
{
    return actions.size();
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

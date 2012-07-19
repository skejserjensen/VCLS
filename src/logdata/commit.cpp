#include "commit.hpp"

/** Using namespace **/
using std::string;

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

Action* Commit::getAction(unsigned int index)
{
    if(index > actions.size())
        return nullptr;

    return &actions.at(index);
}

void Commit::addAction(Action action)
{
    actions.push_back(action);
}

int Commit::actionsSize()
{
    return actions.size();
}

/** Constructor **/
Commit::Commit(string revision, string author, string time, string date)
{
    this->revision = revision;
    this->author = author;
    this->time = time;
    this->date = date;
}

/** Destructor **/
Commit::~Commit()
{
}

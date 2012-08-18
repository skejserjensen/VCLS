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

int User::getCommitsSize()
{
    return commits.size();
}

Commit& User::addCommit(Commit* commit)
{
    commits.push_back(commit);
    commitsCounter++;
    
    if(commit->commentMissing())
        missingCommentsCounter++;

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

unsigned int User::getCommitsCounter()
{
    return commitsCounter;
}

unsigned int User::getMissingCommentsCounter()
{
    return missingCommentsCounter;
}

/** Constructor **/
User::User(string name)
{
    commitsCounter = 0;
    missingCommentsCounter = 0;

    this->name = name;
}

/** Destructor **/
User::~User()
{
}

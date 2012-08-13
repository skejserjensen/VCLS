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

/** Constructor **/
User::User(string name)
{
    this->name = name;
}

/** Destructor **/
User::~User()
{
}

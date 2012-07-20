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

int Log::getUsersSize()
{
    return users.size();
}

User& Log::getUser(unsigned int index)
{
    try
    {
        return users.at(index);
    }
    catch(...)
    {
        cerr << "ERROR: acces to users was out of bounds" << endl;
        exit(-1);
    }
}

int Log::getCommitsSize()
{
    return commits.size();
} 

Commit& Log::getCommit(unsigned int index)
{
    try
    {                                                                
        return commits.at(index);
    }
    catch(...)
    {
        cerr << "ERROR: acces to commits was out of bounds" << endl;
        exit(-1);
    }
}

/** Constructor **/
Log::Log(string filename)
{
    this->filename = filename;
}

/** Destructor **/
Log::~Log()
{
}

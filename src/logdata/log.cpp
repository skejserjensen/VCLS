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
        cerr << "ERROR: acces to users was out of bounds" << endl;
        exit(-1);
    }
}

int Log::getCommitsSize()
{
    return commits.size();
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
        cerr << "ERROR: acces to commits was out of bounds" << endl;
        exit(-1);
    }
}

void Log::assignCommitsToUsers()
{
    bool userExist;

    for(Commit& commit : commits)
    {
        userExist = false;
        string userName = commit.getAuthor();

        //A foreach loop is not used for the users as the index is needed outside the scope of the loop
        int usersCounter;
        int usersSize = users.size(); 

        for(usersCounter = 0; usersCounter < usersSize; usersCounter++)
        {
            User& user = users.at(usersCounter);

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

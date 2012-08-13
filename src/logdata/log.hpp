#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
#include <vector>

#include "user.hpp"
#include "commit.hpp"

class Log 
{
    public:
        std::string getFileName();
        int getUsersSize();
        User& addUser(std::string name);
        User& getUser(unsigned int index);
        int getCommitsSize();
        Commit& addCommit(std::string revision, std::string author, std::string time, std::string date, std::string comment);
        Commit& getCommit(unsigned int index);

        Log(std::string filename);
        ~Log();

    private:
        std::string filename;
        std::vector <User> users;
        std::vector <Commit> commits;
};

#endif /* end of include guard: LOG_H */

#ifndef COMMIT_H
#define COMMIT_H

#include <iostream>
#include <string>
#include <vector>

#include "action.hpp"

class Commit
{
    public:
        std::string getRevision();
        std::string getAuthor();
        std::string getTime();
        std::string getDate();
        std::string getComment();
       
        Action& getAction(unsigned int index);
        Action& addAction(char actionType, std::string filePath);
        int getActionsSize();  

        Commit(std::string revision, std::string author, std::string time, std::string date, std::string comment);
        ~Commit();

    private:
        std::string revision;
        std::string author;
        std::string time;
        std::string date;
        std::string comment;
        std::vector<Action> actions;
};

#endif /* end of include guard: COMMIT_H */

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
       
        Action& getAction(unsigned int index);
        void addAction(Action action);
        int getActionsSize();  

        Commit(std::string revision, std::string author, std::string time, std::string date);
        ~Commit();

    private:
        std::string revision;
        std::string author;
        std::string time;
        std::string date;
        std::vector<Action> actions;
};

#endif /* end of include guard: COMMIT_H */

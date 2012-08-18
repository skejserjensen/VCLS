#ifndef USER_H 
#define USER_H

#include <iostream>
#include <string>
#include <vector>

#include "commit.hpp"

class User 
{
    public:
        std::string getName();
        int getCommitsSize();
        Commit& addCommit(Commit* commit);
        Commit& getCommit(int index);

        unsigned int getCommitsCounter();
        unsigned int getMissingCommentsCounter();

        User(std::string name);
        ~User(); 

    private:
        std::string name;
        unsigned int commitsCounter;
        unsigned int missingCommentsCounter;

        //Raw pointers are used as this is only a list of referances 
        //to the actual commits stored in the log class.
        std::vector<Commit*> commits;
};

#endif /* end of include guard: COMITTER_H */

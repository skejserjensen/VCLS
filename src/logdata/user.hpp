#ifndef USER_H 
#define USER_H

#include <iostream>
#include <string>
#include <vector>

#include "commit.hpp"
#include "worktimehandler.hpp"
#include "commitedfileshandler.hpp"

class User 
{
    public:
        std::string getName();
        unsigned int getCommitsSize();
        Commit& addCommit(Commit* commit);
        Commit& getCommit(int index);

        unsigned int getMissingComments();
        unsigned int getAverageCommentLength();
        unsigned int getAverageChangesInCommits();

        WorkTimeHandler& getWorkTimeHandler();
        CommittedFilesHandler& getCommitedFilesHandler();

        void extractDataFromCommits();

        User(std::string name);
        ~User(); 

    private:
        std::string name;
        unsigned int missingComments;
        unsigned int averageCommentLength;
        unsigned int averageChangesInCommits;

        //Raw pointers are used as this is only a list of references 
        //to the actual commits stored in the log class.
        std::vector<Commit*> commits;

        //Saves aggregate information about when commits where made
        WorkTimeHandler workTimeHandler;

        //Saves aggregate information about when commits where made
        CommittedFilesHandler commitedFilesHandler;
};

#endif /* end of include guard: COMITTER_H */

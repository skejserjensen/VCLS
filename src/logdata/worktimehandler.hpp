#ifndef WORKTIMEHANDLER_H
#define WORKTIMEHANDLER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "commit.hpp"

class WorkTimeHandler 
{
    public:
        void addCommit(Commit* commit);
        unsigned int getWorkTimeIntervals();
        std::string& getWorkTimeInterval(unsigned int index);
        unsigned int getWorkTimeIntervalCommits(unsigned int index);
        unsigned int getWorkTimeIntervalMissingComments(unsigned int index);

        WorkTimeHandler();

    private:
        //The intervals corresponding to the computed data is saved for printing;
        std::vector<std::string> workTimeIntervals;

        //The array represents eight three hour intervals with commits and missing comments counted
        const unsigned static int intervals = 8;
        unsigned int workTimeData[intervals][2];
};
#endif /* end of include guard: WORKTIMEHANDLER_H */

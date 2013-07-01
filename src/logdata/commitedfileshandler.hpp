#ifndef COMMITEDFILESHANDLER_H
#define COMMITEDFILESHANDLER_H

#include <iostream>
#include <map>

#include "commit.hpp"

class CommittedFilesHandler 
{
    public:
        void addCommit(Commit* commit);
        void extractDataFromCommits();
        unsigned int getMostCommitedFilesSize();
        std::string& getMostCommitedFileName(unsigned int index);
        unsigned int getMostCommitedFileCommits(unsigned int index);

    private:
        //A multimap is used as multiple files can be committed the same number of times
        std::multimap<unsigned int, std::string> mostCommitedFiles;

        //This map is only used to save temporary references to the commits and will be cleared
        //when data is extracted
        std::map<std::string, unsigned int> fileCommitedCounter;

};
#endif /* end of include guard: COMMITEDFILESHANDLER_H */

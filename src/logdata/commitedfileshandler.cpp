#include "commitedfileshandler.hpp"

/** Using namespaces **/
using std::string;
using std::map;
using std::multimap;
using std::pair;
using std::advance;


/** Public methods **/
void CommittedFilesHandler::addCommit(Commit* commit)
{
    unsigned int counter = 0;
    unsigned int actionsSize = commit->getActionsSize();

    for(; counter < actionsSize; counter++)
    {
        string& filePath = commit->getAction(counter).getFilePath();

        //If the file exist in the map then its counter is incremented, otherwise it is started at one
        if(fileCommitedCounter.count(filePath))
        {
            fileCommitedCounter[filePath] += 1;
        }
        else
            fileCommitedCounter[filePath] = 1;
    }
}

void CommittedFilesHandler::extractDataFromCommits()
{
    //Ensures that extractDataFromCommits is not called without commits        
    if(fileCommitedCounter.empty())
        return;

    //All elements are stored in the invert map to be sorted by commits
    for(pair<string, unsigned int> element : fileCommitedCounter)
    {
        mostCommitedFiles.insert(pair<unsigned int, string>(element.second, element.first));
    }

    //The original map is cleared as there are no reasons to save the inforamtion it contained
    fileCommitedCounter.clear();

    //Only the first ten files are saved as less commited files mosten often are uninteresting
    auto iterator = mostCommitedFiles.end();
    advance(iterator, -10);

    mostCommitedFiles.erase(mostCommitedFiles.begin(), iterator); 
}

unsigned int CommittedFilesHandler::getMostCommitedFilesSize()
{
    return mostCommitedFiles.size();
}

string& CommittedFilesHandler::getMostCommitedFileName(unsigned int index)
{
    auto iterator = mostCommitedFiles.begin();
    advance(iterator, index);

    return iterator->second;
}

unsigned int CommittedFilesHandler::getMostCommitedFileCommits(unsigned int index)
{
    auto iterator = mostCommitedFiles.begin();
    advance(iterator, index);

    return iterator->first;
}

/** Constructor **/
CommittedFilesHandler::CommittedFilesHandler()
{
}

/** Destructor **/
CommittedFilesHandler::~CommittedFilesHandler()
{
}

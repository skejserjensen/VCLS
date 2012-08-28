#include "worktimehandler.hpp"

/** Using namespaces **/
using std::stoi;
using std::cerr;
using std::endl;
using std::string;
using std::stringstream;

/** Public methods **/
void WorkTimeHandler::addCommit(Commit* commit)
{
    unsigned int commitHours = stoi(commit->getTime());

    //A rather ugly way to save information about when commits and missing comments are made
    if(commitHours < 3)
    {
        workTimeData[0][0]++;
        if(commit->commentMissing())
            workTimeData[0][1]++;
    }
    else if (commitHours < 6)
    {
        workTimeData[1][0]++;
        if(commit->commentMissing())
            workTimeData[1][1]++;
    }
    else if (commitHours < 9)
    {
        workTimeData[2][0]++;
        if(commit->commentMissing())
            workTimeData[2][1]++;
    }
    else if (commitHours < 12)
    {
        workTimeData[3][0]++;
        if(commit->commentMissing())
            workTimeData[3][1]++;
    }
    else if (commitHours < 15)
    {
        workTimeData[4][0]++;
        if(commit->commentMissing())
            workTimeData[4][1]++;
    }
    else if (commitHours < 18)
    {
        workTimeData[5][0]++;
        if(commit->commentMissing())
            workTimeData[5][1]++;
    }
    else if (commitHours < 21)
    {
        workTimeData[6][0]++;
        if(commit->commentMissing())
            workTimeData[6][1]++;
    }
    else if (commitHours < 24)
    {
        workTimeData[7][0]++;
        if(commit->commentMissing())
            workTimeData[7][1]++;
    }
} 

unsigned int WorkTimeHandler::getWorkTimeIntervals()
{
    return intervals; 
}

string& WorkTimeHandler::getWorkTimeInterval(unsigned index)
{
    try
    {
        return workTimeIntervals.at(index);
    }
    catch(...)
    {
        throw "ERROR: acces to worktime interval is out of bounds";
    }
}

unsigned int WorkTimeHandler::getWorkTimeIntervalCommits(unsigned int index)
{
    if(index < intervals)
        return workTimeData[index][0];
    else
    {
        cerr << "ERROR: acces to worktime commits is out of bounds" << endl;
        exit(-1);
    }
}

unsigned int WorkTimeHandler::getWorkTimeIntervalMissingComments(unsigned int index)
{
    if(index < intervals)
        return workTimeData[index][1];
    else
    {
        throw "ERROR: acces to worktime missing comments is out of bounds";
    }
}

/** Constructor **/
WorkTimeHandler::WorkTimeHandler()
{
    unsigned int hourCounter = 0;
    unsigned int hourCounterNext = 24/intervals;

    for(; hourCounter < 8; hourCounter++) 
    {
        //All elements is set to zero
        workTimeData[hourCounter][0] = 0;
        workTimeData[hourCounter][1] = 0;
    }

    //The hour counter is resued as its purpose in the above loop is forfiled
    for(hourCounter = 0; hourCounter < 24; hourCounter += hourCounterNext)
    {
        //Stringstream used as temporary container for the string used as workTimeIntervals
        stringstream intervalStream;

        //Ensures that all intervals contains two digits
        if(hourCounter < 10)
            intervalStream << "0" << hourCounter << ":00:00"; 
        else
            intervalStream << hourCounter << ":00:00";

        if((hourCounter + hourCounterNext) < 10)
            intervalStream << " - " << "0" << (hourCounter + hourCounterNext) << ":00:00";
        else
            intervalStream << " - " << (hourCounter + hourCounterNext) << ":00:00";

        workTimeIntervals.push_back(intervalStream.str());
    }
}

/** Destructor **/
WorkTimeHandler::~WorkTimeHandler()
{
}

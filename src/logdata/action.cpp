#include "action.hpp"

/** Using namespaces **/
using std::string;

/** Public methods **/
char Action::getActionType()
{
    return actionType;
}

string& Action::getFilePath()
{
    return filePath;
}

/** Constructor **/
Action::Action(char actionType, string filePath)
{
    this->actionType = actionType;
    this->filePath = filePath;
}

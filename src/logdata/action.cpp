#include "action.hpp"

/** Using namespaces **/
using std::string

/** Public methods **/
char Action::getActionType()
{
    return actionType;
}

string Action::getFileName()
{
    return fileName;
}

/** Constructor **/
Action::Action(char actionType, string fileName)
{
    this.actionType = actionType;
    this.fileName = fileName;
}

/** Destructor **/
Action::~Action()
{
}

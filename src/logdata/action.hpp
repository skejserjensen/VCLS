#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <string>

class Action 
{
    public:
        char getActionType();
        std::string getFileName();

        Action(char, std::string);
        ~Action();
        
    private:
        char actionType;
        std::string fileName;
};

#endif /* end of include guard: ACTION_H */


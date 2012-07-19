#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <string>

class Action 
{
    public:
        char getActionType();
        std::string getFileName();

        Action(char, string);
        ~Action();
        
    private:
        char actionType;
        std::tring fileName;
}

#endif /* end of include guard: ACTION_H */


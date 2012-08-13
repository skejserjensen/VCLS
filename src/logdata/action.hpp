#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <string>

class Action 
{
    public:
        char getActionType();
        std::string getFilePath();

        Action(char actionType, std::string filePath);
        ~Action();
        
    private:
        char actionType;
        std::string filePath;
};

#endif /* end of include guard: ACTION_H */


#ifndef MAININTERFACE_H 
#define MAININTERFACE_H 

#include <iostream>
#include <string>
#include <memory>

#include "../logdata/logfilehandler.hpp"

//Determines if the exceptions caught from the logfilehandler are printed
#define DEBUG 0

class MainInterface
{
    public:
        void printResult();

        MainInterface(std::string logFilePath);
        ~MainInterface();

    private:
        //Raw pointer is used for the internal implementation as it cant be accessed
        LogFileHandler *logFileHandler;
};
#endif /* end of include guard: MAININTERFACE_H */

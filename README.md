#Introduction
VCLS or Version Control Log Statistics, is a small program to calculate various statistics based on log files from different version control systems.

##Version control logs supported
**Subversion:** log files created both with and without the --verbose flag is currently implemented.

**Git:** log files created by the log and whatchanged commands are currently implemented.

##Dependencies
**Boost:** used for its regex  library at the moment as the C++11 version isn't implemented in GCC's library yet, it will be removed when it does.

**QT:** used for the gui at the movement, versions using differant toolkits and the commandline will be implemented when i have some spare time to do it.

##License
The program is license under version 3 of the GPL, and a copy of the license is bundled with the program. 

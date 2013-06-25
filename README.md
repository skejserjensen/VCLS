#Version Control Log Statistics
Version Control Log Statistics, is a small program to calculate various statistics based on log files from different popular version control systems.

##Version control logs supported
**Subversion:** log files created both with and without the --verbose flag is currently implemented.

**Git:** log files created by the log and whatchanged commands are currently implemented.

**Mercurial:** log files created by the log and log with the no-merges or stat flag are currently implemented.

Note: using git wrappers such as git-tfs should allow the git log file to parsed, but this has only been tested very briefly.
##Dependencies
**Boost:** used for its regex library at the moment as the C++11 version isn't implemented in GCC's library yet.

**QT:** used for the Gui at the movement, the command line version can be compiled without it.

## Installation
1. Install dependencies.

2. Compile the program with "make" for a Qt gui or "make cli" for a cli.

## TODO
+ Change the regexes so they use the standard C++11 implementation instead of boosts, when gcc supports it.

##License
The program is licensed under version 3 of the GPL, and a copy of the license is bundled with the program. 

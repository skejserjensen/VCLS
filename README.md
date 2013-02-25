#Version Control Log Statistics,
VCLS or Version Control Log Statistics, is a small program to calculate various statistics based on log files from different version control systems.

##Version control logs supported
**Subversion:** log files created both with and without the --verbose flag is currently implemented.

**Git:** log files created by the log and whatchanged commands are currently implemented.

##Dependencies
**Boost:** used for its regex library at the moment as the C++11 version isn't implemented in GCC's library yet, it will be removed when it does.

**QT:** used for the Gui at the movement, versions using different toolkits or the command line might be implemented when i have some spare time to do it.

## TODO
+ Add support for logs files from more version control systems, mainly Mercurial and Bazaar.
+ Change the regexes so they use the standard C++11 implementation instead of boosts, when gcc supports it.
+ Write a version of the user interface in gtkmm or cli so users aren't forced to use qt on gtk based desktop.
+ Rewrite the svn regexses so they do not include the newline, without requiring the extra call to string.erase()

##License
The program is license under version 3 of the GPL, and a copy of the license is bundled with the program. 

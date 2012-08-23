#Todo List

- Add support for logs files from more version control systems.
- Add a non hackish way to remove whitespace from the regex sub match when a commit is missing a message.
- Change the regexes so they use the standard C++11 implementation instead of boots, when gcc supports it.
- Change the error handling in the log data part of the program to throw exceptions instead of calling exit.
- Write a version of the user interface in gtkmm and cli so users aren't forced to use qt on gtk based desktop.
- Add filters based on the files mime type to the file dialog so it only allows the user to selected plain/text files with considering the extension.

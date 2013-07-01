#include "listview.hpp"

/** Using namespaces **/
using std::shared_ptr;

/** Public methods **/
void ListView::fillList(shared_ptr<Log> log)
{
    unsigned int counter = 0;
    unsigned int usersSize = log->getUsersSize();

    //Clears the list view if another log file has been open before
    clear();

    for(; counter != usersSize; counter++)
    {
        //The qstring is created as the list view has no constructor for std::string
        QString userName = QString::fromStdString(log->getUser(counter).getName());
        addItem(userName);
    }
}

/** Constructor **/
ListView::ListView(QWidget *parent) : QListWidget(parent)
{
}

#include "textview.hpp"

/** Private methods **/

/** Constructor **/
TextView::TextView(QWidget *parent) : QTextEdit(parent)
{
    setReadOnly(true);
}

/** Destructor **/
TextView::~TextView()
{
}

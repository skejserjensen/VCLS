#include "errorpopup.hpp"

/** Constructor **/
ErrorPopup::ErrorPopup(QWidget *parent) : QMessageBox(parent)
{
    addButton(QMessageBox::Ok);
    setWindowTitle("Unsupported log type");
    setText("The file opened is not a supported log file, please select a file containing a log from a supported version control system.");
}

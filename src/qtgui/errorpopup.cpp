#include "errorpopup.hpp"

/** Constructor **/
ErrorPopup::ErrorPopup(QWidget *parent) : QMessageBox(parent)
{
    addButton(QMessageBox::Ok);
    setWindowTitle("Unsupported log type");
    setText("The log type is unsupported, press OK to continue.");
}

/** Destructor **/
ErrorPopup::~ErrorPopup()
{
}

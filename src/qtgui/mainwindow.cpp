#include "mainwindow.hpp"

/** Public methods **/

/** Constructor **/
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    
    openFile = new QPushButton("Open File", this);
    openedFile = new QLineEdit(this);
    windowLayout = new QGridLayout();

    openedFile->setReadOnly(true);
    windowLayout->addWidget(openedFile, 0, 0);
    windowLayout->addWidget(openFile, 0, 1);

    this->setLayout(windowLayout);

}

/** Destructor **/
MainWindow::~MainWindow()
{
}

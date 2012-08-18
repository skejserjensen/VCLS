#include <iostream>
#include <QApplication>

#include "qtgui/mainwindow.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    //Leaving the constructor empty sets the parent as nullptr to prevent seq fault
    MainWindow mainWindow;
    mainWindow.show();

    //Initiates the main loop of the gui program    
    app.exec();

    return 0;
}

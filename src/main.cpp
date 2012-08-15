#include <iostream>
#include <QApplication>

#include "qtgui/mainwindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    //Initiates the main loop of the gui program    
    return app.exec();
}

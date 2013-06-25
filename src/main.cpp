#include <iostream>

#ifdef GUI
    #include <QApplication>
    #include "gui/mainwindow.hpp"
#else
    #include "cli/maininterface.hpp"
#endif

int main(int argc, char **argv)
{
#ifdef GUI
    QApplication app(argc, argv, true);

    //Leaving the constructor empty sets the parent as nullptr to prevent seq fault
    MainWindow mainWindow;
    mainWindow.show();

    //Initiates the main loop of the gui program    
    app.exec();
#else
    if(argc != 2)
    {
        std::cout << "ERROR: non or multiple log files given as command line arguments, exciting." << std::endl;
        exit(-1);
    }

    MainInterface mainInterface(argv[1]);
    mainInterface.printResult();
#endif

    return 0;
}

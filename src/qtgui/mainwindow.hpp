#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

#include "listview.hpp"
#include "textview.hpp"
#include "../logdata/logfilehandler.hpp"

//Determins if the exceptions caught from the handler are printed
#define DEBUG 0

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        //Raw pointer is used for the internal implementation as it cant be accessed
        LogFileHandler *logFileHandler;

        //The qt gui components 
        QPushButton *openFile;
        QLineEdit *openedFile;
        QFileDialog *fileDialog; 

        ListView *listView;
        TextView *generalTextView;

        TextView *topUserTextView;
        TextView *middleUserTextView;
        TextView *bottumUserTextView;

    private slots:
        void selectAndOpenFile();
        void setActiveText();
};

#endif /* end of include guard: MAINWINDOW_H */

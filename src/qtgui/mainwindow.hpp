#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

#include "filedialog.hpp"
#include "listview.hpp"
#include "textview.hpp"
#include "../logdata/logfilehandler.hpp"

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        //Raw pointer is used for the internal implementation as it cant be acessed
        LogFileHandler *logFileHandler;

        //The qt gui components
        QGridLayout *windowLayout;

        QPushButton *openFile;
        QLineEdit *openedFile;
        FileDialog *fileDialog; 

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

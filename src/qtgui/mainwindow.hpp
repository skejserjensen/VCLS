#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

#include "filedialog.hpp"

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        QPushButton *openFile;
        QLineEdit *openedFile;
       
        FileDialog *fileDialog; 

        QGridLayout *windowLayout;

    private slots:
        void selectAndOpenFile();
};

#endif /* end of include guard: MAINWINDOW_H */

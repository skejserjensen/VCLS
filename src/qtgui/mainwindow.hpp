#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <iostream>

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        QGridLayout *windowLayout;
        QPushButton *openFile;
        QLineEdit *openedFile;
        
};

#endif /* end of include guard: MAINWINDOW_H */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

#include "filedialog.hpp"
#include "listview.hpp"
#include "textview.hpp"

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
        FileDialog *fileDialog; 

        ListView *listView;

        TextView *topUserTextView;
        TextView *middleUserTextView;
        TextView *bottumUserTextView;


    private slots:
        void selectAndOpenFile();
};

#endif /* end of include guard: MAINWINDOW_H */

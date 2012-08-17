#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QtGui>

class FileDialog : public QFileDialog
{
    Q_OBJECT

    public:
        FileDialog(QWidget *parent);
        ~FileDialog();

    private:
        /* data */
};


#endif /* end of include guard: FILEDIALOG_H */

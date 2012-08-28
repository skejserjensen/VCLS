#ifndef ERRORPOPUP_H
#define ERRORPOPUP_H

#include <QtGui>

class ErrorPopup : public QMessageBox  
{
    Q_OBJECT

    public:
        ErrorPopup(QWidget *parent = nullptr);
        ~ErrorPopup();

    private:

};

#endif /* end of include guard: ERRORPOPUP_H */

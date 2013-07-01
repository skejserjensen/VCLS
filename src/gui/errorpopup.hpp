#ifndef ERRORPOPUP_H
#define ERRORPOPUP_H

#include <QMessageBox>

class ErrorPopup : public QMessageBox  
{
    Q_OBJECT

    public:
        ErrorPopup(QWidget *parent = nullptr);
};
#endif /* end of include guard: ERRORPOPUP_H */

#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <QtGui>

class TextView : public QTextEdit 
{
    Q_OBJECT

    public:
        TextView(QWidget *parent);
        ~TextView();

    private:
        /* data */
};


#endif /* end of include guard: TEXTVIEW_H */

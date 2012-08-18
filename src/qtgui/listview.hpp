#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QtGui>

class ListView : public QListWidget
{
    Q_OBJECT

    public:
        ListView(QWidget *parent);
        ~ListView();

    private:
        /* data */
};

#endif /* end of include guard: TREEVIEW_H */

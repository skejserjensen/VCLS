#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QtGui>
#include <memory>

#include "../logdata/logfilehandler.hpp"

class ListView : public QListWidget
{
    Q_OBJECT

    public:
        void fillList(std::shared_ptr<Log> log);

        ListView(QWidget *parent);
        ~ListView();

    private:
};

#endif /* end of include guard: TREEVIEW_H */

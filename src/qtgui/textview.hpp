#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <iostream>
#include <sstream>
#include <QtGui>

#include "../logdata/logfilehandler.hpp"

class TextView : public QTextEdit 
{
    Q_OBJECT

    public:
        int getFormattedTextSize();
        void setActiveText(unsigned int index); 
        void formatTextUsers(std::shared_ptr<Log> log);
        void formatTextWorkTime(std::shared_ptr<Log> log);
        void formatTextCommitedFiles(std::shared_ptr<Log> log);

        TextView(QWidget *parent);
        ~TextView();

    private:
        std::vector<QString> formattedText;        
};


#endif /* end of include guard: TEXTVIEW_H */

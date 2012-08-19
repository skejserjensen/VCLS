#include "mainwindow.hpp"

/** Using namespaces **/
using std::string;

/** Public methods **/

/** Constructor **/
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    //The logfilehandler is initialised to null, to ensure we only delete it once
    logFileHandler = nullptr;

    //Creates the layout used by the mainwindow
    windowLayout = new QGridLayout();
    this->setLayout(windowLayout);
    
    //Instansitaion of gui elements
    openFile = new QPushButton("Open File", this);
    openedFile = new QLineEdit(this);
    fileDialog = new FileDialog(this);

    listView = new ListView(this);  

    topUserTextView = new TextView(this);
    middleUserTextView = new TextView(this);
    bottumUserTextView = new TextView(this);

    //Set the differant properties of defualt widgets
    openedFile->setReadOnly(true);
    
    //Attach signals to slots
    QObject::connect(openFile, SIGNAL(clicked()), SLOT(selectAndOpenFile()));
    QObject::connect(listView, SIGNAL(itemSelectionChanged()), SLOT(setActiveText()));

    //Attah the elements to the layout and attach the layout to the mainwindow
    windowLayout->addWidget(openedFile, 0, 0, 1, 1);
    windowLayout->addWidget(openFile, 0, 1);

    windowLayout->addWidget(listView, 1, 0, -1, 1);

    windowLayout->addWidget(topUserTextView, 1, 1);
    windowLayout->addWidget(middleUserTextView, 2, 1);
    windowLayout->addWidget(bottumUserTextView, 3, 1);
}

/** Destructor **/
MainWindow::~MainWindow()
{
    if(logFileHandler != nullptr)
        delete logFileHandler;
}

/** Private slots **/
void MainWindow::selectAndOpenFile()
{
    QString filePath;
    filePath = fileDialog->getOpenFileName();

    if(logFileHandler != nullptr)
        delete logFileHandler;

    logFileHandler = new LogFileHandler(filePath.toStdString());

    //Fills the listwidget and sets the filepath to the textbox
    listView->fillList(logFileHandler->getLogData());
    openedFile->setText(filePath);

    //Formats and saves the text the three text boxes are going to display
    topUserTextView->formatTextUsers(logFileHandler->getLogData());
    middleUserTextView->formatTextWorkTime(logFileHandler->getLogData());
    bottumUserTextView->formatTextCommitedFiles(logFileHandler->getLogData());
}

void MainWindow::setActiveText()
{
    unsigned int rowSelected = listView->currentRow();

    //The displayed text is formatted doing the construction process and only needs to be set
    topUserTextView->setActiveText(rowSelected);
    middleUserTextView->setActiveText(rowSelected);
    bottumUserTextView->setActiveText(rowSelected);
}

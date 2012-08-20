#include "mainwindow.hpp"

/** Using namespaces **/
using std::string;

/** Public methods **/

/** Constructor **/
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    //The logfilehandler is initialised to null, to ensure we only delete it once
    logFileHandler = nullptr;

    //Creates the layout needed, parents are set by setlayout and addlayout
    windowLayout = new QGridLayout();
    topHbox = new QHBoxLayout();

    windowLayout->addLayout(topHbox, 0, 0, 1, 2);
    this->setLayout(windowLayout);
    
    //Instantiation of gui elements
    openFile = new QPushButton("Open File", this);
    openedFile = new QLineEdit(this);
    fileDialog = new FileDialog(this);

    listView = new ListView(this);  
    generalTextView = new TextView(this);

    topUserTextView = new TextView(this);
    middleUserTextView = new TextView(this);
    bottumUserTextView = new TextView(this);

    //Set the differant properties of defualt widgets
    openedFile->setReadOnly(true);
    
    //Attach signals to slots
    QObject::connect(openFile, SIGNAL(clicked()), SLOT(selectAndOpenFile()));
    QObject::connect(listView, SIGNAL(itemSelectionChanged()), SLOT(setActiveText()));

    //Attach the elements to the layouts 
    topHbox->addWidget(openedFile);
    topHbox->addWidget(openFile);

    windowLayout->addWidget(listView, 1, 0, 2, 1);
    windowLayout->addWidget(generalTextView, 3, 0);

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

    //Formats and saves the text the general text box are going to display
    generalTextView->formatTextGeneral(logFileHandler->getLogData());
    generalTextView->setActiveText(0);

    //Formats and saves the text the three user text boxes are going to display
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

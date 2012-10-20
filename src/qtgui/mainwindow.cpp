#include "mainwindow.hpp"

/** Using namespaces **/
using std::string;

/** Public methods **/

/** Constructor **/
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    //The logfilehandler is initialised to null, to ensure we only delete it once
    logFileHandler = nullptr;

    //Ensures that QStrings created by converting from C++ strings uses UTF-8
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    //Creates the layout needed, parents are set by setlayout and addlayout
    QGridLayout *windowLayout = new QGridLayout();
    QHBoxLayout *topHbox = new QHBoxLayout();

    QGroupBox *generalGroupBox = new QGroupBox("General Log Statistics", this); 
    QGroupBox *topUserGroupBox = new QGroupBox("General User Statistics", this); 
    QGroupBox *middleUserGroupBox = new QGroupBox("User Worktime Statistics", this); 
    QGroupBox *bottumUserGroupBox = new QGroupBox("User File Statistics", this); 
    
    //Groupboxes dont have layouts themself so an hbox is used for each
    QHBoxLayout *generalHbox = new QHBoxLayout();
    QHBoxLayout *topUserHbox = new QHBoxLayout();
    QHBoxLayout *middleUserHbox = new QHBoxLayout();
    QHBoxLayout *bottumUserHbox = new QHBoxLayout();

    //Instantiation of gui elements
    openFile = new QPushButton("Open File", this);
    openedFile = new QLineEdit(this);
    fileDialog = new QFileDialog(this);

    listView = new ListView(this);  
    generalTextView = new TextView(this);

    topUserTextView = new TextView(this);
    middleUserTextView = new TextView(this);
    bottumUserTextView = new TextView(this);

    //Set the different properties of default widgets
    openedFile->setReadOnly(true);
    
    //Attach signals to slots
    QObject::connect(openFile, SIGNAL(clicked()), SLOT(selectAndOpenFile()));
    QObject::connect(listView, SIGNAL(itemSelectionChanged()), SLOT(setActiveText()));

    //Adds layouts and widgets to the QGroupBoxses 
    generalHbox->addWidget(generalTextView);
    topUserHbox->addWidget(topUserTextView);
    middleUserHbox->addWidget(middleUserTextView);
    bottumUserHbox->addWidget(bottumUserTextView);

    generalGroupBox->setLayout(generalHbox);
    topUserGroupBox->setLayout(topUserHbox);
    middleUserGroupBox->setLayout(middleUserHbox);
    bottumUserGroupBox->setLayout(bottumUserHbox);

    //Adds the groupboxses to the grid layout 
    topHbox->addWidget(openedFile);
    topHbox->addWidget(openFile);

    windowLayout->addWidget(listView, 1, 0, 2, 1);
    windowLayout->addWidget(generalGroupBox, 3, 0);

    windowLayout->addWidget(topUserGroupBox, 1, 1);
    windowLayout->addWidget(middleUserGroupBox, 2, 1);
    windowLayout->addWidget(bottumUserGroupBox, 3, 1);

    //Adds the layout to the mainwindow
    windowLayout->addLayout(topHbox, 0, 0, 1, 2);
    this->setLayout(windowLayout);

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

    //If the user presses cancel then the method return an empty string, which the handler can't find on the file system
    if(filePath.size() == 0)
        return;

    //Ensures that the old data is deleted if a log file have already been opened.
    if(logFileHandler != nullptr)
        delete logFileHandler;

    //The logfilehandler might throw exceptions if it is unable to read the file our encounters a bug
    try
    {
        logFileHandler = new LogFileHandler(filePath.toStdString());
    }
    catch(char const* exception)
    {
        if(DEBUG)
            qDebug() << exception;
        
        //Creates a small popup with a message that the file format is unsupported    
        ErrorPopup errorPopup;
        errorPopup.exec(); 

        return;
    }

    //Fills the listwidget and sets the filepath to the text box
    listView->fillList(logFileHandler->getLogData());
    openedFile->setText(filePath);

    //Formats and saves the text the general text box are going to display
    generalTextView->formatTextGeneral(logFileHandler->getLogData());
    generalTextView->setActiveText(0);

    //Clears the user specific text boxes so they are empty before a user is selected
    topUserTextView->clear();
    middleUserTextView->clear();
    bottumUserTextView->clear();

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

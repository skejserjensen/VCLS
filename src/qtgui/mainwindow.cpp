#include "mainwindow.hpp"

/** Using namespaces **/
using std::string;

/** Public methods **/

/** Constructor **/
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
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
}

/** Private slots **/
void MainWindow::selectAndOpenFile()
{
    QString fileName;
    fileName = fileDialog->getOpenFileName();
    openedFile->setText(fileName);
}

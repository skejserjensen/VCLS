#include "mainwindow.hpp"

/** Using namespaces **/
using std::string;

/** Public methods **/

/** Constructor **/
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    //Instansitaion of gui elements    
    openFile = new QPushButton("Open File", this);
    openedFile = new QLineEdit(this);

    fileDialog = new FileDialog(this);

    windowLayout = new QGridLayout();

    //Set the differant properties of defualt widgets
    openedFile->setReadOnly(true);
    
    //Attach signals to slots
    QObject::connect(openFile, SIGNAL(clicked()), SLOT(selectAndOpenFile()));

    //Attah the elements to the layout and attach the layout to the mainwindow
    windowLayout->addWidget(openedFile, 0, 0);
    windowLayout->addWidget(openFile, 0, 1);
    this->setLayout(windowLayout);
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

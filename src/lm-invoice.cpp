#include "lm-invoice.h"
#include "dialogs/SettingsDialog.h"

#include <iostream>
#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QWidget>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QFrame>
#include <QtGui/QMessageBox>
#include <QCloseEvent>
#include <QFileDialog>
#include <QtGui/QTableWidgetItem>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QHash>
#include <QSettings>

void lm_invoice::closing() {
  qDebug() << "In about to quit";
}


/***
 *** INITIALIZE LAYOUTS AND MENUS
 */

void lm_invoice::createLayout() {
  root = new QFrame(/*parent =*/ 0);
  this->setCentralWidget(root);  
  gridLayout = new QGridLayout(root);  
  gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
  gridLayout->setHorizontalSpacing(0);
  gridLayout->setContentsMargins(0, 0, 0, 0);
  /* set up the table*/
  tableWidget = new QTableWidget(root);
  tableWidget->setColumnCount(7);
  tableWidget->setSortingEnabled(true); //enable sorting
  QTableWidgetItem *col1 = new QTableWidgetItem();
  col1 -> setText("First Name");
  QTableWidgetItem *col2 = new QTableWidgetItem();
  col2 -> setText("Last Name");
  QTableWidgetItem *col3 = new QTableWidgetItem();
  col3 -> setText("Street");
  QTableWidgetItem *col4 = new QTableWidgetItem();
  col4 -> setText("Post Code");
  QTableWidgetItem *col5 = new QTableWidgetItem();
  col5 -> setText("Phone");
  QTableWidgetItem *col6 = new QTableWidgetItem();
  col6 -> setText("Birthday");
  QTableWidgetItem *col7 = new QTableWidgetItem();
  col7 -> setText("Email");  
  tableWidget->setHorizontalHeaderItem(0,col1);
  tableWidget->setHorizontalHeaderItem(1,col2);
  tableWidget->setHorizontalHeaderItem(2,col3);
  tableWidget->setHorizontalHeaderItem(3,col4);
  tableWidget->setHorizontalHeaderItem(4,col5);
  tableWidget->setHorizontalHeaderItem(5,col6);
  tableWidget->setHorizontalHeaderItem(6,col7);
  tableWidget->setLayoutDirection(Qt::LeftToRight);
  tableWidget->setFrameShadow(QFrame::Plain);  
  /* add the table to the grid layout*/
  gridLayout->addWidget(tableWidget, 0, 0);
  /* add the push burron*/
  pushButton = new QPushButton(root);
  pushButton -> setText("Generate");
  connect(pushButton,SIGNAL(clicked()),this,SLOT(genButtonPressed()));
  gridLayout->addWidget(pushButton, 0, 1); 
  
}

void lm_invoice::createToolBars() {
 /*create the menubar, menus and the toolbar*/
  menuBar = new QMenuBar(this);
  //
  menuFile = new QMenu(menuBar);
  menuFile->setTitle("File");
  menuFile->addAction(openAct);
  menuFile->addAction(saveAct);  
  //
  menuSettings = new QMenu(menuBar);
  menuSettings->setTitle("Settings");
  menuSettings->addAction(openSettingsDialogAct);
  //
  menuHelp = new QMenu(menuBar);
  menuHelp->setTitle("Help");
  menuHelp->addAction(aboutAct);
  //
  menuBar->addMenu(menuFile);
  menuBar->addMenu(menuSettings);
  menuBar->addMenu(menuHelp);
  this->setMenuBar(menuBar);
  //
  mainToolBar = new QToolBar(this);
  mainToolBar->addAction(openAct);
  mainToolBar->addAction(saveAct);
  mainToolBar->addAction(openSettingsDialogAct);
  this->addToolBar(mainToolBar);
  
}

void lm_invoice::createActions() {
  openAct = new QAction(tr("&Open"),/*parent=*/this);
  openAct->setShortcut(QKeySequence::Open);
  openAct->setToolTip("Open membership file");
  openAct->setIcon(QIcon("../resources/icons/open.png"));
  connect(openAct, SIGNAL(triggered()), this, SLOT(showFileDialog()));
  //
  saveAct = new QAction(tr("&Save"),/*parent=*/this);
  saveAct->setShortcut(QKeySequence::Save);
  saveAct->setIcon(QIcon("../resources/icons/save.png"));
  saveAct->setToolTip("Save changes to membership file");
  saveAct->setEnabled(false); //wait until changes have been made
  connect(saveAct, SIGNAL(triggered()), this, SLOT(saveMembFile()));
  //
  openSettingsDialogAct = new QAction(tr("&Configure InvoiceGenerator"),/*parent=*/this);
  //loadLatexTemaplateAct->setShortcut(QKeySequence::);
  openSettingsDialogAct->setIcon(QIcon("../resources/icons/settings.png"));
  openSettingsDialogAct->setToolTip("Configure InvoiceGenerator");
  connect(openSettingsDialogAct, SIGNAL(triggered()), this, SLOT(openSettingsDialog()));
  //
  aboutAct = new QAction(tr("&About"),/*parent=*/this);
  aboutAct->setStatusTip("Who did this?");
  connect(aboutAct, SIGNAL(triggered()), this, SLOT(showAbout())); 
}
/********/

/***
 *** SLOTS 
 */
void lm_invoice::showFileDialog() {
  return openMembFile(QFileDialog::getOpenFileName(this));
}

void lm_invoice::saveMembFile() {
  std::cout<<"Save"<<std::endl;
}

void lm_invoice::openSettingsDialog() {  
  //reuse previous dialogs if any
  if (!sd)
    sd=new SettingsDialog(root);
  //this is a blocking call
  QDialog::DialogCode rv = sd->showDialog();  
  std::cout<<"Configure InvoiceGenerator"<<std::endl;  
}

void lm_invoice::showAbout() {
  QMessageBox::about(this, tr("About Application"),
		     tr("The <b>Application</b> example demonstrates how to "
		"write modern GUI applications using Qt, with a menu bar, "
               "toolbars, and a status bar."));

  std::cout<<"Who did this?"<<std::endl;  
}

void lm_invoice::genButtonPressed() {
  std::cout<<"Generate"<<std::endl;
}
/*******/

/***
 *** CORE FUNCTIONS
 */
void lm_invoice::openMembFile(QString filename) {
  if (!filename.isEmpty()) {
    //load the csv file    
    std::cout<<filename.toStdString()<<std::endl;
    membershipFile = new QFile(filename);
    if (membershipFile->open(QIODevice::ReadOnly)) {
    //file opened successfully
      QList<QByteArray> wordList;
      while (!membershipFile->atEnd()) {
	QByteArray line = membershipFile->readLine();
	wordList = line.split('<');
	QHash<QString, QTableWidgetItem *> newrow;
	//first name
	newrow["FirstName"]=new QTableWidgetItem(tr("%1").arg(QString(wordList[0])));
	//last name
	newrow["LastName"]=new QTableWidgetItem(tr("%1").arg(QString(wordList[1])));
	//street
	newrow["Street"]=new QTableWidgetItem(tr("%1").arg(QString(wordList[2])));
	//post code
	newrow["PostCode"]=new QTableWidgetItem(tr("%1").arg(QString(wordList[3])));
	//phone
	newrow["Phone"]=new QTableWidgetItem(tr("%1").arg(QString(wordList[4])));
	//birth date
	newrow["BirthDate"]=new QTableWidgetItem(tr("%1").arg(QString(wordList[5])));
	//email
	newrow["Email"]=new QTableWidgetItem(tr("%1").arg(QString(wordList[6])));
	this->addTableRow(newrow);
      }
    }
    else {
      qDebug() << membershipFile->errorString();
    // TODO handle this exception      
    }
    membershipFile->close();
  }
  qDebug() << "Open";
}

void lm_invoice::addTableRow(QHash<QString, QTableWidgetItem* > row) {
  if (row.size() > 0) {
    tableWidget->insertRow(tableWidget->rowCount());
    tableWidget->setItem(/*row=*/tableWidget->rowCount()-1,/*column=*/0,row["FirstName"]);
    tableWidget->setItem(/*row=*/tableWidget->rowCount()-1,/*column=*/1,row["LastName"]);
    tableWidget->setItem(/*row=*/tableWidget->rowCount()-1,/*column=*/2,row["Street"]);
    tableWidget->setItem(/*row=*/tableWidget->rowCount()-1,/*column=*/3,row["PostCode"]);
    tableWidget->setItem(/*row=*/tableWidget->rowCount()-1,/*column=*/4,row["Phone"]);
    tableWidget->setItem(/*row=*/tableWidget->rowCount()-1,/*column=*/5,row["BirthDate"]);
    tableWidget->setItem(/*row=*/tableWidget->rowCount()-1,/*column=*/6,row["Email"]);
  }
  else {
    //TODO the function should have never been called in this case
  }
}

void lm_invoice::closeEvent(QCloseEvent *event) {
  if (maybeSave()) {
    event->accept();
  } 
  else {
    event->ignore();
  }
}

/*******/

/***
 *** UTILITY FUNCTIONS
 */
void lm_invoice::writeSettings() {
    //save any changes to the location of the membership file 
    //and the latex template as new settings
    QSettings settings;
    //make sure files have been loaded
    if (membershipFile!=0 || latexTemplate!=0) {
      settings.beginGroup("MainFiles");
      if (membershipFile) 
	settings.setValue("membership file",membershipFile->fileName());
      if (latexTemplate)
	settings.setValue("latex template",latexTemplate->fileName());
      settings.endGroup();
    }
}

void lm_invoice::readSettings() {
  QSettings settings;
  settings.beginGroup("MainFiles");
  QString membFile = settings.value("membership file","../resources/files/Mitgliedschaft 2015.csv").toString();
   this->openMembFile(membFile);
  settings.endGroup();
  
}
/*******/

bool lm_invoice::maybeSave() {
  QMessageBox::StandardButton ret;
  ret = QMessageBox::warning(this, tr("Application"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
  if (ret == QMessageBox::Save) {
    writeSettings();
    return true;
  }
  else if (ret == QMessageBox::Cancel)
    return false;  
  return true;
}

/*******/

/***
 *** CONSTRUCTORS AND DESTRUCTOR 
 */
lm_invoice::lm_invoice() {
    //make sure pointers are properly initialized
    membershipFile=0;latexTemplate=0;sd=0;
    //init gui elements
    createActions();  
    createLayout();
    createToolBars();
    //
    readSettings();

}

lm_invoice::~lm_invoice() {  
  qDebug() << "In ~lm_invoice";
  if (membershipFile)
    delete membershipFile;
  if (latexTemplate)
    delete latexTemplate;  
  if (sd) {
    qDebug() << sd;
    delete sd;
  }
  qDebug() << "Out of ~lm_invoice";
}
/*******/
//#include "lm-invoice.moc"

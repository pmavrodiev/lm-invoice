#include "lm-invoice.h"

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

/*
void lm_invoice::closeEvent(QCloseEvent *event) {
  if (maybeSave()) {    
    event->accept();
  } 
  else {
    event->ignore();
  }  
}
*/

bool lm_invoice::maybeSave() {
  QMessageBox::StandardButton ret;
  ret = QMessageBox::warning(this, tr("Application"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
  if (ret == QMessageBox::Save)
    return true;
  else if (ret == QMessageBox::Cancel)
    return false;  
  return true;
}


void lm_invoice::createLayout() {
  root = new QFrame(/*parent =*/ 0);
  this->setCentralWidget(root);
  
  //gridLayoutWidget = new QWidget(centralWidget);
  gridLayout = new QGridLayout(root);  
  //gridLayout->setContentsMargins(11, 11, 11, 11);  
  gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
  gridLayout->setHorizontalSpacing(0);
  gridLayout->setContentsMargins(0, 0, 0, 0);
  /* set up the table*/
  tableWidget = new QTableWidget(root);
  tableWidget->setColumnCount(4);
  QTableWidgetItem *col1 = new QTableWidgetItem();
  col1 -> setText("First Name");
  QTableWidgetItem *col2 = new QTableWidgetItem();
  col2 -> setText("Last Name");
  QTableWidgetItem *col3 = new QTableWidgetItem();
  col3 -> setText("Address");
  QTableWidgetItem *col4 = new QTableWidgetItem();
  col4 -> setText("Email");    
  tableWidget->setHorizontalHeaderItem(0,col1);
  tableWidget->setHorizontalHeaderItem(0,col2);
  tableWidget->setHorizontalHeaderItem(0,col3);
  tableWidget->setHorizontalHeaderItem(0,col4);  
  tableWidget->setLayoutDirection(Qt::LeftToRight);
  tableWidget->setFrameShadow(QFrame::Plain);  
  /* add the table to the grid layout*/
  gridLayout->addWidget(tableWidget, 0, 0, 3, 1);
  /* add the push burron*/
  pushButton = new QPushButton(root);
  pushButton -> setText("Generate");
  gridLayout->addWidget(pushButton, 1, 0, 1, 1); 
  
}

void lm_invoice::createToolBars() {
 /*create the menubar, menus and the toolbar*/
  menuBar = new QMenuBar(this);
  //
  menuFile = new QMenu(menuBar);
  menuFile->setTitle("Menu");
  menuFile->addAction(openAct);
  menuFile->addAction(saveAct);  
  //
  menuSettings = new QMenu(menuBar);
  menuSettings->setTitle("Settings");
  menuSettings->addAction(loadLatexTemaplateAct);
  //
  menuHelp = new QMenu(menuBar);
  menuHelp->setTitle("Help");
  menuHelp->addAction(aboutAct);
  //
  this->setMenuBar(menuBar);
  mainToolBar = new QToolBar(this);
  mainToolBar->setWindowTitle(tr("Ludi Mladi"));
  this->addToolBar(Qt::TopToolBarArea,mainToolBar);
  
}

void lm_invoice::openMembFile() {
  std::cout<<"Open"<<std::endl;
}

void lm_invoice::saveMembFile() {
  std::cout<<"Save"<<std::endl;
}

void lm_invoice::loadLatexTemplate() {
  std::cout<<"Load a new latex template"<<std::endl;  
}

void lm_invoice::showAbout() {
  std::cout<<"Who did this?"<<std::endl;  
}

void lm_invoice::createActions() {
  openAct = new QAction(tr("&Open"),/*parent=*/this);
  openAct->setShortcut(QKeySequence::Open);
  openAct->setStatusTip("Open membership file");
  connect(openAct, SIGNAL(triggered()), this, SLOT(openMembFile()));
  //
  saveAct = new QAction(tr("&Save"),/*parent=*/this);
  saveAct->setShortcut(QKeySequence::Save);
  saveAct->setStatusTip("Save changes to membership file");
  connect(saveAct, SIGNAL(triggered()), this, SLOT(saveMembFile()));
  //
  loadLatexTemaplateAct = new QAction(tr("&Load Latex Template"),/*parent=*/this);
  //loadLatexTemaplateAct->setShortcut(QKeySequence::);
  loadLatexTemaplateAct->setStatusTip("Save changes to membership file");
  connect(loadLatexTemaplateAct, SIGNAL(triggered()), this, SLOT(loadLatexTemplate()));
  //
  aboutAct = new QAction(tr("&About"),/*parent=*/this);
  aboutAct->setStatusTip("Who did this?");
  connect(aboutAct, SIGNAL(triggered()), this, SLOT(showAbout())); 
}


lm_invoice::lm_invoice()
{
    createActions();  
    createLayout();
    createToolBars();
    
    
    /*
    //Create the actions in the menu
    QAction* aLoad = new QAction(this);
    QAction* aQuit = new QAction(this);
    aLoad->setText("Load members file");
    aQuit->setText( "Quit" );
    connect(aQuit, SIGNAL(triggered()), SLOT(close()) );
    //Create the main menu
    QMenuBar* mainMenu=menuBar();
    //Add the file button and populate it
    QMenu* mFile=mainMenu->addMenu("File");
    mFile->addAction(aLoad);
    mFile->addAction(aQuit);
    */
}

lm_invoice::~lm_invoice()
{}

#include "lm-invoice.moc"

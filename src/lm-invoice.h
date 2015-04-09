#ifndef lm_invoice_H
#define lm_invoice_H

#include <QtGui/QMainWindow>
#include <QList>

//forward declaration of QT components
class QAction;
class QMenu;
class QWidget;
class QGridLayout;
class QTableWidget;
class QButtonGroup;
class QHeaderView;
class QMainWindow;
class QMenuBar;
class QPushButton;
class QSpacerItem;
class QTableWidget;
class QVBoxLayout;
class QToolBar;
class QCloseEvent;
class QTableWidgetItem;
class QFile;
class SettingsDialog;
//

class lm_invoice : public QMainWindow
{
Q_OBJECT
public:
    lm_invoice();
    virtual ~lm_invoice();
    
protected:
    void closeEvent(QCloseEvent *event);
    
    
private slots:
    //Action methods
    void showFileDialog();
    void saveMembFile();
    void openSettingsDialog();
    void showAbout();
    //Push push button
    void genButtonPressed();
    void closing();

private:
    //File pointers to resource files
    QFile *membershipFile;
    QFile *latexTemplate;
    //QT elements
    QWidget *root;
    QWidget *gridLayoutWidget;
    SettingsDialog *sd;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QVBoxLayout *verticalLayout;
    QMenu* menuFile;
    QMenu* menuSettings;
    QMenu* menuHelp;
    QToolBar *mainToolBar;
    QToolBar *toolBar;   
    //QT actions
    QAction* openAct;
    QAction* saveAct;
    QAction* exitAct;
    QAction* openSettingsDialogAct;
    QAction* aboutAct;
    //UI - Initialize layout and menus
    void createActions();
    void createLayout();
    void createToolBars();
    void createStatusBar();
    //Core functionality
    void openMembFile(QString filename);    
    void addTableRow(QHash<QString, QTableWidgetItem *> row);   
    //Utility functions
    void readSettings();
    void writeSettings();
    bool maybeSave();  
    //
    
};
#endif // lm_invoice_H

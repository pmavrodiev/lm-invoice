#ifndef lm_invoice_H
#define lm_invoice_H

#include <QtGui/QMainWindow>

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


class lm_invoice : public QMainWindow
{
Q_OBJECT
public:
    lm_invoice();
    virtual ~lm_invoice();
    
//protected:
//    void closeEvent(QCloseEvent *event);
    


private:
    //QT layout elements
    QWidget *root;
    QWidget *gridLayoutWidget;
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
    //Initialize layout and menus
    void createActions();
    void createLayout();
    void createToolBars();
    void createStatusBar();
    //QT actions
    QAction* openAct;
    QAction* saveAct;
    QAction* exitAct;
    QAction* loadLatexTemaplateAct;
    QAction* aboutAct;
    //Action methods
    void openMembFile();
    void saveMembFile();
    void loadLatexTemplate();
    void showAbout();
    //
    void readSettings();
    void writeSettings();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);    
    QString curFile;

  
    
    
    
};
#endif // lm_invoice_H

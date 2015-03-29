#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QtGui/QDialog>
#include <QtGui/QWidget>

class SettingsDialog: public QDialog {
Q_OBJECT

public:
    // Returns a settings dialog. This makes sure that always only
    // a single settings dialog instance is running.
    // The dialog will be deleted automatically on close.
    static SettingsDialog *getSettingsDialog(QWidget *parent);
    // Run the dialog and wait for it to finish.
    // Returns if the changes have been applied.
    //bool execDialog(); 
    
    
//private slots:
  //void done(int);
    virtual ~SettingsDialog() {};
private:
  SettingsDialog(QWidget *parent);    
  
  //void accept();
  //void reject();
  //void apply();
  //void currentChanged(const QModelIndex &current);
  //void currentTabChanged(int);
  //void filter(const QString &text);
  
  //void createGui();
  //void showCategory(int index);
  //void showPage(Id pageId);
  //void updateEnabledTabs(Category *category, const QString &searchText);
  //void ensureCategoryWidget(Category *category);
  //void disconnectTabWidgets();
  
  
  
  
};

#endif
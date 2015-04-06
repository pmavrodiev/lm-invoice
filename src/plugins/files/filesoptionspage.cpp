#include "filesoptionspage.h"
#include "filessettings.h"
#include "ui_locationsTabWidget.h"


#include <QCoreApplication>
#include <QPointer>
#include <QSettings>

// -------------- FilesOptionsPagePrivate

class FilesOptionsPagePrivate {
public:
  FilesOptionsPagePrivate(int, const QString, const QString);
  ~FilesOptionsPagePrivate() {};
  int m_id;
  const QString m_displayName;
  const QString m_settingsGroup;
  
  FilesSettings m_value;
  FilesSettings m_lastValue;
  
  QPointer<QWidget> m_widget;
  Ui::LocationsTabWidget *m_ui;
};

FilesOptionsPagePrivate::FilesOptionsPagePrivate(int id, 
						    const QString displayName, 
						    const QString settingsGroup) {
  m_id=id;
  m_displayName=displayName;
  m_settingsGroup=settingsGroup;
  m_ui=0;
  
  bool settingsFound=false;
  
  //TODO - implement plugin manager and work with global settings
  //for now work with default settings
  QSettings *settings = new QSettings();  
  settingsFound = m_value.fromSettings(m_settingsGroup,settings);
  if (!settingsFound) {
    //TODO apply defaults
  }
  else {}//TODO
  m_lastValue=m_value;
  delete settings;
}






// -------------- FilesOptionsPage

FilesOptionsPage::FilesOptionsPage(QObject* parent): IOptionsPage(parent) {
  setCategory(QString("C.FileChooser"));
  setDisplayCategory(QCoreApplication::translate("FileChooser", "File Chooser"));
  setCategoryIcon(QLatin1String("images/category_texteditor.png"));
  
}

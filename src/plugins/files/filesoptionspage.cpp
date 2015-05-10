#include "filesoptionspage.h"
#include "filessettings.h"
#include "../../libs/pluginmanager/pluginmanager.h"
#include "../../libs/utils/pathchooser.h"
#include "ui_locationsTabWidget.h"


#include <QCoreApplication>
#include <QPointer>
#include <QSettings>

using namespace Utils;

// -------------- FilesOptionsPagePrivate

class FilesOptionsPagePrivate {
public:
  FilesOptionsPagePrivate(int, const QString, const QString);
  ~FilesOptionsPagePrivate() {};
  int m_id;
  QString m_displayName;
  QString m_settingsGroup;
  
  FilesSettings m_value;
  FilesSettings m_lastValue;
  
  QPointer<QWidget> m_widget;
  Ui::LocationsTabWidget *m_ui;
};

FilesOptionsPagePrivate::FilesOptionsPagePrivate(int id, 
						    QString displayName, 
						    QString settingsGroup) {
  m_id=id;
  m_displayName=displayName;
  m_settingsGroup=settingsGroup;
  m_ui=0;
  
  bool settingsFound=false;
  
  QSettings *settings = ExtensionSystem::PluginManager::getGlobalSettings();
  settingsFound = m_value.fromSettings(m_settingsGroup,settings);
  if (!settingsFound) {
    m_value.setLatexTemplate("../../../resources/files/Mitgliedschaft 2015");
    m_value.setMembersTemplate("../../../resources/files/latex.template");
  }
  m_lastValue=m_value;
}


// -------------- FilesOptionsPage



FilesOptionsPage::FilesOptionsPage(int id,QObject* parent): IOptionsPage(parent,id) {
  setCategory(QString("C.FileChooser"));
  setDisplayCategory(QCoreApplication::translate("FileChooser", "File Chooser"));
  setCategoryIcon(QLatin1String("images/category_texteditor.png"));
  
  d_ptr = new FilesOptionsPagePrivate(id,tr("File paths"),this->category());
}


FilesOptionsPage::~FilesOptionsPage() {
  if (d_ptr)
    delete d_ptr;
}

QWidget* FilesOptionsPage::widget() {
  if (!d_ptr->m_widget) {
    d_ptr->m_widget = new QWidget;
    d_ptr->m_ui = new Ui::LocationsTabWidget;
    //the argument to setupUi is a pointer to the widget
    //hosting the content of FilesOptionsPage.
    //setupUi will then position all GUI elements in that widget
    d_ptr->m_ui->setupUi(d_ptr->m_widget);
    //connect signals
    connect(d_ptr->m_ui->latextemplateChooser,
	    SIGNAL(pathChanged(const QString )),
	    &d_ptr->m_value,
	    SLOT(setLatexTemplate(const QString &))
 	  );
    connect(d_ptr->m_ui->membersFileChooser,
	    SIGNAL(pathChanged(const QString &)),
	    &d_ptr->m_value,
	    SLOT(setMembersTemplate(const QString &))
 	  );
    d_ptr->m_lastValue=d_ptr->m_value;
  }
  return d_ptr->m_widget;
}

void FilesOptionsPage::apply() {
  if (!d_ptr->m_ui) //page was never shown
    return;
  saveSettings();  
}

void FilesOptionsPage::saveSettings() {
  if (d_ptr->m_value != d_ptr->m_lastValue) {
    d_ptr->m_value = d_ptr->m_lastValue;
    d_ptr->m_value.toSettings(d_ptr->m_settingsGroup,ExtensionSystem::PluginManager::getGlobalSettings());
  }
}

void FilesOptionsPage::finish() {
  delete d_ptr->m_widget;
  if (!d_ptr->m_ui) // page was never shown
        return;
  delete d_ptr->m_ui;
  d_ptr->m_ui = 0;
  // If changes were applied, these are equal. Otherwise restores last value.
  d_ptr->m_value = d_ptr->m_lastValue;
}

FilesSettings& FilesOptionsPage::filesSettings() {
  FilesSettings& rv = d_ptr->m_value;
  return rv;
}



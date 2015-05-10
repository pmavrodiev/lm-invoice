#include "files.h"
#include "filesoptionspage.h"
#include "filessettings.h"
#include <QDebug>

#include "../../libs/pluginmanager/pluginmanager.h"


#include <QApplication>


class FilesPrivate {
public:
  FilesOptionsPage *m_filesoptionpage;
  
  FilesPrivate() {m_filesoptionpage=0;}
  ~FilesPrivate() {
    if (m_filesoptionpage)
      delete m_filesoptionpage;
    m_filesoptionpage=0;
  }
};

//static FilesPrivate *d = 0;
//static Files *m_instance = 0;

Files::Files(QObject* parent): QObject(parent) {
  d = new FilesPrivate();
  d->m_filesoptionpage = new FilesOptionsPage(/*id=*/10,/*parent=*/this);
  ExtensionSystem::PluginManager::addObject(d->m_filesoptionpage);
  
  connect(d->m_filesoptionpage, SIGNAL(changed(const FilesSettings &)),
	  this,SLOT(fileSettingsChanged(const FilesSettings&)));
}

Files::~Files() {
  ExtensionSystem::PluginManager::removeObject(d->m_filesoptionpage);
  if (d)
    delete d;  
}

void Files::fileSettingsChanged(const FilesSettings&) {
  qDebug() << "Files::fileSettingsChanged";
}

//FileSettings &Files::fileSettings() {
// return d->m_filesoptionpage->filesSettings();
//}





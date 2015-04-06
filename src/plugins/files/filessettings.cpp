#include "filessettings.h"

#include <QCoreApplication>
#include <QFile>
#include <QSettings>

void FilesSettings::clear() {
  m_latextemplate=QString::null;
  m_membersfile=QString::null;
}


void FilesSettings::toSettings(const QString& category, QSettings* s) {
  s->beginGroup(category);
  s->setValue(QLatin1String("LaTeX Template"),m_latextemplate);
  s->setValue(QLatin1String("Members Template"),m_membersfile);
  s->endGroup(category);
}

bool FilesSettings::fromSettings(const QString& category, const QSettings* s) {
  clear();
  
  //can we find the settings category we ask for?
  if (!s->childGroups().contains(category))
    return false;
  
  QString group = category;
  group += QLatin1String("/");
  
  m_latextemplate=s->value(group+QLatin1String("LaTeX Template")).toString();
  m_membersfile=s->value(group+QLatin1String("Members Template")).toString();  
  return true;  
}

bool FilesSettings::equals(const FilesSettings& fs) const {
  return m_latextemplate == m_membersfile;
}





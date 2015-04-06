#ifndef FILESSETTINGS_H
#define FILESSETTINGS_H

#include <QString>

class QSettings;


class FilesSettings {
public:
  FilesSettings() {
    m_latextemplate=QString::null;
    m_membersfile=QString::null;
  };
  void clear();
  void toSettings(const QString &category, QSettings *s);
  bool fromSettings(const QString &category,
		      const QSettings *s);
  void setLatexTemplate(const QString &file) {m_latextemplate=file;}
  void setMembersTemplate(const QString &file) {m_membersfile=file;}
  bool equals(const FilesSettings &fs) const;
  
  QString latexTemplate() const {return m_latextemplate;};
  QString membersTemplate() const {return m_membersfile;};
  
private:
  QString m_latextemplate;
  QString m_membersfile; 
};

inline bool operator==(const FilesSettings &f1, const FilesSettings &f2) { return f1.equals(f2); }
inline bool operator!=(const FilesSettings &f1, const FilesSettings &f2) { return !f1.equals(f2); }

#endif FILESSETTINGS_H
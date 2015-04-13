#ifndef FILESSETTINGS_H
#define FILESSETTINGS_H

#include <QString>
#include <QObject>

class QSettings;


class FilesSettings: public QObject {
Q_OBJECT
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
  FilesSettings &operator= (const FilesSettings &f) {
    m_latextemplate=f.m_latextemplate;
    m_membersfile=f.m_membersfile;
    return *this;
  };
  
public slots:
  QString latexTemplate() const {return m_latextemplate;};
  QString membersTemplate() const {return m_membersfile;};
private:
  QString m_latextemplate;
  QString m_membersfile; 
};

inline bool operator==(const FilesSettings &f1, const FilesSettings &f2) { return f1.equals(f2); }
inline bool operator!=(const FilesSettings &f1, const FilesSettings &f2) { return !f1.equals(f2); }



#endif 
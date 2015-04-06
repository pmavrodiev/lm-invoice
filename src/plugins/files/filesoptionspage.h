#ifndef FILESOPTIONSPAGE_H
#define FILESOPTIONSPAGE_H

#include <qglobal.h>
#include "../../dialogs/ioptionspage.h"

#if defined(FILES_LIBRARY)
#  define FILES_EXPORT Q_DECL_EXPORT
#else
#  define FILES_EXPORT Q_DECL_IMPORT
#endif

class FilesOptionsPagePrivate; //defined in filesoptionspage.cpp
class FilesSettings;


/**
 * An abstract options page in the Text Editor category.
 */
class FILES_EXPORT FilesOptionsPage : public IOptionsPage
{
    Q_OBJECT

public:
    explicit FilesOptionsPage(int id, QObject *parent = 0);
    ~FilesOptionsPage();
    
    QWidget *widget();
    void apply();
    void finish();
    
    void saveSettings();
    
    const FilesSettings &filesSettings() const; //TODO
    
signals:
  void changed(const FilesSettings&);
  
private slots:
  void delayedChange();
  void latexTemplateChanged();
  void membersTemplateChanged();
  
  FilesOptionsPagePrivate *d_ptr;
};



#endif // FILESOPTIONSPAGE_H

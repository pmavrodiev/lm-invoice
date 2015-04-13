#ifndef FILES_H
#define FILES_H

#include <QObject>

class FilesSettings;
class FilesPrivate;

/**
 * This class provides a central place for basic Location chooser settings.
 */

class Files : public QObject{
  
  Q_OBJECT
public:
  explicit Files(QObject *parent);
  ~Files();
  //FileSettings &fileSettings();
private:
  FilesPrivate *d;
public slots:
  void fileSettingsChanged(const FilesSettings &);
  
  
};

#endif //FILES_H
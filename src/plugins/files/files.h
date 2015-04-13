#ifndef FILES_H
#define FILES_H

#include <QObject>

class FileSettings;
class FilesPrivate;

/**
 * This class provides a central place for basic Location chooser settings.
 */

class Files : public QObject{
  
  Q_OBJECT
public:
  explicit Files(QObject *parent);
  ~Files();
  const FileSettings &fileSettings();
private:
  FilesPrivate *d;
signals:
  void fileSettingsChanged(const FileSettings &);
  
  
};

#endif //FILES_H
#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QStringList>
#include <qglobal.h>
#include <QReadWriteLock>
#include <QSettings>

class QTextStream;

namespace ExtensionSystem {

//TODO move in separate header file
class PluginSpec {
public:
  enum State {Invalid, Read, Resolved, Loaded, Initialized, Running, Stopped, Deleted};
  explicit PluginSpec(QString n) {
    name=n;
    is_enabledByDefault=true;
    state=Running;
  }
  ~PluginSpec();
  QString getName() const {return name;};
  bool isEnabledByDefault() const {return is_enabledByDefault;};
  bool setName(const QString n) {name=n;}
private:
  QString name;
  bool is_enabledByDefault;
  State state;
};
  

class PluginManager: public QObject {
    Q_OBJECT
 public:
   static PluginManager *instance();
   
   PluginManager();
   ~PluginManager();
   
   //Object pool operations
   static void addObject(QObject *obj);
   static void removeObject(QObject *obj);
   static QList<QObject *> allObjects() {return PluginManager::instance()->m_allObjects;};
   static QReadWriteLock *listLock() {return &PluginManager::instance()->m_lock;};
   //cast only
   template <typename T> static QList<T *> getObjects() {
        QReadLocker lock(listLock());
        QList<T *> results;
        QList<QObject *> all = allObjects();
        foreach (QObject *obj, all) {
            T *result = qobject_cast<T *>(obj);
            if (result)
                results += result;
        }
        return results;
    }
    //cast and predicate
    template <typename T, typename Predicate>
    static QList<T *> getObjects(Predicate predicate) {
        QReadLocker lock(listLock());
        QList<T *> results;
        QList<QObject *> all = allObjects();
        foreach (QObject *obj, all) {
            T *result = qobject_cast<T *>(obj);
            if (result && predicate(result))
                results += result;
        }
        return results;
    }
    //cast only
    template <typename T> static T *getObject() {
        QReadLocker lock(listLock());
        QList<QObject *> all = allObjects();
        foreach (QObject *obj, all) {
            if (T *result = qobject_cast<T *>(obj))
                return result;
        }
        return 0;
    }
    //predicate only
    template <typename T, typename Predicate> static T *getObject(Predicate predicate) {
        QReadLocker lock(listLock());
        QList<QObject *> all = allObjects();
        foreach (QObject *obj, all) {
            if (T *result = qobject_cast<T *>(obj))
                if (predicate(result))
                    return result;
        }
        return 0;
    }
    /*!
    Retrieves one object with a name from the object pool.
    addObject()	
    */
    static QObject *getObjectByName(const QString &name);
    /*!
    Retrieves one object inheriting a class with a className from the object
    pool.
    */
    static QObject *getObjectByClassName(const QString &className);
    
    // Plugin operations
    //static void loadPlugins();
    //static QStringList pluginPaths();
    //static void setPluginPaths(const QStringList &paths);
    //static QString pluginIID();
    //static void setPluginIID(const QString &iid);
    static QList<PluginSpec *> plugins();
    //static QHash<QString, PluginCollection *> pluginCollections();
    //static bool hasError();
    //static QSet<PluginSpec *> pluginsRequiringPlugin(PluginSpec *spec);
    //static QSet<PluginSpec *> pluginsRequiredByPlugin(PluginSpec *spec);

    // Settings
    //static void setSettings(QSettings *settings);
    //static QSettings *getSettings() {return settings;};
    static void setGlobalSettings(QSettings *settings);
    static QSettings *getGlobalSettings() {return PluginManager::instance()->m_globalSettings;};
    static void writeGlobalSettings();
    static void saveGlobalSettings() { PluginManager::instance()->m_globalSettings->sync();};

    static QList<PluginSpec *> plugings() {return PluginManager::instance()->pluginSpecs;};
    static QString platformName();
    
    
 private:
    QList<QObject *> m_allObjects;
    QReadWriteLock m_lock;
    QSettings *m_globalSettings;
    QList<PluginSpec *> pluginSpecs;
    
 signals:
    void objectAdded(QObject *obj);
    void objectRemoved(QObject *obj);
    //void aboutToRemoveObject(QObject *obj);

    //void pluginsChanged();
    //void initializationDone();
 public slots:
    //void remoteArguments(const QString &serializedArguments, QObject *socket);
    //void shutdown();
    
 }; 
  
};

#endif
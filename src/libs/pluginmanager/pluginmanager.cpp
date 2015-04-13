#include "pluginmanager.h"

#include <QTextStream>
#include <QSettings>
#include <functional>
#include <QDebug>
#include <QFile>

#include "../utils/algorithm.h"
#include "../utils/qtcassert.h"

using namespace ExtensionSystem;

const char C_DEFAULTENABLED[] = "Plugins/DefaultEnabled";

static PluginManager *m_instance=0;

PluginManager::PluginManager(): QObject() {
  m_globalSettings=0;
  m_instance=this;
}

PluginManager::~PluginManager() {
  if (m_globalSettings)
    delete m_globalSettings;
}

PluginManager* PluginManager::instance() {
  return m_instance;
}


QObject *PluginManager::getObjectByName(const QString &name) {
    QReadLocker lock(&PluginManager::instance()->m_lock);
    QList<QObject *> all = allObjects();
    foreach (QObject *obj, all) {
        if (obj->objectName() == name)
            return obj;
    }
    return 0;
}

QObject *PluginManager::getObjectByClassName(const QString &className) {
    const QByteArray ba = className.toUtf8();
    QReadLocker lock(&PluginManager::instance()->m_lock);
    QList<QObject *> all = allObjects();
    foreach (QObject *obj, all) {
        if (obj->inherits(ba.constData()))
            return obj;
    }
    return 0;
}

void PluginManager::addObject(QObject *obj) {
    if (obj == 0) {
       qWarning() << "PluginManager::addObject(): trying to add null object";
       return;
    }
    if (PluginManager::instance()->m_allObjects.contains(obj)) {
       qWarning() << "PluginManagerPrivate::addObject(): trying to add duplicate object";
       return;
    }
    PluginManager::instance()->m_allObjects.append(obj);
    emit instance()->objectAdded(obj);
}

void PluginManager::removeObject(QObject *obj) {
    if (obj == 0) {
      qWarning() << "PluginManager::removeObject(): trying to remove null object";
      return;
    }
    if (!PluginManager::instance()->m_allObjects.contains(obj)) {
       qWarning() << "PluginManager::removeObject(): object not in list:"
            << obj << obj->objectName();
        return;
    }
    PluginManager::instance()->m_allObjects.removeAll(obj);
    emit instance()->objectRemoved(obj);
}

void PluginManager::setGlobalSettings(QSettings *s) {
  if (PluginManager::instance()->m_globalSettings)
    delete PluginManager::instance()->m_globalSettings;
  PluginManager::instance()->m_globalSettings=s;
  //if (m_globalSettings)
    //m_globalSettings->setParent(this);
}

void PluginManager::writeGlobalSettings() {
    if (!PluginManager::instance()->m_globalSettings)
      return;    
    QStringList defaultEnabledPlugins;
    
    foreach (PluginSpec *spec, PluginManager::instance()->pluginSpecs) {
      defaultEnabledPlugins.append(spec->getName());      
    }
    PluginManager::instance()->m_globalSettings->setValue(QLatin1String(C_DEFAULTENABLED),defaultEnabledPlugins);
}



static inline QString getPlatformName() {
#if defined(Q_OS_MAC)
    if (QSysInfo::MacintoshVersion >= QSysInfo::MV_10_0) {
        QString result = QLatin1String("OS X");
        result += QLatin1String(" 10.") + QString::number(QSysInfo::MacintoshVersion - QSysInfo::MV_10_0);
        return result;
    } else {
        return QLatin1String("Mac OS");
    }
#elif defined(Q_OS_UNIX)
    QString base;
#  ifdef Q_OS_LINUX
    base = QLatin1String("Linux");
#  else
    base = QLatin1String("Unix");
#  endif // Q_OS_LINUX
    QFile osReleaseFile(QLatin1String("/etc/os-release")); // Newer Linuxes
    if (osReleaseFile.open(QIODevice::ReadOnly)) {
        QString name;
        QString version;
        forever {
            const QByteArray line = osReleaseFile.readLine();
            if (line.isEmpty())
                break;
            if (line.startsWith("NAME=\""))
                name = QString::fromLatin1(line.mid(6, line.size() - 8)).trimmed();
            if (line.startsWith("VERSION_ID=\""))
                version = QString::fromLatin1(line.mid(12, line.size() - 14)).trimmed();
        }
        if (!name.isEmpty()) {
            if (!version.isEmpty())
                name += QLatin1Char(' ') + version;
            return base + QLatin1String(" (") + name + QLatin1Char(')');
        }
    }
    return base;
#elif defined(Q_OS_WIN)
    QString result = QLatin1String("Windows");
    switch (QSysInfo::WindowsVersion) {
    case QSysInfo::WV_XP:
        result += QLatin1String(" XP");
        break;
    case QSysInfo::WV_2003:
        result += QLatin1String(" 2003");
        break;
    case QSysInfo::WV_VISTA:
        result += QLatin1String(" Vista");
        break;
    case QSysInfo::WV_WINDOWS7:
        result += QLatin1String(" 7");
        break;
    default:
        break;
    }
    if (QSysInfo::WindowsVersion >= QSysInfo::WV_WINDOWS8)
        result += QLatin1String(" 8");
    return result;
#endif // Q_OS_WIN
    return QLatin1String("Unknown");
}



QString PluginManager::platformName() {
    static const QString result = getPlatformName();
    return result;
}

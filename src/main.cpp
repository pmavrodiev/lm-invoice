#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QSettings>

#include "lm-invoice.h"
#include "libs/pluginmanager/pluginmanager.h"

const char SHARE_PATH[] = "./";
const char ORGANIZATION[] = "Ludi Mladi";
const char APPLICATION[] = "Invoice Generator";

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    //Init the pluginmanager
    // Must be done before any QSettings class is created
    QSettings::setPath(QSettings::IniFormat, QSettings::SystemScope,
                       QCoreApplication::applicationDirPath() + QLatin1String(SHARE_PATH));
    QSettings::setDefaultFormat(QSettings::IniFormat);
    //
    ExtensionSystem::PluginManager pluginmanager;
    // plugin manager takes control of this settings object
    QSettings *globalSettings = new QSettings(QSettings::IniFormat, QSettings::SystemScope,
                                              QLatin1String(ORGANIZATION),
                                              QLatin1String(APPLICATION));
    ExtensionSystem::PluginManager::setGlobalSettings(globalSettings);
    //
    lm_invoice foo;
    /* 
     * resize the main application window to pleasing dimensions
     * dependent on the size of the main screen
    */
    QDesktopWidget desktop; //used only to get screen information
    QRect mainScreenSize=desktop.availableGeometry(desktop.primaryScreen());
    double scalingFactor=0.7; //70% of main screen size
    foo.setFixedSize(scalingFactor*mainScreenSize.width(),scalingFactor*mainScreenSize.height());
    foo.show();
    QObject::connect(&app,SIGNAL(aboutToQuit()),&foo,SLOT(closing()));
    return app.exec();
}

#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include "lm-invoice.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    //used in QSettings
    app.setOrganizationName("Ludi Mladi");
    app.setApplicationName("Invoice generator");
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
    return app.exec();
}

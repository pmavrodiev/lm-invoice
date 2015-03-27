#include <QtGui/QApplication>
#include "lm-invoice.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    lm_invoice foo;
    foo.show();
    return app.exec();
}

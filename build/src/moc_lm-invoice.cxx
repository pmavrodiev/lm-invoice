/****************************************************************************
** Meta object code from reading C++ file 'lm-invoice.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/lm-invoice.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lm-invoice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_lm_invoice[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      29,   11,   11,   11, 0x08,
      44,   11,   11,   11, 0x08,
      65,   11,   11,   11, 0x08,
      77,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_lm_invoice[] = {
    "lm_invoice\0\0showFileDialog()\0"
    "saveMembFile()\0openSettingsDialog()\0"
    "showAbout()\0genButtonPressed()\0"
};

void lm_invoice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        lm_invoice *_t = static_cast<lm_invoice *>(_o);
        switch (_id) {
        case 0: _t->showFileDialog(); break;
        case 1: _t->saveMembFile(); break;
        case 2: _t->openSettingsDialog(); break;
        case 3: _t->showAbout(); break;
        case 4: _t->genButtonPressed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData lm_invoice::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject lm_invoice::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_lm_invoice,
      qt_meta_data_lm_invoice, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &lm_invoice::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *lm_invoice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *lm_invoice::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_lm_invoice))
        return static_cast<void*>(const_cast< lm_invoice*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int lm_invoice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
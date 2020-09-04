/****************************************************************************
** Meta object code from reading C++ file 'hydraulics-channel-gvf.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/hydraulics-channel-gvf.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hydraulics-channel-gvf.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_hydraulics_channel_gvf_t {
    QByteArrayData data[64];
    char stringdata0[725];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_hydraulics_channel_gvf_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_hydraulics_channel_gvf_t qt_meta_stringdata_hydraulics_channel_gvf = {
    {
QT_MOC_LITERAL(0, 0, 22), // "hydraulics_channel_gvf"
QT_MOC_LITERAL(1, 23, 12), // "SI_unite_HAF"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 23), // "copy_table_in_Clipboard"
QT_MOC_LITERAL(4, 61, 13), // "loop_step_haf"
QT_MOC_LITERAL(5, 75, 7), // "double*"
QT_MOC_LITERAL(6, 83, 2), // "So"
QT_MOC_LITERAL(7, 86, 1), // "n"
QT_MOC_LITERAL(8, 88, 1), // "Q"
QT_MOC_LITERAL(9, 90, 2), // "Cm"
QT_MOC_LITERAL(10, 93, 1), // "g"
QT_MOC_LITERAL(11, 95, 1), // "y"
QT_MOC_LITERAL(12, 97, 1), // "B"
QT_MOC_LITERAL(13, 99, 2), // "SS"
QT_MOC_LITERAL(14, 102, 1), // "z"
QT_MOC_LITERAL(15, 104, 1), // "x"
QT_MOC_LITERAL(16, 106, 8), // "stepdist"
QT_MOC_LITERAL(17, 115, 9), // "totaldist"
QT_MOC_LITERAL(18, 125, 17), // "standard_step_haf"
QT_MOC_LITERAL(19, 143, 12), // "channel_geom"
QT_MOC_LITERAL(20, 156, 25), // "std::unique_ptr<double[]>"
QT_MOC_LITERAL(21, 182, 10), // "conveyance"
QT_MOC_LITERAL(22, 193, 1), // "A"
QT_MOC_LITERAL(23, 195, 1), // "R"
QT_MOC_LITERAL(24, 197, 6), // "froude"
QT_MOC_LITERAL(25, 204, 2), // "DH"
QT_MOC_LITERAL(26, 207, 14), // "critical_depth"
QT_MOC_LITERAL(27, 222, 4), // "yopt"
QT_MOC_LITERAL(28, 227, 12), // "normal_depth"
QT_MOC_LITERAL(29, 240, 11), // "get_profile"
QT_MOC_LITERAL(30, 252, 2), // "y0"
QT_MOC_LITERAL(31, 255, 20), // "fonctiondydx_for_RK4"
QT_MOC_LITERAL(32, 276, 10), // "methode_NR"
QT_MOC_LITERAL(33, 287, 14), // "methode_Bresse"
QT_MOC_LITERAL(34, 302, 11), // "methode_RK4"
QT_MOC_LITERAL(35, 314, 10), // "methode_KM"
QT_MOC_LITERAL(36, 325, 12), // "methode_Trap"
QT_MOC_LITERAL(37, 338, 10), // "calcul_HAF"
QT_MOC_LITERAL(38, 349, 25), // "desatif_noneed_Bresse_HAF"
QT_MOC_LITERAL(39, 375, 9), // "ischecked"
QT_MOC_LITERAL(40, 385, 25), // "desatif_noneed_DirectStep"
QT_MOC_LITERAL(41, 411, 13), // "desatif_L_HAF"
QT_MOC_LITERAL(42, 425, 12), // "currentIndex"
QT_MOC_LITERAL(43, 438, 20), // "afficher_information"
QT_MOC_LITERAL(44, 459, 2), // "yc"
QT_MOC_LITERAL(45, 462, 2), // "yn"
QT_MOC_LITERAL(46, 465, 11), // "profiletype"
QT_MOC_LITERAL(47, 477, 4), // "lowy"
QT_MOC_LITERAL(48, 482, 5), // "highy"
QT_MOC_LITERAL(49, 488, 19), // "lowerror_truncation"
QT_MOC_LITERAL(50, 508, 20), // "higherror_truncation"
QT_MOC_LITERAL(51, 529, 16), // "somme_truncation"
QT_MOC_LITERAL(52, 546, 18), // "methode_DirectStep"
QT_MOC_LITERAL(53, 565, 25), // "calcul_Energie_Specifique"
QT_MOC_LITERAL(54, 591, 9), // "calcul_Sf"
QT_MOC_LITERAL(55, 601, 22), // "remplire_Colonne_Yinpt"
QT_MOC_LITERAL(56, 624, 3), // "npt"
QT_MOC_LITERAL(57, 628, 20), // "remplire_Colonne_Yy1"
QT_MOC_LITERAL(58, 649, 2), // "y1"
QT_MOC_LITERAL(59, 652, 20), // "remplire_Colonne_Yy2"
QT_MOC_LITERAL(60, 673, 2), // "y2"
QT_MOC_LITERAL(61, 676, 12), // "Sfmoy_NR_HAF"
QT_MOC_LITERAL(62, 689, 16), // "saveGrapheToFile"
QT_MOC_LITERAL(63, 706, 18) // "Affichage_ycyn_HAF"

    },
    "hydraulics_channel_gvf\0SI_unite_HAF\0"
    "\0copy_table_in_Clipboard\0loop_step_haf\0"
    "double*\0So\0n\0Q\0Cm\0g\0y\0B\0SS\0z\0x\0stepdist\0"
    "totaldist\0standard_step_haf\0channel_geom\0"
    "std::unique_ptr<double[]>\0conveyance\0"
    "A\0R\0froude\0DH\0critical_depth\0yopt\0"
    "normal_depth\0get_profile\0y0\0"
    "fonctiondydx_for_RK4\0methode_NR\0"
    "methode_Bresse\0methode_RK4\0methode_KM\0"
    "methode_Trap\0calcul_HAF\0"
    "desatif_noneed_Bresse_HAF\0ischecked\0"
    "desatif_noneed_DirectStep\0desatif_L_HAF\0"
    "currentIndex\0afficher_information\0yc\0"
    "yn\0profiletype\0lowy\0highy\0lowerror_truncation\0"
    "higherror_truncation\0somme_truncation\0"
    "methode_DirectStep\0calcul_Energie_Specifique\0"
    "calcul_Sf\0remplire_Colonne_Yinpt\0npt\0"
    "remplire_Colonne_Yy1\0y1\0remplire_Colonne_Yy2\0"
    "y2\0Sfmoy_NR_HAF\0saveGrapheToFile\0"
    "Affichage_ycyn_HAF"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_hydraulics_channel_gvf[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  164,    2, 0x0a /* Public */,
       3,    0,  165,    2, 0x0a /* Public */,
       4,   12,  166,    2, 0x0a /* Public */,
      18,   11,  191,    2, 0x0a /* Public */,
      19,    3,  214,    2, 0x0a /* Public */,
      21,    4,  221,    2, 0x0a /* Public */,
      24,    4,  230,    2, 0x0a /* Public */,
      26,    5,  239,    2, 0x0a /* Public */,
      28,    7,  250,    2, 0x0a /* Public */,
      29,    8,  265,    2, 0x0a /* Public */,
      31,    8,  282,    2, 0x0a /* Public */,
      32,    0,  299,    2, 0x0a /* Public */,
      33,    0,  300,    2, 0x0a /* Public */,
      34,    0,  301,    2, 0x0a /* Public */,
      35,    0,  302,    2, 0x0a /* Public */,
      36,    0,  303,    2, 0x0a /* Public */,
      37,    0,  304,    2, 0x0a /* Public */,
      38,    1,  305,    2, 0x0a /* Public */,
      40,    1,  308,    2, 0x0a /* Public */,
      41,    1,  311,    2, 0x0a /* Public */,
      43,    8,  314,    2, 0x0a /* Public */,
      52,    0,  331,    2, 0x0a /* Public */,
      53,    4,  332,    2, 0x0a /* Public */,
      54,    5,  341,    2, 0x0a /* Public */,
      55,    1,  352,    2, 0x0a /* Public */,
      57,    1,  355,    2, 0x0a /* Public */,
      59,    1,  358,    2, 0x0a /* Public */,
      61,    0,  361,    2, 0x0a /* Public */,
      62,    0,  362,    2, 0x0a /* Public */,
      63,    0,  363,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 5, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    6,    7,    8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
    QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    6,    7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
    0x80000000 | 20, QMetaType::Double, QMetaType::Double, QMetaType::Double,   11,   12,   13,
    QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    7,   22,   23,    9,
    QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    8,   10,   22,   25,
    QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    8,   27,   10,   12,   13,
    QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    6,    7,    8,   27,    9,   12,   13,
    QMetaType::QString, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    6,    7,    8,   10,    9,   12,   13,   30,
    QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,   11,   12,   13,    8,    7,    9,    6,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   39,
    QMetaType::Void, QMetaType::Bool,   39,
    QMetaType::Void, QMetaType::Int,   42,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::QString, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,   44,   45,   46,   47,   48,   49,   50,   51,
    QMetaType::Void,
    QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    8,   11,   22,   10,
    QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    8,    7,   22,   23,    9,
    QMetaType::Void, QMetaType::Int,   56,
    QMetaType::Void, QMetaType::Double,   58,
    QMetaType::Void, QMetaType::Double,   60,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void hydraulics_channel_gvf::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        hydraulics_channel_gvf *_t = static_cast<hydraulics_channel_gvf *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SI_unite_HAF(); break;
        case 1: _t->copy_table_in_Clipboard(); break;
        case 2: { double* _r = _t->loop_step_haf((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< double(*)>(_a[7])),(*reinterpret_cast< double(*)>(_a[8])),(*reinterpret_cast< double(*)>(_a[9])),(*reinterpret_cast< double(*)>(_a[10])),(*reinterpret_cast< double(*)>(_a[11])),(*reinterpret_cast< double(*)>(_a[12])));
            if (_a[0]) *reinterpret_cast< double**>(_a[0]) = std::move(_r); }  break;
        case 3: { double _r = _t->standard_step_haf((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< double(*)>(_a[7])),(*reinterpret_cast< double(*)>(_a[8])),(*reinterpret_cast< double(*)>(_a[9])),(*reinterpret_cast< double(*)>(_a[10])),(*reinterpret_cast< double(*)>(_a[11])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 4: { std::unique_ptr<double[]> _r = _t->channel_geom((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< std::unique_ptr<double[]>*>(_a[0]) = std::move(_r); }  break;
        case 5: { double _r = _t->conveyance((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 6: { double _r = _t->froude((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 7: { double _r = _t->critical_depth((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 8: { double _r = _t->normal_depth((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< double(*)>(_a[7])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 9: { QString _r = _t->get_profile((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< double(*)>(_a[7])),(*reinterpret_cast< double(*)>(_a[8])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 10: { double _r = _t->fonctiondydx_for_RK4((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< double(*)>(_a[7])),(*reinterpret_cast< double(*)>(_a[8])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->methode_NR(); break;
        case 12: _t->methode_Bresse(); break;
        case 13: _t->methode_RK4(); break;
        case 14: _t->methode_KM(); break;
        case 15: _t->methode_Trap(); break;
        case 16: _t->calcul_HAF(); break;
        case 17: _t->desatif_noneed_Bresse_HAF((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->desatif_noneed_DirectStep((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->desatif_L_HAF((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->afficher_information((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< double(*)>(_a[7])),(*reinterpret_cast< double(*)>(_a[8]))); break;
        case 21: _t->methode_DirectStep(); break;
        case 22: { double _r = _t->calcul_Energie_Specifique((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 23: { double _r = _t->calcul_Sf((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 24: _t->remplire_Colonne_Yinpt((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->remplire_Colonne_Yy1((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 26: _t->remplire_Colonne_Yy2((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 27: _t->Sfmoy_NR_HAF(); break;
        case 28: _t->saveGrapheToFile(); break;
        case 29: _t->Affichage_ycyn_HAF(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject hydraulics_channel_gvf::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_hydraulics_channel_gvf.data,
    qt_meta_data_hydraulics_channel_gvf,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *hydraulics_channel_gvf::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *hydraulics_channel_gvf::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_hydraulics_channel_gvf.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int hydraulics_channel_gvf::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 30)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 30;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

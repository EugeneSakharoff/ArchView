QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    checkboxselector.cpp \
    comboboxselector.cpp \
    controlbuttons.cpp \
    controlelement.cpp \
    customdelegate.cpp \
    customquerymodel.cpp \
    customsortmodel.cpp \
    customtableview.cpp \
    database.cpp \
    globals.cpp \
    intervalselector.cpp \
    intervalslider.cpp \
    itemselector.cpp \
    main.cpp \
    mainwindow.cpp \
    opendbdialog.cpp \
    optionswindow.cpp \
    qcustomplot.cpp \
    sql_globals.cpp \
    sql_query.cpp \
    stringvalidator.cpp \
    test_tables.cpp \
    timeselector.cpp \
    ui.cpp

HEADERS += \
    checkboxselector.h \
    comboboxselector.h \
    controlbuttons.h \
    controlelement.h \
    customdelegate.h \
    customquerymodel.h \
    customsortmodel.h \
    customtableview.h \
    database.h \
    globals.h \
    intervalselector.h \
    intervalslider.h \
    itemselector.h \
    mainwindow.h \
    opendbdialog.h \
    optionswindow.h \
    qcustomplot.h \
    sql_globals.h \
    sql_query.h \
    stringvalidator.h \
    test_tables.h \
    timeselector.h \
    ui.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    mainwindow.ui \
    opendbdialog.ui \
    optionswindow.ui

RC_FILE = qarchview.rc

RESOURCES += \
    qarchview.qrc

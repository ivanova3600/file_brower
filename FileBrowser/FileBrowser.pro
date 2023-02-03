QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    achieve.cpp \
    dirview.cpp \
    findfileswidget.cpp \
    main.cpp \
    mainwindow.cpp \
    openimagewidget.cpp \
    propertywidget.cpp \
    rename.cpp

HEADERS += \
    achieve.h \
    dirview.h \
    findfileswidget.h \
    mainwindow.h \
    openimagewidget.h \
    propertywidget.h \
    rename.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons/icons.qrc


DEFINES += PRO_FILE_PWD=$$sprintf("\"\\\"%1\\\"\"", $$_PRO_FILE_PWD_)

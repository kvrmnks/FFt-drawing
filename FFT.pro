QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
#使用windeployqt打包程序
TARGET = $$qtLibraryTarget($$TARGET)       #为debug版自动添加d后缀
TargetFile = $$OUT_PWD
CONFIG(debug,debug|release):TargetFile = $$TargetFile/debug/$$TARGET".exe"
CONFIG(release,debug|release):TargetFile = $$TargetFile/release/$$TARGET".exe"
#可用DESTDIR设置TARGER的目录,例如
# DESTDIR = $$PWD/../bin
# TargetFile = $$DESTDIR/$$TARGET".exe"
win32
{
    QMAKE_POST_LINK += $$[QT_INSTALL_BINS]/windeployqt.exe $$TargetFile &
    #QML程序需要加参数
    # $$[QT_INSTALL_BINS]/windeployqt.exe $$TargetFile -qmldir $$[QT_INSTALL_QML]
    #执行其他命令
    # QMAKE_POST_LINK  += copy ..
}

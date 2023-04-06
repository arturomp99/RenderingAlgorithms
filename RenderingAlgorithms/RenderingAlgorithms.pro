QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += dependencies

LIBS += -lopengl32 \
       -L$$PWD/dependencies/GL/libs -lglew32

DEFINES += _USE_MATH_DEFINES

SOURCES += \
    camera.cpp \
    glutils.cpp \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    mesh_io.cpp \
    scenephong.cpp \
    trianglemesh.cpp \
    widgetphong.cpp

HEADERS += \
    camera.h \
    defines.h \
    glutils.h \
    glwidget.h \
    mesh_io.h \
    scene.h \
    mainwindow.h \
    scenephong.h \
    trianglemesh.h \
    widgetphong.h

FORMS += \
    mainwindow.ui \
    widgetphong.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    shaders/phong.frag \
    shaders/phong.vert

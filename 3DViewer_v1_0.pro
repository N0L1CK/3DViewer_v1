QT       += core gui opengl openglwidgets printsupport
LIBS += -lopengl32 -lglu32
include(QTGifimage-master/src/gifimage/qtgifimage.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/affine.c \
    source/viewer.c \
    source/glview.cpp \
    source/main.cpp \
    source/mainviewer.cpp \
    source/settings.cpp

HEADERS += \
    header/viewer.h \
    header/glview.h \
    header/mainviewer.h \
    header/settings.h

FORMS += \
    ui/mainviewer.ui \
    ui/settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

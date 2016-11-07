#-------------------------------------------------
#
# Project created by QtCreator 2016-07-14T19:26:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myData
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    common/mydrawlabel.cpp \
    test/solution.cpp

HEADERS  += dialog.h \
    Tree/avltree.h \
    common/mydrawlabel.h \
    sort/insertionsort.h \
    common/tool.h \
    Hash/mrprime.h \
    Hash/hashtable.h \
    disjoint/disjsets.h \
    test/solution.h

FORMS    += dialog.ui
INCLUDEPATH +=  D:/opencv3.0.1/opencv/build/include \
                D:/opencv3.0.1/opencv/build/include/opencv \
                D:/opencv3.0.1/opencv/build/include/opencv2

LIBS += -LD:/opencv3.0.1/opencv/build/x64/vc12/lib \
-lopencv_world310d

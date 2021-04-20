QT      += core gui
TEMPLATE = app
TARGET = trees
INCLUDEPATH += .

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += AVLTree.h \
           Canvas.h \
           mainwindow.h \
           node.h \
           RedBlackTree.h \
           SplayTree.h \
           tree.h \
           Vertex.h
FORMS += mainwindow.ui
SOURCES += main.cpp mainwindow.cpp Vertex.cpp \
    node.cpp \
    tree.cpp
RESOURCES += src.qrc

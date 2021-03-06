# -------------------------------------------------
# Project created by QtCreator 2009-01-10T14:03:23
# -------------------------------------------------
QT += network widgets
TARGET = MyQServer
TEMPLATE = app

SOURCES += ./src/main.cpp \
    ./src/MySocketServer.cpp \
    ./src/MySocketClient.cpp \
    ./src/dialog.cpp \
    src/Response.cpp \
    src/Htmlwrapper.cpp \
    src/Statistics.cpp

HEADERS += ./src/MySocketServer.h \
    ./src/MySocketClient.h \
    ./src/dialog.h \
    src/Response.h \
    src/Htmlwrapper.h \
    src/Statistics.h \
    src/mylib.h

OTHER_FILES += MyQServer.pro
CONFIG += c++11

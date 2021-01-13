QT += core gui widgets

CONFIG += c++14

OBJECTS_DIR = obj
MOC_DIR = moc

TARGET = connection_colors
TEMPLATE = app

include(../../NodeEditor-static.pri);

HEADERS += $$files($$PWD/*.hpp, false)
SOURCES += $$files($$PWD/*.cpp, false)

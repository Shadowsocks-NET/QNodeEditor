DEFINES += NODE_EDITOR_STATIC

HEADERS += $$files($$PWD/include/nodes/*, true)
HEADERS += $$files($$PWD/src/*.hpp, true)

SOURCES += $$files($$PWD/src/*.cpp, true)

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/include/nodes/
INCLUDEPATH += $$PWD/include/nodes/internal/
INCLUDEPATH += $$PWD/src/

RESOURCES += $$PWD/resources/DefaultStyle.json \
             $$PWD/resources/nodeeditor.qrc

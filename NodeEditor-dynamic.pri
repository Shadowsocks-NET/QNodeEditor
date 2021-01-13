DEFINES += NODE_EDITOR_SHARED

HEADERS += $$files($$PWD/include/nodes/*, true)
HEADERS += $$files($$PWD/src/*.hpp, true)

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/include/nodes/
INCLUDEPATH += $$PWD/include/nodes/internal/
INCLUDEPATH += $$PWD/src/

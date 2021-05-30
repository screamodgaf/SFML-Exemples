TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp




INCLUDEPATH += $$PWD/../LibsSFML32/include
DEPENDPATH += $$PWD/../LibsSFML32/build
unix|win32: LIBS += -L$$PWD/../LibsSFML32/build/lib/ -lsfml-system
unix|win32: LIBS += -L$$PWD/../LibsSFML32/build/lib/ -lsfml-window
unix|win32: LIBS += -L$$PWD/../LibsSFML32/build/lib/ -lsfml-graphics
unix|win32: LIBS += -L$$PWD/../LibsSFML32/build/lib/ -lsfml-audio


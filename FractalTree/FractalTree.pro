TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp
QMAKE_CXXFLAGS += -std=c++14

LIBS += \
        -lsfml-window \
        -lsfml-system \
        -lsfml-graphics

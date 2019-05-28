TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += RANDOM
SOURCES += main.cpp
LIBS += -lsfml-system -lsfml-graphics -lsfml-window

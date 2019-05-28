TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
	main.cpp
DEFINES += SCREENSIZE=600

LIBS += -lsfml-window -lsfml-graphics -lsfml-system

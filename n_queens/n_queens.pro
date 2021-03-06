QT -= gui
QMAKE_CXXFLAGS += -std=c++17
CONFIG += console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

LIBS += -lsfml-system -lsfml-window -lsfml-graphics

OTHER_FILES += \
    $$PWD/queen.png
defineTest(copyHelpFiles) {
    files = $$1
    for(FILE, files) {
        FILE ~= s,docs/,,
        FILE = $$PWD/$$FILE
        MYFILECOPY += @echo "Copying $$FILE" $$escape_expand(\\n\\t)
        win32:FILE ~= s,/,\\,g
        MYFILECOPY += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }
    export(MYFILECOPY)
}
copyHelpFiles($$OTHER_FILES)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

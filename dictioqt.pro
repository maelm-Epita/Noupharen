TEMPLATE = app
TARGET = dictio_gen

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    src/climain.cpp \
    src/dictionnary.cpp \
    src/generator.cpp \
    src/qt_mainwindow.cpp \
    src/word.cpp \
    src/wordattribute.cpp

HEADERS += \
    include/dictionary.hpp \
    include/generator.hpp \
    include/letter.hpp \
    include/lettergroup.hpp \
    include/qt_mainwindow.h \
    include/syllable.hpp \
    include/syllablepattern.hpp \
    include/word.hpp \
    include/wordattribute.hpp \
    include/wordgroup.hpp

FORMS += \
  forms/mainwindow.ui

RESOURCES += \
  resources/images.qrc

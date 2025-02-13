TEMPLATE = app
TARGET = dictio_gen

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    src/climain.cpp \
    src/dictionnary.cpp \
    src/generator.cpp \
    src/qt_attributetableview.cpp \
    src/qt_langsettingswindow.cpp \
    src/qt_mainwindow.cpp \
    src/qt_tbvbuttondelegate.cpp \
    src/qt_tbvcomboboxdelegate.cpp \
    src/settingserror.cpp \
    src/word.cpp \
    src/wordattribute.cpp

HEADERS += \
    forms/langsettingswindow.h \
    include/dictionary.hpp \
    include/generator.hpp \
    include/letter.hpp \
    include/lettergroup.hpp \
    include/qt_attributetableview.h \
    include/qt_langsettingswindow.h \
    include/qt_mainwindow.h \
    include/qt_tbvbuttondelegate.h \
    include/qt_tbvcomboboxdelegate.h \
    include/settingserror.hpp \
    include/syllable.hpp \
    include/syllablepattern.hpp \
    include/word.hpp \
    include/wordattribute.hpp \
    include/wordgroup.hpp \
    qt_tbvcomboboxdelegate.h

FORMS += \
  forms/langsettingswindow.ui \
  forms/mainwindow.ui

RESOURCES += \
  resources/images.qrc

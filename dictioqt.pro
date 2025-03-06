TEMPLATE = app
TARGET = dictio_gen

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



SOURCES += \
    main.cpp \
    src/climain.cpp \
    src/dictionnary.cpp \
    src/generator.cpp \
    src/helpers.cpp \
    src/lettergroup.cpp \
    src/probability.cpp \
    src/qt_attributetableview.cpp \
    src/qt_langsettingswindow.cpp \
    src/qt_mainwindow.cpp \
    src/qt_tbvcomboboxdelegate.cpp \
    src/qt_tbvspinboxdelegate.cpp \
    src/qt_wattrsettingswindow.cpp \
    src/settingserror.cpp \
    src/syllable.cpp \
    src/word.cpp \
    src/wordattribute.cpp \
    src/wordattributefunctionpreset.cpp

HEADERS += \
    forms/langsettingswindow.h \
    include/dictionary.hpp \
    include/dictword.h \
    include/generator.hpp \
    include/helpers.h \
    include/letter.hpp \
    include/lettergroup.hpp \
    include/probability.hpp \
    include/qt_attributetableview.h \
    include/qt_langsettingswindow.h \
    include/qt_mainwindow.h \
    include/qt_tbvcomboboxdelegate.h \
    include/qt_tbvspinboxdelegate.h \
    include/qt_wattrsettingswindow.h \
    include/settingserror.hpp \
    include/syllable.hpp \
    include/syllablepattern.hpp \
    include/word.hpp \
    include/wordattribute.hpp \
    include/wordattributefunctionpreset.hpp \
    include/wordgroup.hpp \
    qt_tbvcomboboxdelegate.h

FORMS += \
  forms/langsettingswindow.ui \
  forms/mainwindow.ui \
  forms/wattrsettingswindow.ui

RESOURCES += \
  resources/images.qrc

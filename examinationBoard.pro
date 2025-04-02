TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        assessmentcode.cpp \
        awardcode.cpp \
        code.cpp \
        main.cpp \
        modulecode.cpp \
        nec.cpp \
        progressioncode.cpp

LIBS += -lboost_unit_test_framework

macx{
  INCLUDEPATH += "/opt/homebrew/cellar/boost/1.84.0_1/include"
  LIBS += -L"/opt/homebrew/cellar/boost/1.84.0_1/lib"
}

HEADERS += \
    CodeConstants.h \
    assessmentcode.h \
    awardcode.h \
    code.h \
    modulecode.h \
    nec.h \
    progressioncode.h

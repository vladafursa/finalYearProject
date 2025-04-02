TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        assessmentcode.cpp \
        code.cpp \
        main.cpp \
        modulecode.cpp \
        progressioncode.cpp

LIBS += -lboost_unit_test_framework

macx{
  INCLUDEPATH += "/opt/homebrew/cellar/boost/1.84.0_1/include"
  LIBS += -L"/opt/homebrew/cellar/boost/1.84.0_1/lib"
}

HEADERS += \
    assessmentcode.h \
    code.h \
    modulecode.h \
    progressioncode.h

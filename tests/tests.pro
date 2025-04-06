TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt
TARGET = tests

SOURCES += moduletests.cpp \
        ../assessment.cpp \
        ../assessmentattempt.cpp \
        ../assessmentcode.cpp \
        ../awardcode.cpp \
        ../code.cpp \
        ../misconduct.cpp \
        ../module.cpp \
        ../moduleattempt.cpp \
        ../modulecode.cpp \
        ../nec.cpp \
        ../progressioncode.cpp \
        ../grades.cpp \
        gradesystemtests.cpp \
        stagetests.cpp \
        testmain.cpp

LIBS += -lboost_unit_test_framework

macx{
  INCLUDEPATH += "/opt/homebrew/cellar/boost/1.84.0_1/include"
  LIBS += -L"/opt/homebrew/cellar/boost/1.84.0_1/lib"
}

INCLUDEPATH += ../

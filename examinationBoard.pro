TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        assessment.cpp \
        assessmentattempt.cpp \
        assessmentcode.cpp \
        awardcode.cpp \
        code.cpp \
        course.cpp \
        courseattempt.cpp \
        examboard.cpp \
        grades.cpp \
        main.cpp \
        misconduct.cpp \
        module.cpp \
        moduleattempt.cpp \
        modulecode.cpp \
        nec.cpp \
        progressioncode.cpp \
        stage.cpp \
        stageattempt.cpp \
        student.cpp \
        studentrecord.cpp

LIBS += -lboost_unit_test_framework

macx{
  INCLUDEPATH += "/opt/homebrew/cellar/boost/1.84.0_1/include"
  LIBS += -L"/opt/homebrew/cellar/boost/1.84.0_1/lib"
}

HEADERS += \
    CodeConstants.h \
    StdExtension.h \
    assessment.h \
    assessmentattempt.h \
    assessmentcode.h \
    awardcode.h \
    code.h \
    course.h \
    courseattempt.h \
    examboard.h \
    grades.h \
    misconduct.h \
    module.h \
    moduleattempt.h \
    modulecode.h \
    nec.h \
    progressioncode.h \
    stage.h \
    stageattempt.h \
    student.h \
    studentrecord.h


INCLUDEPATH += /opt/homebrew/include
LIBS += -L/opt/homebrew/lib -lpqxx -L/opt/homebrew/opt/libpq/lib -lpq



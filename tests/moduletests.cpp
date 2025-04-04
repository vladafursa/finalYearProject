#include <boost/test/unit_test.hpp>
#include "../assessment.h"
#include <iostream>
#include "../assessment.h"
#include "../assessmentattempt.h"
#include "../misconduct.h"
#include <unordered_map>
#include "../StdExtension.h"
#include <functional>
#include "../module.h"
#include "../moduleattempt.h"

using namespace std;
#include <vector>

const double percentageAccuracy =0.1;

//defining courseworks and exams
const Assessment cwk1("11","coursework","coding tax system");
const Assessment cwk2("12","coursework","refactoring tax system");
const Assessment cwk3("13","coursework","evalating tax system program");

const Assessment ex1("21", "exam", "check knowledge about OOP");
const Assessment ex2("22", "exam", "check knowledge about SQL");
const Assessment ex3("23", "exam", "check knowledge about cloud computing");


//misconducts
const Misconduct m1("1", "T1", "serious", "3LOW");

//defining assessment attempts
AssessmentAttempt normalAttemptCoursework("T1", cwk1, 1, "original", false, 10);
AssessmentAttempt failAttemptCoursework("T1", cwk2, 1, "original", false, 2);
AssessmentAttempt repeatAttemptCoursework("T1", cwk2, 2, "original", false, 12);
AssessmentAttempt attemptExam("T1", ex1, 1, "original", false, 3);
AssessmentAttempt failAttemptExam("T1", ex1, 2, "original", false, 8);
AssessmentAttempt goodAttemptExam("T1", ex1, 1, "original", false, 9);
AssessmentAttempt neutralAttemptExam("T1", ex1, 1, "original", false, 5);
AssessmentAttempt attemptMisconductCoursework("T1", cwk3, 1, "original", false, 3, nullptr, nullptr, &m1);


BOOST_AUTO_TEST_SUITE( moduleTests )


//testing populating map
BOOST_AUTO_TEST_CASE(assessmentWeightsMapTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk1), 60);
    assessmentList1.emplace(std::ref(ex1), 40);

    BOOST_CHECK_EQUAL(assessmentList1.size(), 2);
}

//testing getting only final attempts
BOOST_AUTO_TEST_CASE(allFirstTryTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk1), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);
    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(normalAttemptCoursework);
    attempts.push_back(attemptExam);
    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);

    int expectedResult = 2;
    int actualResult = moduleAttempt1.getFinalattempts().size();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(oneFailAttemptTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk2), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);
    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(failAttemptCoursework);
    attempts.push_back(repeatAttemptCoursework);
    attempts.push_back(attemptExam);
    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);

    int expectedResult = 2;
    int actualResult = moduleAttempt1.getFinalattempts().size();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

//check which attempt was added
BOOST_AUTO_TEST_CASE(checkWhichAddedOneFailTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk2), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(failAttemptCoursework));
    attempts.push_back(std::ref(repeatAttemptCoursework));
    attempts.push_back(std::ref(attemptExam));
    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);

    bool found = false;
    for (const auto& attempt : moduleAttempt1.getFinalattempts()) {
        if (attempt.get().getAssessment().getName() == repeatAttemptCoursework.getAssessment().getName() &&
            attempt.get().getNumberOfAttempt() == repeatAttemptCoursework.getNumberOfAttempt()) {
            found = true;
            break;
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(checkWhichAddedALlFailTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk2), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(failAttemptCoursework));
    attempts.push_back(std::ref(repeatAttemptCoursework));
    attempts.push_back(std::ref(attemptExam));
    attempts.push_back(std::ref(failAttemptExam));
    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);

    bool found = false;
    for (const auto& attempt : moduleAttempt1.getFinalattempts()) {
        if (attempt.get().getAssessment().getName() == repeatAttemptCoursework.getAssessment().getName() &&
            attempt.get().getNumberOfAttempt() == repeatAttemptCoursework.getNumberOfAttempt()) {
            found = true;
            break;
        }
    }
    BOOST_CHECK(found);
}


//check aggregates
BOOST_AUTO_TEST_CASE(checkNormalAggregatelTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk1), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(normalAttemptCoursework));
    attempts.push_back(std::ref(attemptExam));

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);

    double actualResult = moduleAttempt1.calculateAggregate();
    double expectedResult = 7.2;

     BOOST_CHECK_CLOSE( actualResult, expectedResult, percentageAccuracy );
}


BOOST_AUTO_TEST_CASE(unusualPercentageTest) {
     AssessmentWeightsMap assessmentList1;
     assessmentList1.emplace(std::ref(cwk1), 85);
     assessmentList1.emplace(std::ref(ex1), 15);
     Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

     std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
     attempts.push_back(std::ref(normalAttemptCoursework));
     attempts.push_back(std::ref(attemptExam));

     ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);

     double actualResult = moduleAttempt1.calculateAggregate();
     double expectedResult = 9.0;

     BOOST_CHECK_CLOSE( actualResult, expectedResult, percentageAccuracy );
}

BOOST_AUTO_TEST_CASE(roundingUpTest) {
     AssessmentWeightsMap assessmentList1;
     assessmentList1.emplace(std::ref(cwk1), 45);
     assessmentList1.emplace(std::ref(ex1), 55);
     Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

     std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
     attempts.push_back(std::ref(normalAttemptCoursework));
     attempts.push_back(std::ref(attemptExam));

     ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);

     double actualResult = moduleAttempt1.calculateAggregate();
     double expectedResult = 6.2;

     BOOST_CHECK_CLOSE( actualResult, expectedResult, percentageAccuracy );
}


//check all elements passed
BOOST_AUTO_TEST_CASE(allPassedTest) {
     AssessmentWeightsMap assessmentList1;
     assessmentList1.emplace(std::ref(cwk1), 40);
     assessmentList1.emplace(std::ref(ex1), 60);
     Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

     std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
     attempts.push_back(std::ref(normalAttemptCoursework));
     attempts.push_back(std::ref(goodAttemptExam));

     ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);

     bool actualResult = moduleAttempt1.checkAllElementsPassed();

     bool expectedResult = true;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

//one element didn't pass
BOOST_AUTO_TEST_CASE(oneNotPassTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk1), 40);
    assessmentList1.emplace(std::ref(ex1), 60);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(normalAttemptCoursework));
    attempts.push_back(std::ref(attemptExam));

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);

    bool actualResult = moduleAttempt1.checkAllElementsPassed();

    bool expectedResult = false;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(allNotPassTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk2), 40);
    assessmentList1.emplace(std::ref(ex1), 60);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(failAttemptCoursework));
    attempts.push_back(std::ref(attemptExam));

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);

    bool actualResult = moduleAttempt1.checkAllElementsPassed();

    bool expectedResult = false;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


//determine special pass
BOOST_AUTO_TEST_CASE(notSpecialPassTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk2), 90);
    assessmentList1.emplace(std::ref(ex1), 10);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(failAttemptCoursework));
    attempts.push_back(std::ref(neutralAttemptExam));

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.getGrade();

    bool actualResult = moduleAttempt1.determinSpecialPass();

    bool expectedResult = false;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(specialPassTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk1), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(normalAttemptCoursework));
    attempts.push_back(std::ref(attemptExam));

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.getGrade();

    bool actualResult = moduleAttempt1.determinSpecialPass();

    bool expectedResult = true;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_SUITE_END()

/*
should I test attempt1.getGrade();? if it is mostly part of gradesystem???
*/

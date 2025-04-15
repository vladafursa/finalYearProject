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
/*
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
const Misconduct m1("1", "T1", "serious", "The module is capped at low 3");
const Misconduct m2("1", "T1", "serious", "The module is set to 0");

//defining assessment attempts
AssessmentAttempt goodAttemptCoursework("T1", cwk1, 1, "original", false, 10);
AssessmentAttempt submittedLateCoursework("T1", cwk1, 1, "original", true, 4);
AssessmentAttempt failAttemptCoursework("T1", cwk2, 1, "original", false, 2);
AssessmentAttempt repeatAttemptCoursework("T1", cwk2, 2, "referred", false, 12);
AssessmentAttempt attemptExam("T1", ex1, 1, "original", false, 3);
AssessmentAttempt failAttemptExam("T1", ex1, 2, "original", false, 8);
AssessmentAttempt goodAttemptExam("T1", ex1, 1, "original", false, 9);
AssessmentAttempt neutralAttemptExam("T1", ex1, 1, "original", false, 5);
AssessmentAttempt attemptMisconductCoursework("T1", cwk3, 1, "original", false, 10, nullptr, nullptr, &m1);
AssessmentAttempt attemptSeriousMisconductCoursework("T1", cwk3, 1, "original", false, 10, nullptr, nullptr, &m2);
AssessmentAttempt attemptSeriousMisconductNotPassCoursework("T1", cwk3, 1, "original", false, 1, nullptr, nullptr, &m2);


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
    attempts.push_back(goodAttemptCoursework);
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
    attempts.push_back(std::ref(goodAttemptCoursework));
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
     attempts.push_back(std::ref(goodAttemptCoursework));
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
     attempts.push_back(std::ref(goodAttemptCoursework));
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
     attempts.push_back(std::ref(goodAttemptCoursework));
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
    attempts.push_back(std::ref(goodAttemptCoursework));
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
    attempts.push_back(std::ref(goodAttemptCoursework));
    attempts.push_back(std::ref(attemptExam));

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.getGrade();

    bool actualResult = moduleAttempt1.determinSpecialPass();

    bool expectedResult = true;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

//applyMisconduct
BOOST_AUTO_TEST_CASE(cap3MisconductTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk3), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(attemptMisconductCoursework));
    attempts.push_back(std::ref(attemptExam));

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.applyMisconduct();

    std::string actualGrade = moduleAttempt1.getGrade();
    std::string expectedGrade = "3LOW";

    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "PB";


    BOOST_CHECK_EQUAL(actualGrade, expectedGrade);

}

//cap 0 misconduct
BOOST_AUTO_TEST_CASE(cap0MisconductTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk3), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(attemptSeriousMisconductCoursework));
    attempts.push_back(std::ref(attemptExam));

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.applyMisconduct();

    std::string actualGrade = moduleAttempt1.getGrade();
    std::string expectedGrade = "ZERO";

    BOOST_CHECK_EQUAL(actualGrade, expectedGrade);

}

BOOST_AUTO_TEST_CASE(noMisconductTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk1), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(goodAttemptCoursework));
    attempts.push_back(std::ref(attemptExam));

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.applyMisconduct();

    std::string actualGrade = moduleAttempt1.getGrade();
    std::string expectedGrade = "22LOW";

    BOOST_CHECK_EQUAL(actualGrade, expectedGrade);

}

//generating codes
BOOST_AUTO_TEST_CASE(passCappedMisconductTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk3), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(attemptMisconductCoursework));
    attempts.push_back(std::ref(goodAttemptExam));

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();
    moduleAttempt1.applyMisconduct();

    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "PB";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}

BOOST_AUTO_TEST_CASE(passAddCreditsOnlyMisconductTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk3), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(attemptSeriousMisconductCoursework));
    attempts.push_back(std::ref(goodAttemptExam));

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();
    moduleAttempt1.applyMisconduct();

    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "PJ";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}

BOOST_AUTO_TEST_CASE(notPassAddCreditsOnlyMisconductTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk3), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(attemptSeriousMisconductNotPassCoursework));
    attempts.push_back(std::ref(goodAttemptExam));

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();
    moduleAttempt1.applyMisconduct();


    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "FC";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}


BOOST_AUTO_TEST_CASE(usualPassDecisionTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk1), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(goodAttemptCoursework));
    attempts.push_back(std::ref(goodAttemptExam));

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();


    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "PA";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}

BOOST_AUTO_TEST_CASE(referredPassDecisionTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk2), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(repeatAttemptCoursework));
    attempts.push_back(std::ref(goodAttemptExam));

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "refered", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();


    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "PR";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}

BOOST_AUTO_TEST_CASE(repeatedPassDecisionTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk2), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(repeatAttemptCoursework));
    attempts.push_back(std::ref(goodAttemptExam));

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "repeated", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();


    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "PF";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}

BOOST_AUTO_TEST_CASE(repeatedAndRepeatedPassDecisionTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk2), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(repeatAttemptCoursework));
    attempts.push_back(std::ref(goodAttemptExam));

    ModuleAttempt moduleAttempt1("T1", mod1, 3, "repeated", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();


    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "PX";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}

BOOST_AUTO_TEST_CASE(submittedLatePassDecisionTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk1), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(submittedLateCoursework));
    attempts.push_back(std::ref(goodAttemptExam));

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();


    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "PL";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}

/*
 *
 * void ModuleAttempt::populatePossibleDecisions(){
    if (module.getType() == "optional"){
            posibleCodes.push_back(&ModuleCodes::FO);
    }

    int notPassed = 0;
    std::vector<std::reference_wrapper<AssessmentAttempt>> finalAttempts = getFinalattempts();
    for (const auto& attempt : finalAttempts) {
            std::string grade = attempt.get().getGrade();
            if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
            notPassed++;
        }
    }
    if (notPassed>1){
        posibleCodes.push_back(&ModuleCodes::FA);
        posibleCodes.push_back(&ModuleCodes::FR);
        posibleCodes.push_back(&ModuleCodes::FM);
    }
    else{
        if(notPassed!=finalAttempts.size()){
            posibleCodes.push_back(&ModuleCodes::RR);
        }
    }
    posibleCodes.push_back(&ModuleCodes::DF);
    if (getHadNec() == true){
        for (const auto& attempt : finalAttempts) {
            if (attempt.get().getGradePoints() == 0){
                 posibleCodes.push_back(&ModuleCodes::S1);
                break;
            }
        }
    }
}


void ModuleAttempt::generateCode(){
    if (checkAllElementsPassed() || determinSpecialPass()){
        passed = true;
        creditsEarned=module.getCredits();

        else if (getSubmittedLate()){
            setFinalCode(&ModuleCodes::PL);
        }
        else{
            setFinalCode(&ModuleCodes::PA);
        }
    }
    else{
        passed = false;
        creditsEarned = 0;
        if (numberOfAttempt == 2){
            if (getHadNec() == false){
                setFinalCode(&ModuleCodes::FN);
            }
            else{
                if (type == "referred"){
                    setFinalCode(&ModuleCodes::F1);
                }
                else{
                    setFinalCode(&ModuleCodes::FP);
                }
            }
        }
        else if (numberOfAttempt > 2){
                setFinalCode(&ModuleCodes::FN);
        }
        else{
                setFinalCode(&ModuleCodes::FP);
        }
    }
}
*/
/*
BOOST_AUTO_TEST_SUITE_END()*/

/*
should I test attempt1.getGrade();? if it is mostly part of gradesystem???
*/

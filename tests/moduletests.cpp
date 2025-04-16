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
const Misconduct m1("1", "T1", "serious", "the module is capped at low 3");
const Misconduct m2("1", "T1", "serious", "overall module grade is capped at zero");
const Misconduct m3("1", "T1", "serious", "no credit given for the module");
const Misconduct m4("1", "T1", "serious", "termination of studies");

const NEC nextOpportunityUpheldNEC("N1", "T1", true, "next opportunity");
const NEC weekUpheldNEC("N1", "T1", true, "1 week");

BOOST_AUTO_TEST_SUITE( moduleTests )

//testing populating map
BOOST_AUTO_TEST_CASE(assessmentWeightsMapTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);

    BOOST_CHECK_EQUAL(assessmentList1.size(), 2);
}

//testing getting latest attempts
BOOST_AUTO_TEST_CASE(allFirstAttemptsTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 16);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    int expectedResult = 2;
    int actualResult = moduleAttempt1.getLatestAttempts().size();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(oneSecondAttemptTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 5);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16);
    auto attempt3 = std::make_shared<AssessmentAttempt>("T1", ex2, 2,  false, 16, nullptr, nullptr, nullptr, &ex1);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);
    attempts.push_back(attempt3);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    int expectedResult = 2;
    int actualResult = moduleAttempt1.getLatestAttempts().size();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);

    //chech that needed attempt was added
    bool found = false;
    for (const auto& attempt : moduleAttempt1.getLatestAttempts()) {
        if (attempt->getAssessment().getName() == attempt3->getAssessment().getName() &&
            attempt->getNumberOfAttempt() == attempt3->getNumberOfAttempt()) {
            found = true;
            break;
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(allSecondAttemptTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 5);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16);
    auto attempt3 = std::make_shared<AssessmentAttempt>("T1", ex2, 2,  false, 16, nullptr, nullptr, nullptr, &ex1);
    auto attempt4 = std::make_shared<AssessmentAttempt>("T1", cwk2, 2,  false, 16, nullptr, nullptr, nullptr, &cwk1);
    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);
    attempts.push_back(attempt3);
    attempts.push_back(attempt4);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    int expectedResult = 2;
    int actualResult = moduleAttempt1.getLatestAttempts().size();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);

    //chech that needed attempt was added
    int foundNeededAttempts=0;
    for (const auto& attempt : moduleAttempt1.getLatestAttempts()) {
        if (attempt->getAssessment().getName() == attempt3->getAssessment().getName() &&
            attempt->getNumberOfAttempt() == attempt3->getNumberOfAttempt()) {
            foundNeededAttempts++;
        }
        if(
            attempt->getAssessment().getName() == attempt4->getAssessment().getName() &&
            attempt->getNumberOfAttempt() == attempt4->getNumberOfAttempt()){
            foundNeededAttempts++;
        }
    }

    BOOST_CHECK_EQUAL(foundNeededAttempts, 2);
}


//testing getting best attempts
BOOST_AUTO_TEST_CASE(usualFirstAttemptsTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 16);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    int expectedResult = 2;
    int actualResult = moduleAttempt1.getFinalattempts().size();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


BOOST_AUTO_TEST_CASE(SecondAttemptBetterTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 14);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 5);
    auto attempt3 = std::make_shared<AssessmentAttempt>("T1", ex2, 2,  false, 16, nullptr, nullptr, nullptr, &ex1);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);
    attempts.push_back(attempt3);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    int expectedResult = 2;
    int actualResult = moduleAttempt1.getFinalattempts().size();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);

    //chech that needed attempt was added
    bool found = false;
    for (const auto& attempt : moduleAttempt1.getFinalattempts()) {
        if (attempt->getAssessment().getName() == attempt3->getAssessment().getName() &&
            attempt->getNumberOfAttempt() == attempt3->getNumberOfAttempt()) {
            found = true;
            break;
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(SecondAttemptSameTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 14);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16);
    auto attempt3 = std::make_shared<AssessmentAttempt>("T1", ex2, 2,  false, 16, nullptr, nullptr, nullptr, &ex1);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);
    attempts.push_back(attempt3);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    int expectedResult = 2;
    int actualResult = moduleAttempt1.getFinalattempts().size();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);

    //chech that needed attempt was added
    bool found = false;
    for (const auto& attempt : moduleAttempt1.getFinalattempts()) {
        if (attempt->getAssessment().getName() == attempt3->getAssessment().getName() &&
            attempt->getNumberOfAttempt() == attempt3->getNumberOfAttempt()) {
            found = true;
            break;
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(allSecondAttemptsBetterTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 5);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 8);
    auto attempt3 = std::make_shared<AssessmentAttempt>("T1", ex2, 2,  false, 16, nullptr, nullptr, nullptr, &ex1);
    auto attempt4 = std::make_shared<AssessmentAttempt>("T1", cwk2, 2,  false, 16, nullptr, nullptr, nullptr, &cwk1);
    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);
    attempts.push_back(attempt3);
    attempts.push_back(attempt4);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    int expectedResult = 2;
    int actualResult = moduleAttempt1.getFinalattempts().size();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);

    //chech that needed attempt was added
    int foundNeededAttempts=0;
    for (const auto& attempt : moduleAttempt1.getFinalattempts()) {
        if (attempt->getAssessment().getName() == attempt3->getAssessment().getName() &&
            attempt->getNumberOfAttempt() == attempt3->getNumberOfAttempt()) {
            foundNeededAttempts++;
        }
        if(
            attempt->getAssessment().getName() == attempt4->getAssessment().getName() &&
            attempt->getNumberOfAttempt() == attempt4->getNumberOfAttempt()){
            foundNeededAttempts++;
        }
    }

    BOOST_CHECK_EQUAL(foundNeededAttempts, 2);
}


BOOST_AUTO_TEST_CASE(FirstAttemptBetterTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 14);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16);
    auto attempt3 = std::make_shared<AssessmentAttempt>("T1", ex2, 2,  false, 5, nullptr, nullptr, nullptr, &ex1);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);
    attempts.push_back(attempt3);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    int expectedResult = 2;
    int actualResult = moduleAttempt1.getFinalattempts().size();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);

    //chech that needed attempt was added
    bool found = false;
    for (const auto& attempt : moduleAttempt1.getFinalattempts()) {
        if (attempt->getAssessment().getName() == attempt2->getAssessment().getName() &&
            attempt->getNumberOfAttempt() == attempt2->getNumberOfAttempt()) {
            found = true;
            break;
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(allFirstAttemptsBetterTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 9);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 9);
    auto attempt3 = std::make_shared<AssessmentAttempt>("T1", ex2, 2,  false, 6, nullptr, nullptr, nullptr, &ex1);
    auto attempt4 = std::make_shared<AssessmentAttempt>("T1", cwk2, 2,  false, 6, nullptr, nullptr, nullptr, &cwk1);
    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);
    attempts.push_back(attempt3);
    attempts.push_back(attempt4);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    int expectedResult = 2;
    int actualResult = moduleAttempt1.getFinalattempts().size();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);

    //chech that needed attempt was added
    int foundNeededAttempts=0;
    for (const auto& attempt : moduleAttempt1.getFinalattempts()) {
        if (attempt->getAssessment().getName() == attempt1->getAssessment().getName() &&
            attempt->getNumberOfAttempt() == attempt1->getNumberOfAttempt()) {
            foundNeededAttempts++;
        }
        if(
            attempt->getAssessment().getName() == attempt1->getAssessment().getName() &&
            attempt->getNumberOfAttempt() == attempt1->getNumberOfAttempt()){
            foundNeededAttempts++;
        }
    }

    BOOST_CHECK_EQUAL(foundNeededAttempts, 2);
}


//assigning types

BOOST_AUTO_TEST_CASE(AssignOriginalTypeTest) {
    Module mod1("1111", "some module", 20);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 14);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);
    moduleAttempt1.assignTypes();
    std::string expectedResult = "original";
    std::string actualResult = moduleAttempt1.getAttempts()[0]->getType();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(AssignOriginalTypeTestForFirstSit) {
    Module mod1("1111", "some module", 20);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 2, false, 14);
    attempt1->setFinalCode(&AssessmentCodes::S1);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);
    moduleAttempt1.assignTypes();
    std::string expectedResult = "original";
    std::string actualResult = moduleAttempt1.getAttempts()[0]->getType();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(AssignRepeatTestForOne) {
    Module mod1("1111", "some module", 20);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 14);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", cwk2, 2,  false, 6, nullptr, nullptr, nullptr, &cwk1);
    auto attempt3 = std::make_shared<AssessmentAttempt>("T1", cwk2, 3,  false, 6, nullptr, nullptr, nullptr, &cwk1);
    attempt1->setFinalCode(&AssessmentCodes::FA);
    attempt2->setFinalCode(&AssessmentCodes::RE);
    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);
    moduleAttempt1.assignTypes();

    std::string expectedResult = "repeat";
    std::string actualResult = moduleAttempt1.getAttempts()[1]->getType();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}
BOOST_AUTO_TEST_CASE(AssignReferralTestForOneInThree) {
    Module mod1("1111", "some module", 20);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 14);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", cwk2, 2,  false, 6, nullptr, nullptr, nullptr, &cwk1);
    auto attempt3 = std::make_shared<AssessmentAttempt>("T1", cwk2, 3,  false, 6, nullptr, nullptr, nullptr, &cwk1);
    attempt1->setFinalCode(&AssessmentCodes::FA);
    attempt2->setFinalCode(&AssessmentCodes::RE);
    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);
    attempts.push_back(attempt3);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);
    moduleAttempt1.assignTypes();

    std::string expectedResult = "referral";
    std::string actualResult = moduleAttempt1.getAttempts()[2]->getType();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


//aggregate tests
BOOST_AUTO_TEST_CASE(checkNormalAggregatelTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 9);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 7);
    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    double actualResult = moduleAttempt1.calculateAggregate();
    double expectedResult = 8.2;

    BOOST_CHECK_CLOSE( actualResult, expectedResult, percentageAccuracy );
}


BOOST_AUTO_TEST_CASE(unusualPercentageTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 85);
    assessmentList1.emplace(ex1, 15);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 9);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 7);
    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    double actualResult = moduleAttempt1.calculateAggregate();
    double expectedResult = 8.7;

    BOOST_CHECK_CLOSE( actualResult, expectedResult, percentageAccuracy );
}


BOOST_AUTO_TEST_CASE(roundingUpTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 45);
    assessmentList1.emplace(ex1, 55);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 7);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 4);
    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    double actualResult = moduleAttempt1.calculateAggregate();
    double expectedResult = 5.4;

    BOOST_CHECK_CLOSE( actualResult, expectedResult, percentageAccuracy );
}


//when repeating/referral
BOOST_AUTO_TEST_CASE(repeatingOriginalWeightningTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    assessmentList1.emplace(cwk2, 30);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 7);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 4);
    auto attempt3 = std::make_shared<AssessmentAttempt>("T1", cwk2, 2,  false, 10, nullptr, nullptr, nullptr, &cwk1);
    attempt3->setType("repeat");
    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);
    attempts.push_back(attempt3);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    double actualResult = moduleAttempt1.calculateAggregate();
    double expectedResult = 7.6;

    BOOST_CHECK_CLOSE( actualResult, expectedResult, percentageAccuracy );
}

BOOST_AUTO_TEST_CASE(usingFresherWeightingTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    assessmentList1.emplace(cwk2, 30);
    assessmentList1.emplace(ex2, 70);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 7);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 4);
    auto attempt3 = std::make_shared<AssessmentAttempt>("T1", cwk2, 2,  false, 10, nullptr, nullptr, nullptr, &cwk1);
    auto attempt4 = std::make_shared<AssessmentAttempt>("T1", ex2, 2,  false, 8, nullptr, nullptr, nullptr, &ex1);
    attempt3->setType("repeat");
    attempt4->setType("repeat");
    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);
    attempts.push_back(attempt3);
    attempts.push_back(attempt4);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    double actualResult = moduleAttempt1.calculateAggregate();
    double expectedResult = 8.6;

    BOOST_CHECK_CLOSE( actualResult, expectedResult, percentageAccuracy );
}

//determine number of repeated
BOOST_AUTO_TEST_CASE(noRepeatedTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 7);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 4);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);


    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    double actualResult = moduleAttempt1.numberOfRepeated();
    double expectedResult = 0;

    BOOST_CHECK_EQUAL( actualResult, expectedResult );
}

BOOST_AUTO_TEST_CASE(oneRepeatedTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 7);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 4);
    auto attempt3 = std::make_shared<AssessmentAttempt>("T1", cwk2, 2,  false, 10, nullptr, nullptr, nullptr, &cwk1);
    attempt3->setType("repeat");
    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);
    attempts.push_back(attempt3);


    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    double actualResult = moduleAttempt1.numberOfRepeated();
    double expectedResult = 1;

    BOOST_CHECK_EQUAL( actualResult, expectedResult );
}

BOOST_AUTO_TEST_CASE(allRepeatedTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 7);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 4);
    auto attempt3 = std::make_shared<AssessmentAttempt>("T1", cwk2, 2,  false, 10, nullptr, nullptr, nullptr, &cwk1);
    auto attempt4 = std::make_shared<AssessmentAttempt>("T1", ex2, 2,  false, 8, nullptr, nullptr, nullptr, &ex1);
    attempt3->setType("repeat");
    attempt4->setType("repeat");
    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);
    attempts.push_back(attempt3);
    attempts.push_back(attempt4);


    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    double actualResult = moduleAttempt1.numberOfRepeated();
    double expectedResult = 2;

    BOOST_CHECK_EQUAL( actualResult, expectedResult );
}

//check all elements passed
BOOST_AUTO_TEST_CASE(allRassedTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 7);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 5);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);


    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    bool actualResult = moduleAttempt1.checkAllElementsPassed();
    bool expectedResult = true;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(oneNotPassTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 7);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 3);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    bool actualResult = moduleAttempt1.checkAllElementsPassed();
    bool expectedResult = false;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(allNotPassTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 3);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 3);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    bool actualResult = moduleAttempt1.checkAllElementsPassed();
    bool expectedResult = false;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


BOOST_AUTO_TEST_CASE(notSpecialPassTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 9);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 2);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    bool actualResult = moduleAttempt1.determinSpecialPass();

    bool expectedResult = false;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


BOOST_AUTO_TEST_CASE(specialPassTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 60);
    assessmentList1.emplace(ex1, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 9);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 3);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.getGrade();
    bool actualResult = moduleAttempt1.determinSpecialPass();

    bool expectedResult = true;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(notSpecialPassTestMoreThanOneFailed) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);
    assessmentList1.emplace(ex2, 40);
    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 10);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 3);
    auto attempt3 = std::make_shared<AssessmentAttempt>("T1", ex2, 1, false, 3);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);
    attempts.push_back(attempt3);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    bool actualResult = moduleAttempt1.determinSpecialPass();

    bool expectedResult = false;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

//number of not passed
BOOST_AUTO_TEST_CASE(noFailsTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 10);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 5);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    int actualResult = moduleAttempt1.numberOfNotPassed();

    int expectedResult = 0;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(oneFailTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 10);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 2);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    int actualResult = moduleAttempt1.numberOfNotPassed();

    int expectedResult = 1;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(allFailTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 2);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 2);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    int actualResult = moduleAttempt1.numberOfNotPassed();

    int expectedResult = 2;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


//submittedLate

BOOST_AUTO_TEST_CASE(notSubmittedLateTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 2);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 2);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    bool actualResult = moduleAttempt1.getSubmittedLate();

    bool expectedResult = false;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


BOOST_AUTO_TEST_CASE(oneSubmittedLateTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, true, 2);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 2);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    bool actualResult = moduleAttempt1.getSubmittedLate();

    bool expectedResult = true;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(allSubmittedLateTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, true, 2);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, true, 2);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    bool actualResult = moduleAttempt1.getSubmittedLate();

    bool expectedResult = true;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(noMisconductTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 2);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 2);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    bool actualResult = moduleAttempt1.getHadMisconduct();

    bool expectedResult = false;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


BOOST_AUTO_TEST_CASE(oneMisconductTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, true, 2);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16, nullptr, nullptr, &m1, nullptr);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    bool actualResult = moduleAttempt1.getHadMisconduct();

    bool expectedResult = true;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(allhaveMisconductTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1,  false, 16, nullptr, nullptr, &m2, nullptr);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16, nullptr, nullptr, &m1, nullptr);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    bool actualResult = moduleAttempt1.getHadMisconduct();

    bool expectedResult = true;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(noHaveNecTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1,  false, 16, nullptr);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    bool actualResult = moduleAttempt1.getHadNec();

    bool expectedResult = false;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(oneHaveNecTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1,  false, 16, nullptr, &weekUpheldNEC, nullptr, nullptr);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    bool actualResult = moduleAttempt1.getHadNec();

    bool expectedResult = true;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(allhaveNecTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1,  false, 16, nullptr, &weekUpheldNEC, nullptr, nullptr);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16, nullptr, &nextOpportunityUpheldNEC, nullptr, nullptr);


    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    bool actualResult = moduleAttempt1.getHadNec();

    bool expectedResult = true;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}



BOOST_AUTO_TEST_CASE(noNecTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 2);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 2);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    bool actualResult = moduleAttempt1.getHadNec();

    bool expectedResult = false;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


BOOST_AUTO_TEST_CASE(oneNeedFirstSeetTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, true, 2);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16);
    attempt1->setFinalCode(&AssessmentCodes::S1);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    bool actualResult = moduleAttempt1.needFirstSeet();

    bool expectedResult = true;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(allNeedFirstSeetTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1,  false, 16);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16);
    attempt1->setFinalCode(&AssessmentCodes::S1);
    attempt2->setFinalCode(&AssessmentCodes::S1);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    bool actualResult = moduleAttempt1.needFirstSeet();

    bool expectedResult = true;

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


//applyMisconduct
BOOST_AUTO_TEST_CASE(cap0MisconductTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 16, nullptr, nullptr, &m2, nullptr);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;

    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    moduleAttempt1.calculateAggregate();
    moduleAttempt1.applyMisconduct();

    std::string actualGrade = moduleAttempt1.getGrade();
    std::string expectedGrade = "ZERO";

    BOOST_CHECK_EQUAL(actualGrade, expectedGrade);

}

BOOST_AUTO_TEST_CASE(noGradeMisconductTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 60);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 16);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;

    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    moduleAttempt1.calculateAggregate();
    moduleAttempt1.applyMisconduct();

    std::string actualGrade = moduleAttempt1.getGrade();
    std::string expectedGrade = "1EXC";

    BOOST_CHECK_EQUAL(actualGrade, expectedGrade);

}

BOOST_AUTO_TEST_CASE(passCappedMisconductTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 16, nullptr, nullptr, &m2, nullptr);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;

    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();
    moduleAttempt1.applyMisconduct();

    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "PJ";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}

BOOST_AUTO_TEST_CASE(notPassNotFinalAttemptCappedMisconductTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 2, nullptr, nullptr, &m2, nullptr);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 3);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;

    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();
    moduleAttempt1.applyMisconduct();

    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "FC";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}

BOOST_AUTO_TEST_CASE(noCreditsMisconductTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 16, nullptr, nullptr, &m3, nullptr);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 4);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;

    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();
    moduleAttempt1.applyMisconduct();

    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "FN";

    int actualCredits = moduleAttempt1.getCreditsEarned();
    int expectedCredits = 0;

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
    BOOST_CHECK_EQUAL(actualCredits, expectedCredits);
}

BOOST_AUTO_TEST_CASE(terminationOfStudiesMisconductTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 20);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 16, nullptr, nullptr, &m4, nullptr);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 4);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;

    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();
    moduleAttempt1.applyMisconduct();

    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "WD";

    int actualCredits = moduleAttempt1.getCreditsEarned();
    int expectedCredits = 0;

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
    BOOST_CHECK_EQUAL(actualCredits, expectedCredits);
}


//generating code tests
BOOST_AUTO_TEST_CASE(usualPassDecisionTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 60);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 16);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;

    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();


    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "PA";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);

}

BOOST_AUTO_TEST_CASE(specialPassDecisionTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 60);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 16);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 3);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;

    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);

    moduleAttempt1.calculateAggregate();
    moduleAttempt1.getGrade();
    moduleAttempt1.generateCode();

    std::cout<<"was special pass: "<<moduleAttempt1.determinSpecialPass();
    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "PA";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);

}

BOOST_AUTO_TEST_CASE(referredPassDecisionTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 60);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 16);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;

    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);
    moduleAttempt1.setType("referral");
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();


    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "PR";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}


BOOST_AUTO_TEST_CASE(repeatedPassDecisionTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 60);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 16);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;

    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);
    moduleAttempt1.setType("repeat");
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();


    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "PF";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}

BOOST_AUTO_TEST_CASE(manyTriesPassDecisionTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 60);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 16);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 16);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;

    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 3, "202425", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();


    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "PX";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}


BOOST_AUTO_TEST_CASE(submittedLatePassDecisionTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 60);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, true, 10);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 5);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;

    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();


    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "PL";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}

BOOST_AUTO_TEST_CASE(finalFailAfterSecondAttemptWithoutNECDecisionTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 60);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, true, 3);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 2);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;

    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 2, "202425", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();


    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "FN";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}

BOOST_AUTO_TEST_CASE(finalFailAfterManyAttemptsDecisionTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 60);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, true, 3);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 2);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;

    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 3, "202425", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();


    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "FN";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}


BOOST_AUTO_TEST_CASE(referredFailDecisionTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 60);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 3,  nullptr, &nextOpportunityUpheldNEC, nullptr, nullptr);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 2);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;

    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 2, "202425", attempts);
    moduleAttempt1.setType("referral");
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();


    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "F?";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}


BOOST_AUTO_TEST_CASE(repeatedFailDecisionTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 60);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 0, nullptr, &nextOpportunityUpheldNEC, nullptr, nullptr);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 2);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;

    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 2, "202425", attempts);
    moduleAttempt1.setType("repeat");
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();


    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "??";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}

BOOST_AUTO_TEST_CASE(usualFailDecisionTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 40);
    assessmentList1.emplace(ex1, 60);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 0);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", ex1, 1, false, 2);

    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;

    attempts.push_back(attempt1);
    attempts.push_back(attempt2);

    ModuleAttempt moduleAttempt1("T1", mod1, 1, "202425", attempts);
    moduleAttempt1.calculateAggregate();
    moduleAttempt1.generateCode();


    std::string actualCode = moduleAttempt1.getFinalCode()->getCode();
    std::string expectedCode = "??";

    BOOST_CHECK_EQUAL(actualCode, expectedCode);
}


//populate possible decisions




BOOST_AUTO_TEST_SUITE_END()


/*

void ModuleAttempt::populatePossibleDecisions(){
    if (module.getType() == "optional"){
            posibleCodes.push_back(&ModuleCodes::FO);
    }

    int notPassed = 0;
    std::vector<std::shared_ptr<AssessmentAttempt>> finalAttempts = getFinalattempts();
    for (const auto& attempt : finalAttempts) {
            std::string grade = attempt->getGrade();
            if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
            notPassed++;
        }
    }
    if (notPassed>1){ //add referrals, all options + elements codes
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
    if (getHadNec() == true && notPassed ==0){//another second sitting extension - next opportunity
        for (const auto& attempt : finalAttempts) {
             setFinalCode(&ModuleCodes::S1);
        }
    }
}

void ModuleAttempt::referElements(){
    std::vector<std::shared_ptr<AssessmentAttempt>> finalAttempts = getLatestAttempts();//final
    const ModuleCode* code = getFinalCode();
    std::string stringCode = code->getCode();
    if(stringCode=="RR"){
        for (const auto& attempt : finalAttempts){
             std::string grade = attempt->getGrade();
             if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
                //final attempt
                if(attempt->getNumberOfAttempt()==2){
                    //RF
                    attempt->setPossibleDecisions(&AssessmentCodes::RF);
                }
                else if(attempt->getAssessment().getType()=="Exam"){
                    attempt->setPossibleDecisions(&AssessmentCodes::RE);
                    attempt->setPossibleDecisions(&AssessmentCodes::RW);
                }
                else if(attempt->getAssessment().getType()=="Coursework"){
                    attempt->setPossibleDecisions(&AssessmentCodes::RK);
                }
                else if(attempt->getAssessment().getType()=="Test"){
                    attempt->setPossibleDecisions(&AssessmentCodes::RT);
                }
                else{
                    attempt->setPossibleDecisions(&AssessmentCodes::RM);
                }
                attempt->setPossibleDecisions(&AssessmentCodes::RN);
                attempt->setPossibleDecisions(&AssessmentCodes::DF);
             }
        }
    }
}

void ModuleAttempt::failElements(){
    std::vector<std::shared_ptr<AssessmentAttempt>> finalAttempts = getLatestAttempts();
    const ModuleCode* code = getFinalCode();
    std::string stringCode = code->getCode();
    if(stringCode=="FA"){
        for (const auto& attempt : finalAttempts){
             std::string grade = attempt->getGrade();
             if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
                attempt->setPossibleDecisions(&AssessmentCodes::FA);
                attempt->setPossibleDecisions(&AssessmentCodes::FR);
                attempt->setPossibleDecisions(&AssessmentCodes::DF);
            }
        }
    if(stringCode=="FM"){
            for (const auto& attempt : finalAttempts){
                std::string grade = attempt->getGrade();
                if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
                    attempt->setPossibleDecisions(&AssessmentCodes::FW);
                    attempt->setPossibleDecisions(&AssessmentCodes::FR);
                    attempt->setPossibleDecisions(&AssessmentCodes::DF);
                }
            }
        }
    if (stringCode=="FM"){
            for (const auto& attempt : finalAttempts){
                std::string grade = attempt->getGrade();
                if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
                    attempt->setPossibleDecisions(&AssessmentCodes::FA);
                    attempt->setPossibleDecisions(&AssessmentCodes::FW);
                    attempt->setPossibleDecisions(&AssessmentCodes::FR);
                    attempt->setPossibleDecisions(&AssessmentCodes::DF);
                }
            }
        }
    }
    if (stringCode=="FO"){
        for (const auto& attempt : finalAttempts){
            std::string grade = attempt->getGrade();
            if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
                attempt->setPossibleDecisions(&AssessmentCodes::FO);
                attempt->setPossibleDecisions(&AssessmentCodes::DF);
            }
        }
    }
}


void ModuleAttempt::transferMisconduct(){
    for (size_t i = 0; i < attempts.size(); ++i) {
        auto& first = attempts[i];
        std::string firstAssessmentId;
        if(first->getOriginalAttempt()!=nullptr){
            firstAssessmentId = first->getOriginalAttempt()->getId();
        }
        else{
            firstAssessmentId = first->getAssessment().getId();
        }

        int firstAssessmentNumber = first->getNumberOfAttempt();
        if (first->getMisconduct() != nullptr) {
            for (size_t j = i + 1; j < attempts.size(); ++j) {
                auto& second = attempts[j];
                std::string secondAssessmentId = second->getOriginalAttempt()->getId();
                int secondAssessmentNumber = second->getNumberOfAttempt();
                if (firstAssessmentId == secondAssessmentId && firstAssessmentNumber<secondAssessmentNumber) {
                    second->setMisconduct(first->getMisconduct());
                }
            }
        }
    }
}


*/
/*
BOOST_AUTO_TEST_SUITE_END()*/

/*
should I test attempt1.getGrade();? if it is mostly part of gradesystem???
*/

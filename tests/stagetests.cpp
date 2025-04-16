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
#include "../stage.h"
#include "../stageattempt.h"

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


BOOST_AUTO_TEST_SUITE( stageTests )


BOOST_AUTO_TEST_CASE(AssiglTestForOneInThree) {
    BOOST_CHECK_EQUAL(0, 0);
}


BOOST_AUTO_TEST_CASE(assignReferralTypeTest) {
    Module mod1("1111", "some module", 20);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    Stage st1("St1", 120, 1,4,modules, 20);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 14);


    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;
    assessmentAttempts.push_back(attempt1);

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod1, 2, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::RR);
    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.setTypes();

    std::string expectedResult = "referral";
    std::string actualResult = sta1.getAttempts()[1]->getType();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(assignRepeatTypeTest) {
    Module mod1("1111", "some module", 20);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    Stage st1("St1", 120, 1,4,modules, 20);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 14);


    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;
    assessmentAttempts.push_back(attempt1);

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod1, 2, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::FR);
    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.setTypes();

    std::string expectedResult = "repeat";
    std::string actualResult = sta1.getAttempts()[1]->getType();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(severalAssignmentsTest) {
    Module mod1("1111", "some module", 20);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    Stage st1("St1", 120, 1,4,modules, 20);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 14);


    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;
    assessmentAttempts.push_back(attempt1);

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod1, 2, "202425", assessmentAttempts);
    auto moduleAttempt3 = std::make_shared<ModuleAttempt>("T1", mod1, 3, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::FR);
    moduleAttempt2->setFinalCode(&ModuleCodes::RR);
    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    attempts.push_back(moduleAttempt3);
    StageAttempt sta1("T1",st1,attempts);
    sta1.setTypes();

    std::string expectedResult = "repeat";
    std::string actualResult = sta1.getAttempts()[1]->getType();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);

    std::string expectedResult2 = "referral";
    std::string actualResult2 = sta1.getAttempts()[2]->getType();

    BOOST_CHECK_EQUAL(actualResult2, expectedResult2);
}


BOOST_AUTO_TEST_SUITE_END()


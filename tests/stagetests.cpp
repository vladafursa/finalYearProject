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

//calculate aggregate
BOOST_AUTO_TEST_CASE(usualAggregateTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 100);


    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    Stage st1("St1", 20, 1,4,modules, 20);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 14);


    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;
    assessmentAttempts.push_back(attempt1);
    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);


    std::vector<std::shared_ptr<ModuleAttempt>> attempts;
    attempts.push_back(moduleAttempt1);
    StageAttempt sta1("T1",st1,attempts);
    moduleAttempt1->calculateAggregate();

    BOOST_CHECK_EQUAL(sta1.calculateAggregate(), 14);
}

BOOST_AUTO_TEST_CASE(twoAggregateTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 30);
    assessmentList1.emplace(cwk2, 70);


    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);


    Module mod2("1112", "some module", 20);
    mod2.setAssessmentWeights(assessmentList1);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 14);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", cwk2, 1, false, 10);


    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;
    assessmentAttempts.push_back(attempt1);
    assessmentAttempts.push_back(attempt2);

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);
    std::cout << "Mod1 Aggregate: " << moduleAttempt1->calculateAggregate() << "\n";
    std::cout << "Mod2 Aggregate: " << moduleAttempt2->calculateAggregate() << "\n";



    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);

    Stage st1("St1", 40, 1,4,modules, 40);



    std::vector<std::shared_ptr<ModuleAttempt>> attempts;
    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);

     std::cout << "Stage Aggregate: " << sta1.calculateAggregate() << "\n";


    BOOST_CHECK_EQUAL(sta1.calculateAggregate(), 11);
}

BOOST_AUTO_TEST_CASE(determinCompensationPassTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(cwk1, 30);
    assessmentList1.emplace(cwk2, 70);

    Module mod1("1111", "some module", 20);
    mod1.setAssessmentWeights(assessmentList1);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    std::vector<std::shared_ptr<Module>> modules1;
    modules1.push_back(mod1ptr);
    Stage st1("St1", 20, 1, 4, modules1, 20);

    auto attempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 14);
    auto attempt2 = std::make_shared<AssessmentAttempt>("T1", cwk2, 1, false, 10);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts1;
    assessmentAttempts1.push_back(attempt1);
    assessmentAttempts1.push_back(attempt2);

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts1);

    std::vector<std::shared_ptr<ModuleAttempt>> attempts1;
    attempts1.push_back(moduleAttempt1);
    StageAttempt sta1("T1", st1, attempts1);

    moduleAttempt1->calculateAggregate();

    AssessmentWeightsMap assessmentWeights;
    assessmentWeights.emplace(cwk1, 60);
    assessmentWeights.emplace(cwk2, 40);

    Module module("1111", "Some Module", 20);
    Module module2("1112", "Some Module", 20);
    module.setAssessmentWeights(assessmentWeights);
    module2.setAssessmentWeights(assessmentWeights);

    std::shared_ptr<Module> modulePtr = std::make_shared<Module>(module);
    std::shared_ptr<Module> modulePtr2 = std::make_shared<Module>(module2);

    std::vector<std::shared_ptr<Module>> modules2;
    modules2.push_back(modulePtr);
    modules2.push_back(modulePtr2);

    Stage stage("Stage1", 40, 1, 4, modules2, 40);

    auto assessmentAttempt1 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 3);
    auto assessmentAttempt2 = std::make_shared<AssessmentAttempt>("T1", cwk2, 1, false, 4);
    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts2;
    assessmentAttempts2.push_back(assessmentAttempt1);
    assessmentAttempts2.push_back(assessmentAttempt2);

    auto moduleAttempt = std::make_shared<ModuleAttempt>("T1", module, 1, "202425", assessmentAttempts2);
    moduleAttempt->generateCode();

    auto assessmentAttempt3 = std::make_shared<AssessmentAttempt>("T1", cwk1, 1, false, 10);
    auto assessmentAttempt4 = std::make_shared<AssessmentAttempt>("T1", cwk2, 1, false, 12);
    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts3;
    assessmentAttempts3.push_back(assessmentAttempt3);
    assessmentAttempts3.push_back(assessmentAttempt4);

    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", module2, 1, "202425", assessmentAttempts3);
    moduleAttempt2->generateCode();

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt);
    moduleAttempts.push_back(moduleAttempt2);

    StageAttempt stageAttempt("T1", stage, moduleAttempts);

    std::cout << "Module Attempt 1 Aggregate: " << moduleAttempt->calculateAggregate() << std::endl;
    std::cout << "Module Attempt 2 Aggregate: " << moduleAttempt2->calculateAggregate() << std::endl;
    std::cout << "Stage Aggregate: " << stageAttempt.calculateAggregate() << std::endl;

    stageAttempt.getGrade();
    stageAttempt.setTypes();
    stageAttempt.determinCompensationPass();

    // Ensure the possible codes are filled correctly
    BOOST_CHECK(!moduleAttempt->getPossibleCodes().empty());

}


BOOST_AUTO_TEST_CASE(allFirstAttemptsTest) {

    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1111", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4,modules, 20);



    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    int expectedResult = 2;
    int actualResult =  sta1.getFinalattempts().size();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(oneSecondAttemptTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    Stage st1("St1", 120, 1,4,modules, 20);



    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;


    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod1, 2, "202425", assessmentAttempts);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    int expectedResult = 1;
    int actualResult =  sta1.getFinalattempts().size();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);


    //chech that needed attempt was added
    int foundNeededAttempts=0;
    for (const auto& attempt : sta1.getFinalattempts()) {
        if (attempt->getModule().getCode() == moduleAttempt2->getModule().getCode() &&
            attempt->getNumberOfAttempt() == moduleAttempt2->getNumberOfAttempt()) {
            foundNeededAttempts++;
        }
    }

    BOOST_CHECK_EQUAL(foundNeededAttempts, 1);
}



BOOST_AUTO_TEST_CASE(allSecondAttemptTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4,modules, 20);



    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod1, 2, "202425", assessmentAttempts);
    auto moduleAttempt3 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);
    auto moduleAttempt4 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);


    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    attempts.push_back(moduleAttempt3);
    attempts.push_back(moduleAttempt4);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    int expectedResult = 2;
    int actualResult =  sta1.getFinalattempts().size();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);


    //chech that needed attempt was added
    int foundNeededAttempts=0;

    for (const auto& attempt : sta1.getFinalattempts()) {
        if ((attempt->getModule().getCode() == moduleAttempt2->getModule().getCode() &&
             attempt->getNumberOfAttempt() == moduleAttempt2->getNumberOfAttempt()) ||
            (attempt->getModule().getCode() == moduleAttempt4->getModule().getCode() &&
             attempt->getNumberOfAttempt() == moduleAttempt4->getNumberOfAttempt())) {
            foundNeededAttempts++;
        }
    }
    BOOST_CHECK_EQUAL(foundNeededAttempts, 2);
}


BOOST_AUTO_TEST_CASE(allPassedWithPACodeTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::PA);
    moduleAttempt2->setFinalCode(&ModuleCodes::PA);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    bool expectedResult = true;
    bool actualResult =  sta1.checkAllModulesPassed();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);

}

BOOST_AUTO_TEST_CASE(allPassedWithDifferentPassCodesTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::PA);
    moduleAttempt2->setFinalCode(&ModuleCodes::PC);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    bool expectedResult = true;
    bool actualResult =  sta1.checkAllModulesPassed();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);

}

BOOST_AUTO_TEST_CASE(oneReferredAnotherPassTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::PA);
    moduleAttempt2->setFinalCode(&ModuleCodes::RR);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    bool expectedResult = false;
    bool actualResult =  sta1.checkAllModulesPassed();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);

}

BOOST_AUTO_TEST_CASE(oneFailAnotherPassTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::PA);
    moduleAttempt2->setFinalCode(&ModuleCodes::F1);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    bool expectedResult = false;
    bool actualResult =  sta1.checkAllModulesPassed();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);

}


BOOST_AUTO_TEST_CASE(allNotPassDifferentCodesTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::RR);
    moduleAttempt2->setFinalCode(&ModuleCodes::F1);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    bool expectedResult = false;
    bool actualResult =  sta1.checkAllModulesPassed();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(allNotPassSameCodesTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::RR);
    moduleAttempt2->setFinalCode(&ModuleCodes::RR);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    bool expectedResult = false;
    bool actualResult =  sta1.checkAllModulesPassed();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


BOOST_AUTO_TEST_CASE(allPassCheckFailTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::PA);
    moduleAttempt2->setFinalCode(&ModuleCodes::PA);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    int expectedResult = 0;
    int actualResult =  sta1.checkFail();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


BOOST_AUTO_TEST_CASE(oneFailCheckFailTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::RR);
    moduleAttempt2->setFinalCode(&ModuleCodes::F1);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    int expectedResult = 1;
    int actualResult =  sta1.checkFail();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(allFailCheckFailTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::FR);
    moduleAttempt2->setFinalCode(&ModuleCodes::F1);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    int expectedResult = 2;
    int actualResult =  sta1.checkFail();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


BOOST_AUTO_TEST_CASE(allPassCheckReferredTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::PA);
    moduleAttempt2->setFinalCode(&ModuleCodes::PA);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    int expectedResult = 0;
    int actualResult =  sta1.checkReferred();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


BOOST_AUTO_TEST_CASE(oneReferredCheckReferredTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::RR);
    moduleAttempt2->setFinalCode(&ModuleCodes::F1);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    int expectedResult = 1;
    int actualResult =  sta1.checkReferred();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(allReferredCheckReferredTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::RR);
    moduleAttempt2->setFinalCode(&ModuleCodes::RR);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    int expectedResult = 2;
    int actualResult =  sta1.checkReferred();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}



BOOST_AUTO_TEST_CASE(allPassCheckFirstSitsTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::PA);
    moduleAttempt2->setFinalCode(&ModuleCodes::PA);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    int expectedResult = 0;
    int actualResult =  sta1.checkFirstSeats();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


BOOST_AUTO_TEST_CASE(oneFirstSitCheckFirstSitsTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::PA);
    moduleAttempt2->setFinalCode(&ModuleCodes::S1);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    int expectedResult = 1;
    int actualResult =  sta1.checkFirstSeats();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(allFirstSitsCheckFirstSitsTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::S1);
    moduleAttempt2->setFinalCode(&ModuleCodes::S1);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();


    int expectedResult = 2;
    int actualResult =  sta1.checkFirstSeats();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


//code distribution tests
BOOST_AUTO_TEST_CASE(allModulesPassedFirstYearProgressionTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1, 4, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::PA);
    moduleAttempt2->setFinalCode(&ModuleCodes::PA);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();
    sta1.generateCode();


    std::string expectedResult = "P1";
    std::string actualResult =  sta1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(allModulesPassedFinalYearProgressionTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 3, 6, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::PA);
    moduleAttempt2->setFinalCode(&ModuleCodes::PA);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();
    sta1.generateCode();


    std::string expectedResult = "SO";
    std::string actualResult =  sta1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(firstSitInAugProgressionTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1, 4, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::PA);
    moduleAttempt2->setFinalCode(&ModuleCodes::S2);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();
    sta1.generateCode();


    std::string expectedResult = "R1";
    std::string actualResult =  sta1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(firstSitNextYearProgressionTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 3, 6, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::PA);
    moduleAttempt2->setFinalCode(&ModuleCodes::S3);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();
    sta1.generateCode();


    std::string expectedResult = "F1";
    std::string actualResult =  sta1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(variousFirstSitProgressionTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 3, 6, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::S2);
    moduleAttempt2->setFinalCode(&ModuleCodes::S3);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();
    sta1.generateCode();


    std::string expectedResult = "F1";
    std::string actualResult =  sta1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


BOOST_AUTO_TEST_CASE(allowedDefficiencyProgressionTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 40, 3, 6, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::RR);
    moduleAttempt1->setCreditsEarned(0);
    moduleAttempt2->setFinalCode(&ModuleCodes::PA);
    moduleAttempt2->setCreditsEarned(20);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();
    sta1.getCreditsEarned();
    sta1.generateCode();


    std::string expectedResult = "PD";
    std::string actualResult =  sta1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(notAllowedDefficiencyProgressionTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    Module mod3("1113", "some module", 20);

    std::shared_ptr<Module> mod3ptr = std::make_shared<Module>(mod3);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    modules.push_back(mod3ptr);
    Stage st1("St1", 60, 3, 6, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);
    auto moduleAttempt3 = std::make_shared<ModuleAttempt>("T1", mod3, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::RR);
    moduleAttempt1->setCreditsEarned(0);
    moduleAttempt2->setFinalCode(&ModuleCodes::PA);
    moduleAttempt2->setCreditsEarned(20);
    moduleAttempt3->setFinalCode(&ModuleCodes::F1);
    moduleAttempt3->setCreditsEarned(0);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    attempts.push_back(moduleAttempt3);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();
    sta1.generateCode();

    bool expectedResult = false;

    bool actualResult;
    if(sta1.getFinalCode()->getCode()!="PD"){
        actualResult = false;
    }
    else{
        actualResult = true;
    }
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}


BOOST_AUTO_TEST_CASE(referredProgressionTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    Module mod3("1113", "some module", 20);

    std::shared_ptr<Module> mod3ptr = std::make_shared<Module>(mod3);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    modules.push_back(mod3ptr);
    Stage st1("St1", 60, 3, 6, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);
    auto moduleAttempt3 = std::make_shared<ModuleAttempt>("T1", mod3, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::RR);
    moduleAttempt1->setCreditsEarned(0);
    moduleAttempt2->setFinalCode(&ModuleCodes::PA);
    moduleAttempt2->setCreditsEarned(20);
    moduleAttempt3->setFinalCode(&ModuleCodes::RR);
    moduleAttempt3->setCreditsEarned(0);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    attempts.push_back(moduleAttempt3);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();
    sta1.getCreditsEarned();
    sta1.generateCode();


    std::string expectedResult = "RF";
    std::string actualResult =  sta1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
    BOOST_CHECK_EQUAL(sta1.getPossibleCodes().size(), 5);

    BOOST_CHECK_EQUAL(sta1.getPossibleCodes()[0]->getCode(), "RA");
    BOOST_CHECK_EQUAL(sta1.getPossibleCodes()[1]->getCode(), "RN");
    BOOST_CHECK_EQUAL(sta1.getPossibleCodes()[2]->getCode(), "RS");
    BOOST_CHECK_EQUAL(sta1.getPossibleCodes()[3]->getCode(), "DF");
    BOOST_CHECK_EQUAL(sta1.getPossibleCodes()[4]->getCode(), "PR");
}


BOOST_AUTO_TEST_CASE(mixOfRferralsAndFailuresProgressionTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    Module mod3("1113", "some module", 20);

    std::shared_ptr<Module> mod3ptr = std::make_shared<Module>(mod3);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    modules.push_back(mod3ptr);
    Stage st1("St1", 60, 3, 6, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);
    auto moduleAttempt3 = std::make_shared<ModuleAttempt>("T1", mod3, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::RR);
    moduleAttempt1->setCreditsEarned(0);
    moduleAttempt2->setFinalCode(&ModuleCodes::PA);
    moduleAttempt2->setCreditsEarned(20);
    moduleAttempt3->setFinalCode(&ModuleCodes::F1);
    moduleAttempt3->setCreditsEarned(0);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    attempts.push_back(moduleAttempt3);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();
    sta1.getCreditsEarned();
    sta1.generateCode();


    std::string expectedResult = "RR";
    std::string actualResult =  sta1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);

    BOOST_CHECK_EQUAL(sta1.getPossibleCodes().size(), 2);

    BOOST_CHECK_EQUAL(sta1.getPossibleCodes()[0]->getCode(), "DF");
    BOOST_CHECK_EQUAL(sta1.getPossibleCodes()[1]->getCode(), "FR");
}

BOOST_AUTO_TEST_CASE(someFailuresProgressionTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    Module mod3("1113", "some module", 20);

    std::shared_ptr<Module> mod3ptr = std::make_shared<Module>(mod3);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    modules.push_back(mod3ptr);
    Stage st1("St1", 60, 3, 6, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);
    auto moduleAttempt3 = std::make_shared<ModuleAttempt>("T1", mod3, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::F1);
    moduleAttempt1->setCreditsEarned(0);
    moduleAttempt2->setFinalCode(&ModuleCodes::PA);
    moduleAttempt2->setCreditsEarned(20);
    moduleAttempt3->setFinalCode(&ModuleCodes::F1);
    moduleAttempt3->setCreditsEarned(0);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    attempts.push_back(moduleAttempt3);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();
    sta1.getCreditsEarned();
    sta1.generateCode();


    std::string expectedResult = "FR";
    std::string actualResult =  sta1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);

    BOOST_CHECK_EQUAL(sta1.getPossibleCodes().size(), 3);

    BOOST_CHECK_EQUAL(sta1.getPossibleCodes()[0]->getCode(), "DF");
    BOOST_CHECK_EQUAL(sta1.getPossibleCodes()[1]->getCode(), "FY");
    BOOST_CHECK_EQUAL(sta1.getPossibleCodes()[2]->getCode(), "FD");
}



BOOST_AUTO_TEST_CASE(allFailuresProgressionTest) {
    Module mod1("1111", "some module", 20);

    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 20);

    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);

    Module mod3("1113", "some module", 20);

    std::shared_ptr<Module> mod3ptr = std::make_shared<Module>(mod3);

    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    modules.push_back(mod3ptr);
    Stage st1("St1", 60, 3, 6, modules, 20);

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    std::vector<std::shared_ptr<ModuleAttempt>> attempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 1, "202425", assessmentAttempts);
    auto moduleAttempt3 = std::make_shared<ModuleAttempt>("T1", mod3, 1, "202425", assessmentAttempts);

    moduleAttempt1->setFinalCode(&ModuleCodes::F1);
    moduleAttempt1->setCreditsEarned(0);
    moduleAttempt2->setFinalCode(&ModuleCodes::F1);
    moduleAttempt2->setCreditsEarned(0);
    moduleAttempt3->setFinalCode(&ModuleCodes::F1);
    moduleAttempt3->setCreditsEarned(0);

    attempts.push_back(moduleAttempt1);
    attempts.push_back(moduleAttempt2);
    attempts.push_back(moduleAttempt3);
    StageAttempt sta1("T1",st1,attempts);
    sta1.getFinalattempts();
    sta1.getCreditsEarned();
    sta1.generateCode();


    std::string expectedResult = "FT";
    std::string actualResult =  sta1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}
BOOST_AUTO_TEST_SUITE_END()




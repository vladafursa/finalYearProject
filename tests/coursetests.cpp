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
#include "../course.h"
#include "../courseattempt.h"


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

BOOST_AUTO_TEST_CASE(simpleProgressionTest) {
    Module mod1("1111", "some module", 60);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 60);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1,4,modules, 20);
    std::shared_ptr<Stage> st1ptr = std::make_shared<Stage>(st1);
    Stage st2("St2", 120, 2,5,modules, 20);
    std::shared_ptr<Stage> st2ptr = std::make_shared<Stage>(st2);
    std::vector<std::shared_ptr<Stage>> stages;
    stages.push_back(st1ptr);
    stages.push_back(st2ptr);
    Course c1("COMP1", "Computer Science", stages, "Bachelor", "FullTime");

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);
    moduleAttempt1->setCreditsEarned(60);
    moduleAttempt2->setCreditsEarned(60);

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt1);
    moduleAttempts.push_back(moduleAttempt2);

    auto StageAttempt1 = std::make_shared<StageAttempt>("T1",st1,moduleAttempts);
    auto StageAttempt2 = std::make_shared<StageAttempt>("T1",st2,moduleAttempts);
    StageAttempt1->getFinalattempts();
    StageAttempt2->getFinalattempts();

    std::vector<std::shared_ptr<StageAttempt>> stageAttempts;
    stageAttempts.push_back(StageAttempt1);
    stageAttempts.push_back(StageAttempt2);

    CourseAttempt ca1("T1", c1, stageAttempts);
    ca1.setStartClassification(ca1.getStartClassification());
    ca1.calculateProgression();

    BOOST_CHECK_EQUAL(StageAttempt2->getPossibleCodes().size(), 0);
}



BOOST_AUTO_TEST_CASE(notAllowedProgressionTest) {
    Module mod1("1111", "some module", 60);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 60);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 1, 4,modules, 20);
    std::shared_ptr<Stage> st1ptr = std::make_shared<Stage>(st1);
    Stage st2("St2", 120, 2, 5, modules, 20);
    std::shared_ptr<Stage> st2ptr = std::make_shared<Stage>(st2);
    std::vector<std::shared_ptr<Stage>> stages;
    stages.push_back(st1ptr);
    stages.push_back(st2ptr);
    Course c1("COMP1", "Computer Science", stages, "Bachelor", "FullTime");

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);
    moduleAttempt1->setCreditsEarned(20);
    moduleAttempt2->setCreditsEarned(60);

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt1);
    moduleAttempts.push_back(moduleAttempt2);
    auto StageAttempt1 = std::make_shared<StageAttempt>("T1",st1,moduleAttempts);
    auto StageAttempt2 = std::make_shared<StageAttempt>("T1",st2,moduleAttempts);
    StageAttempt1->getFinalattempts();
    StageAttempt2->getFinalattempts();

    std::vector<std::shared_ptr<StageAttempt>> stageAttempts;
    stageAttempts.push_back(StageAttempt1);
    stageAttempts.push_back(StageAttempt2);

    CourseAttempt ca1("T1", c1, stageAttempts);
    ca1.setStartClassification(ca1.getStartClassification());
    ca1.calculateProgression();

    BOOST_CHECK_EQUAL(StageAttempt2->getPossibleCodes().size(), 6);
    BOOST_CHECK_EQUAL(StageAttempt2->getPossibleCodes()[0]->getCode(), "FC");
    BOOST_CHECK_EQUAL(StageAttempt2->getPossibleCodes()[1]->getCode(), "FD");
    BOOST_CHECK_EQUAL(StageAttempt2->getPossibleCodes()[2]->getCode(), "DF");
    BOOST_CHECK_EQUAL(StageAttempt2->getPossibleCodes()[3]->getCode(), "RE");
    BOOST_CHECK_EQUAL(StageAttempt2->getPossibleCodes()[4]->getCode(), "RP");
    BOOST_CHECK_EQUAL(StageAttempt2->getPossibleCodes()[5]->getCode(), "PG");
}




//aggregate tests
BOOST_AUTO_TEST_CASE(aggregateTest) {
    Module mod1("1111", "some module", 60);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 60);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 2, 5,modules, 20);
    std::shared_ptr<Stage> st1ptr = std::make_shared<Stage>(st1);
    Stage st2("St2", 120, 3, 6, modules, 20);
    std::shared_ptr<Stage> st2ptr = std::make_shared<Stage>(st2);
    std::vector<std::shared_ptr<Stage>> stages;
    stages.push_back(st1ptr);
    stages.push_back(st2ptr);
    Course c1("COMP1", "Computer Science", stages, "Bachelor", "FullTime");

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);
    moduleAttempt1->setCreditsEarned(20);
    moduleAttempt2->setCreditsEarned(60);

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt1);
    moduleAttempts.push_back(moduleAttempt2);
    auto StageAttempt1 = std::make_shared<StageAttempt>("T1",st1,moduleAttempts);
    auto StageAttempt2 = std::make_shared<StageAttempt>("T1",st2,moduleAttempts);
    StageAttempt1->setAggregate(6.7);
    StageAttempt2->setAggregate(8.2);


    std::vector<std::shared_ptr<StageAttempt>> stageAttempts;
    stageAttempts.push_back(StageAttempt1);
    stageAttempts.push_back(StageAttempt2);

    CourseAttempt ca1("T1", c1, stageAttempts);
    ca1.getAttempts();

    BOOST_CHECK_EQUAL(ca1.calculateAggregate(), 7.8);
}

//generating code


BOOST_AUTO_TEST_CASE(bachelorAward22Test) {
    Module mod1("1111", "some module", 60);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 60);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 2, 5,modules, 20);
    std::shared_ptr<Stage> st1ptr = std::make_shared<Stage>(st1);
    Stage st2("St2", 120, 3, 6, modules, 20);
    std::shared_ptr<Stage> st2ptr = std::make_shared<Stage>(st2);
    std::vector<std::shared_ptr<Stage>> stages;
    stages.push_back(st1ptr);
    stages.push_back(st2ptr);
    Course c1("COMP1", "Computer Science", stages, "Bachelor", "FullTime");

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);
    moduleAttempt1->setCreditsEarned(20);
    moduleAttempt2->setCreditsEarned(60);

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt1);
    moduleAttempts.push_back(moduleAttempt2);
    auto StageAttempt1 = std::make_shared<StageAttempt>("T1",st1,moduleAttempts);
    auto StageAttempt2 = std::make_shared<StageAttempt>("T1",st2,moduleAttempts);
    StageAttempt1->setAggregate(6.7);
    StageAttempt2->setAggregate(8.2);


    std::vector<std::shared_ptr<StageAttempt>> stageAttempts;
    stageAttempts.push_back(StageAttempt1);
    stageAttempts.push_back(StageAttempt2);

    CourseAttempt ca1("T1", c1, stageAttempts);
    ca1.getAttempts();
    ca1.calculateAggregate();
    ca1.setEarnedCredits(360);
    ca1.generateCode();
    std::string expectedResult = "22";
    std::string actualResult = ca1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
    BOOST_CHECK_EQUAL(StageAttempt2->getFinalCode()->getCode(), "PA");
}



BOOST_AUTO_TEST_CASE(bachelorAward1Test) {
    Module mod1("1111", "some module", 60);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 60);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 2, 5,modules, 20);
    std::shared_ptr<Stage> st1ptr = std::make_shared<Stage>(st1);
    Stage st2("St2", 120, 3, 6, modules, 20);
    std::shared_ptr<Stage> st2ptr = std::make_shared<Stage>(st2);
    std::vector<std::shared_ptr<Stage>> stages;
    stages.push_back(st1ptr);
    stages.push_back(st2ptr);
    Course c1("COMP1", "Computer Science", stages, "Bachelor", "FullTime");

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);
    moduleAttempt1->setCreditsEarned(20);
    moduleAttempt2->setCreditsEarned(60);

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt1);
    moduleAttempts.push_back(moduleAttempt2);
    auto StageAttempt1 = std::make_shared<StageAttempt>("T1",st1,moduleAttempts);
    auto StageAttempt2 = std::make_shared<StageAttempt>("T1",st2,moduleAttempts);
    StageAttempt1->setAggregate(15);
    StageAttempt2->setAggregate(16);


    std::vector<std::shared_ptr<StageAttempt>> stageAttempts;
    stageAttempts.push_back(StageAttempt1);
    stageAttempts.push_back(StageAttempt2);

    CourseAttempt ca1("T1", c1, stageAttempts);
    ca1.getAttempts();
    ca1.calculateAggregate();
    ca1.setEarnedCredits(360);
    ca1.generateCode();
    std::string expectedResult = "10";
    std::string actualResult = ca1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
    BOOST_CHECK_EQUAL(StageAttempt2->getFinalCode()->getCode(), "PA");
}

BOOST_AUTO_TEST_CASE(bachelorAward21Test) {
    Module mod1("1111", "some module", 60);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 60);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 2, 5,modules, 20);
    std::shared_ptr<Stage> st1ptr = std::make_shared<Stage>(st1);
    Stage st2("St2", 120, 3, 6, modules, 20);
    std::shared_ptr<Stage> st2ptr = std::make_shared<Stage>(st2);
    std::vector<std::shared_ptr<Stage>> stages;
    stages.push_back(st1ptr);
    stages.push_back(st2ptr);
    Course c1("COMP1", "Computer Science", stages, "Bachelor", "FullTime");

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);
    moduleAttempt1->setCreditsEarned(20);
    moduleAttempt2->setCreditsEarned(60);

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt1);
    moduleAttempts.push_back(moduleAttempt2);
    auto StageAttempt1 = std::make_shared<StageAttempt>("T1",st1,moduleAttempts);
    auto StageAttempt2 = std::make_shared<StageAttempt>("T1",st2,moduleAttempts);
    StageAttempt1->setAggregate(10);
    StageAttempt2->setAggregate(12);


    std::vector<std::shared_ptr<StageAttempt>> stageAttempts;
    stageAttempts.push_back(StageAttempt1);
    stageAttempts.push_back(StageAttempt2);

    CourseAttempt ca1("T1", c1, stageAttempts);
    ca1.getAttempts();
    ca1.calculateAggregate();
    ca1.setEarnedCredits(360);
    ca1.generateCode();
    std::string expectedResult = "21";
    std::string actualResult = ca1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
    BOOST_CHECK_EQUAL(StageAttempt2->getFinalCode()->getCode(), "PA");
}

BOOST_AUTO_TEST_CASE(bachelorAward3Test) {
    Module mod1("1111", "some module", 60);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 60);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 2, 5,modules, 20);
    std::shared_ptr<Stage> st1ptr = std::make_shared<Stage>(st1);
    Stage st2("St2", 120, 3, 6, modules, 20);
    std::shared_ptr<Stage> st2ptr = std::make_shared<Stage>(st2);
    std::vector<std::shared_ptr<Stage>> stages;
    stages.push_back(st1ptr);
    stages.push_back(st2ptr);
    Course c1("COMP1", "Computer Science", stages, "Bachelor", "FullTime");

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);
    moduleAttempt1->setCreditsEarned(20);
    moduleAttempt2->setCreditsEarned(60);

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt1);
    moduleAttempts.push_back(moduleAttempt2);
    auto StageAttempt1 = std::make_shared<StageAttempt>("T1",st1,moduleAttempts);
    auto StageAttempt2 = std::make_shared<StageAttempt>("T1",st2,moduleAttempts);
    StageAttempt1->setAggregate(5);
    StageAttempt2->setAggregate(4);


    std::vector<std::shared_ptr<StageAttempt>> stageAttempts;
    stageAttempts.push_back(StageAttempt1);
    stageAttempts.push_back(StageAttempt2);

    CourseAttempt ca1("T1", c1, stageAttempts);
    ca1.getAttempts();
    ca1.calculateAggregate();
    ca1.setEarnedCredits(360);
    ca1.generateCode();
    std::string expectedResult = "30";
    std::string actualResult = ca1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
    BOOST_CHECK_EQUAL(StageAttempt2->getFinalCode()->getCode(), "PA");
}


BOOST_AUTO_TEST_CASE(bachelorNotEnoughCreditsTest) {
    Module mod1("1111", "some module", 60);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 60);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 2, 5,modules, 20);
    std::shared_ptr<Stage> st1ptr = std::make_shared<Stage>(st1);
    Stage st2("St2", 120, 3, 6, modules, 20);
    std::shared_ptr<Stage> st2ptr = std::make_shared<Stage>(st2);
    std::vector<std::shared_ptr<Stage>> stages;
    stages.push_back(st1ptr);
    stages.push_back(st2ptr);
    Course c1("COMP1", "Computer Science", stages, "Bachelor", "FullTime");

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);
    moduleAttempt1->setCreditsEarned(20);
    moduleAttempt2->setCreditsEarned(60);

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt1);
    moduleAttempts.push_back(moduleAttempt2);
    auto StageAttempt1 = std::make_shared<StageAttempt>("T1",st1,moduleAttempts);
    auto StageAttempt2 = std::make_shared<StageAttempt>("T1",st2,moduleAttempts);
    StageAttempt1->setAggregate(13);
    StageAttempt2->setAggregate(14);


    std::vector<std::shared_ptr<StageAttempt>> stageAttempts;
    stageAttempts.push_back(StageAttempt1);
    stageAttempts.push_back(StageAttempt2);

    CourseAttempt ca1("T1", c1, stageAttempts);

    ca1.getAttempts();
    ca1.calculateAggregate();
    ca1.setEarnedCredits(320);
    ca1.generateCode();
    BOOST_CHECK_EQUAL(StageAttempt2->getFinalCode()->getCode(), "RD");
}


BOOST_AUTO_TEST_CASE(ordinaryDistinctionTest) {
    Module mod1("1111", "some module", 60);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 60);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 2, 5,modules, 20);
    std::shared_ptr<Stage> st1ptr = std::make_shared<Stage>(st1);
    Stage st2("St2", 120, 3, 6, modules, 20);
    std::shared_ptr<Stage> st2ptr = std::make_shared<Stage>(st2);
    std::vector<std::shared_ptr<Stage>> stages;
    stages.push_back(st1ptr);
    stages.push_back(st2ptr);
    Course c1("COMP1", "Computer Science", stages, "Bachelor", "FullTime");

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);
    moduleAttempt1->setCreditsEarned(20);
    moduleAttempt2->setCreditsEarned(60);

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt1);
    moduleAttempts.push_back(moduleAttempt2);
    auto StageAttempt1 = std::make_shared<StageAttempt>("T1",st1,moduleAttempts);
    auto StageAttempt2 = std::make_shared<StageAttempt>("T1",st2,moduleAttempts);
    StageAttempt1->setAggregate(13);
    StageAttempt2->setAggregate(14);


    std::vector<std::shared_ptr<StageAttempt>> stageAttempts;
    stageAttempts.push_back(StageAttempt1);
    stageAttempts.push_back(StageAttempt2);

    CourseAttempt ca1("T1", c1, stageAttempts);
    ca1.setStartClassification("Ordinary");
    ca1.getAttempts();
    ca1.calculateAggregate();
    ca1.setEarnedCredits(320);
    ca1.generateCode();
    std::string expectedResult = "DD";
    std::string actualResult = ca1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
    BOOST_CHECK_EQUAL(StageAttempt2->getFinalCode()->getCode(), "PA");
}



BOOST_AUTO_TEST_CASE(ordinaryUsualTest) {
    Module mod1("1111", "some module", 60);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 60);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 2, 5,modules, 20);
    std::shared_ptr<Stage> st1ptr = std::make_shared<Stage>(st1);
    Stage st2("St2", 120, 3, 6, modules, 20);
    std::shared_ptr<Stage> st2ptr = std::make_shared<Stage>(st2);
    std::vector<std::shared_ptr<Stage>> stages;
    stages.push_back(st1ptr);
    stages.push_back(st2ptr);
    Course c1("COMP1", "Computer Science", stages, "Bachelor", "FullTime");

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);
    moduleAttempt1->setCreditsEarned(20);
    moduleAttempt2->setCreditsEarned(60);

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt1);
    moduleAttempts.push_back(moduleAttempt2);
    auto StageAttempt1 = std::make_shared<StageAttempt>("T1",st1,moduleAttempts);
    auto StageAttempt2 = std::make_shared<StageAttempt>("T1",st2,moduleAttempts);
    StageAttempt1->setAggregate(10);
    StageAttempt2->setAggregate(9);


    std::vector<std::shared_ptr<StageAttempt>> stageAttempts;
    stageAttempts.push_back(StageAttempt1);
    stageAttempts.push_back(StageAttempt2);

    CourseAttempt ca1("T1", c1, stageAttempts);
    ca1.setStartClassification("Ordinary");
    ca1.getAttempts();
    ca1.calculateAggregate();
    ca1.setEarnedCredits(320);
    ca1.generateCode();
    std::string expectedResult = "DN";
    std::string actualResult = ca1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
    BOOST_CHECK_EQUAL(StageAttempt2->getFinalCode()->getCode(), "PA");
}


BOOST_AUTO_TEST_CASE(ordinaryNotEnoughCreditsTest) {
    Module mod1("1111", "some module", 60);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 60);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 2, 5,modules, 20);
    std::shared_ptr<Stage> st1ptr = std::make_shared<Stage>(st1);
    Stage st2("St2", 120, 3, 6, modules, 20);
    std::shared_ptr<Stage> st2ptr = std::make_shared<Stage>(st2);
    std::vector<std::shared_ptr<Stage>> stages;
    stages.push_back(st1ptr);
    stages.push_back(st2ptr);
    Course c1("COMP1", "Computer Science", stages, "Bachelor", "FullTime");

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);
    moduleAttempt1->setCreditsEarned(20);
    moduleAttempt2->setCreditsEarned(60);

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt1);
    moduleAttempts.push_back(moduleAttempt2);
    auto StageAttempt1 = std::make_shared<StageAttempt>("T1",st1,moduleAttempts);
    auto StageAttempt2 = std::make_shared<StageAttempt>("T1",st2,moduleAttempts);
    StageAttempt1->setAggregate(13);
    StageAttempt2->setAggregate(14);


    std::vector<std::shared_ptr<StageAttempt>> stageAttempts;
    stageAttempts.push_back(StageAttempt1);
    stageAttempts.push_back(StageAttempt2);

    CourseAttempt ca1("T1", c1, stageAttempts);

    ca1.getAttempts();
    ca1.calculateAggregate();
    ca1.setEarnedCredits(280);
    ca1.generateCode();
    BOOST_CHECK_EQUAL(StageAttempt2->getFinalCode()->getCode(), "RN");
}


BOOST_AUTO_TEST_CASE(DipHEDistinctionTest) {
    Module mod1("1111", "some module", 60);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 60);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 2, 5,modules, 20);
    std::shared_ptr<Stage> st1ptr = std::make_shared<Stage>(st1);
    Stage st2("St2", 120, 3, 6, modules, 20);
    std::shared_ptr<Stage> st2ptr = std::make_shared<Stage>(st2);
    std::vector<std::shared_ptr<Stage>> stages;
    stages.push_back(st1ptr);
    stages.push_back(st2ptr);
    Course c1("COMP1", "Computer Science", stages, "Bachelor", "FullTime");

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);
    moduleAttempt1->setCreditsEarned(20);
    moduleAttempt2->setCreditsEarned(60);

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt1);
    moduleAttempts.push_back(moduleAttempt2);
    auto StageAttempt1 = std::make_shared<StageAttempt>("T1",st1,moduleAttempts);
    auto StageAttempt2 = std::make_shared<StageAttempt>("T1",st2,moduleAttempts);
    StageAttempt1->setAggregate(13);
    StageAttempt2->setAggregate(14);


    std::vector<std::shared_ptr<StageAttempt>> stageAttempts;
    stageAttempts.push_back(StageAttempt1);
    stageAttempts.push_back(StageAttempt2);

    CourseAttempt ca1("T1", c1, stageAttempts);
    ca1.setStartClassification("DipHE");
    ca1.getAttempts();
    ca1.calculateAggregate();
    ca1.setEarnedCredits(280);
    ca1.generateCode();
    std::string expectedResult = "ID";
    std::string actualResult = ca1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
    BOOST_CHECK_EQUAL(StageAttempt2->getFinalCode()->getCode(), "PA");
}



BOOST_AUTO_TEST_CASE(DipHEUsualTest) {
    Module mod1("1111", "some module", 60);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 60);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 2, 5,modules, 20);
    std::shared_ptr<Stage> st1ptr = std::make_shared<Stage>(st1);
    Stage st2("St2", 120, 3, 6, modules, 20);
    std::shared_ptr<Stage> st2ptr = std::make_shared<Stage>(st2);
    std::vector<std::shared_ptr<Stage>> stages;
    stages.push_back(st1ptr);
    stages.push_back(st2ptr);
    Course c1("COMP1", "Computer Science", stages, "Bachelor", "FullTime");

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);
    moduleAttempt1->setCreditsEarned(20);
    moduleAttempt2->setCreditsEarned(60);

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt1);
    moduleAttempts.push_back(moduleAttempt2);
    auto StageAttempt1 = std::make_shared<StageAttempt>("T1",st1,moduleAttempts);
    auto StageAttempt2 = std::make_shared<StageAttempt>("T1",st2,moduleAttempts);
    StageAttempt1->setAggregate(10);
    StageAttempt2->setAggregate(9);


    std::vector<std::shared_ptr<StageAttempt>> stageAttempts;
    stageAttempts.push_back(StageAttempt1);
    stageAttempts.push_back(StageAttempt2);

    CourseAttempt ca1("T1", c1, stageAttempts);
    ca1.setStartClassification("DipHE");
    ca1.getAttempts();
    ca1.calculateAggregate();
    ca1.setEarnedCredits(280);
    ca1.generateCode();
    std::string expectedResult = "A2";
    std::string actualResult = ca1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
    BOOST_CHECK_EQUAL(StageAttempt2->getFinalCode()->getCode(), "PA");
}

BOOST_AUTO_TEST_CASE(CertHEDistinctionTest) {
    Module mod1("1111", "some module", 60);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 60);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 2, 5,modules, 20);
    std::shared_ptr<Stage> st1ptr = std::make_shared<Stage>(st1);
    Stage st2("St2", 120, 3, 6, modules, 20);
    std::shared_ptr<Stage> st2ptr = std::make_shared<Stage>(st2);
    std::vector<std::shared_ptr<Stage>> stages;
    stages.push_back(st1ptr);
    stages.push_back(st2ptr);
    Course c1("COMP1", "Computer Science", stages, "Bachelor", "FullTime");

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);
    moduleAttempt1->setCreditsEarned(20);
    moduleAttempt2->setCreditsEarned(60);

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt1);
    moduleAttempts.push_back(moduleAttempt2);
    auto StageAttempt1 = std::make_shared<StageAttempt>("T1",st1,moduleAttempts);
    auto StageAttempt2 = std::make_shared<StageAttempt>("T1",st2,moduleAttempts);
    StageAttempt1->setAggregate(13);
    StageAttempt2->setAggregate(14);


    std::vector<std::shared_ptr<StageAttempt>> stageAttempts;
    stageAttempts.push_back(StageAttempt1);
    stageAttempts.push_back(StageAttempt2);

    CourseAttempt ca1("T1", c1, stageAttempts);
    ca1.setStartClassification("CertHE");
    ca1.getAttempts();
    ca1.calculateAggregate();
    ca1.setEarnedCredits(220);
    ca1.generateCode();
    std::string expectedResult = "CD";
    std::string actualResult = ca1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
    BOOST_CHECK_EQUAL(StageAttempt2->getFinalCode()->getCode(), "PA");
}



BOOST_AUTO_TEST_CASE(CertHEUsualTest) {
    Module mod1("1111", "some module", 60);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 60);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 2, 5,modules, 20);
    std::shared_ptr<Stage> st1ptr = std::make_shared<Stage>(st1);
    Stage st2("St2", 120, 3, 6, modules, 20);
    std::shared_ptr<Stage> st2ptr = std::make_shared<Stage>(st2);
    std::vector<std::shared_ptr<Stage>> stages;
    stages.push_back(st1ptr);
    stages.push_back(st2ptr);
    Course c1("COMP1", "Computer Science", stages, "Bachelor", "FullTime");

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);
    moduleAttempt1->setCreditsEarned(20);
    moduleAttempt2->setCreditsEarned(60);

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt1);
    moduleAttempts.push_back(moduleAttempt2);
    auto StageAttempt1 = std::make_shared<StageAttempt>("T1",st1,moduleAttempts);
    auto StageAttempt2 = std::make_shared<StageAttempt>("T1",st2,moduleAttempts);
    StageAttempt1->setAggregate(10);
    StageAttempt2->setAggregate(9);


    std::vector<std::shared_ptr<StageAttempt>> stageAttempts;
    stageAttempts.push_back(StageAttempt1);
    stageAttempts.push_back(StageAttempt2);

    CourseAttempt ca1("T1", c1, stageAttempts);
    ca1.setStartClassification("CertHE");
    ca1.getAttempts();
    ca1.calculateAggregate();
    ca1.setEarnedCredits(220);
    ca1.generateCode();
    std::string expectedResult = "A1";
    std::string actualResult = ca1.getFinalCode()->getCode();
    BOOST_CHECK_EQUAL(actualResult, expectedResult);
    BOOST_CHECK_EQUAL(StageAttempt2->getFinalCode()->getCode(), "PA");
}

BOOST_AUTO_TEST_CASE(DipHENotEnoughCreditsTest) {
    Module mod1("1111", "some module", 60);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 60);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 2, 5,modules, 20);
    std::shared_ptr<Stage> st1ptr = std::make_shared<Stage>(st1);
    Stage st2("St2", 120, 3, 6, modules, 20);
    std::shared_ptr<Stage> st2ptr = std::make_shared<Stage>(st2);
    std::vector<std::shared_ptr<Stage>> stages;
    stages.push_back(st1ptr);
    stages.push_back(st2ptr);
    Course c1("COMP1", "Computer Science", stages, "Bachelor", "FullTime");

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);
    moduleAttempt1->setCreditsEarned(20);
    moduleAttempt2->setCreditsEarned(60);

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt1);
    moduleAttempts.push_back(moduleAttempt2);
    auto StageAttempt1 = std::make_shared<StageAttempt>("T1",st1,moduleAttempts);
    auto StageAttempt2 = std::make_shared<StageAttempt>("T1",st2,moduleAttempts);
    StageAttempt1->setAggregate(10);
    StageAttempt2->setAggregate(9);


    std::vector<std::shared_ptr<StageAttempt>> stageAttempts;
    stageAttempts.push_back(StageAttempt1);
    stageAttempts.push_back(StageAttempt2);

    CourseAttempt ca1("T1", c1, stageAttempts);
    ca1.setStartClassification("DipHE");
    ca1.getAttempts();
    ca1.calculateAggregate();
    ca1.setEarnedCredits(220);
    ca1.generateCode();
    BOOST_CHECK_EQUAL(StageAttempt2->getFinalCode()->getCode(), "RE");
}

BOOST_AUTO_TEST_CASE(smallAmountOfCreditsCreditsTest) {
    Module mod1("1111", "some module", 60);
    std::shared_ptr<Module> mod1ptr = std::make_shared<Module>(mod1);

    Module mod2("1112", "some module", 60);
    std::shared_ptr<Module> mod2ptr = std::make_shared<Module>(mod2);
    std::vector<std::shared_ptr<Module>> modules;
    modules.push_back(mod1ptr);
    modules.push_back(mod2ptr);
    Stage st1("St1", 120, 2, 5,modules, 20);
    std::shared_ptr<Stage> st1ptr = std::make_shared<Stage>(st1);
    Stage st2("St2", 120, 3, 6, modules, 20);
    std::shared_ptr<Stage> st2ptr = std::make_shared<Stage>(st2);
    std::vector<std::shared_ptr<Stage>> stages;
    stages.push_back(st1ptr);
    stages.push_back(st2ptr);
    Course c1("COMP1", "Computer Science", stages, "Bachelor", "FullTime");

    std::vector<std::shared_ptr<AssessmentAttempt>> assessmentAttempts;

    auto moduleAttempt1 = std::make_shared<ModuleAttempt>("T1", mod1, 1, "202425", assessmentAttempts);
    auto moduleAttempt2 = std::make_shared<ModuleAttempt>("T1", mod2, 2, "202425", assessmentAttempts);
    moduleAttempt1->setCreditsEarned(20);
    moduleAttempt2->setCreditsEarned(60);

    std::vector<std::shared_ptr<ModuleAttempt>> moduleAttempts;
    moduleAttempts.push_back(moduleAttempt1);
    moduleAttempts.push_back(moduleAttempt2);
    auto StageAttempt1 = std::make_shared<StageAttempt>("T1",st1,moduleAttempts);
    auto StageAttempt2 = std::make_shared<StageAttempt>("T1",st2,moduleAttempts);
    StageAttempt1->setAggregate(10);
    StageAttempt2->setAggregate(9);


    std::vector<std::shared_ptr<StageAttempt>> stageAttempts;
    stageAttempts.push_back(StageAttempt1);
    stageAttempts.push_back(StageAttempt2);

    CourseAttempt ca1("T1", c1, stageAttempts);
    ca1.setStartClassification("DipHE");
    ca1.getAttempts();
    ca1.calculateAggregate();
    ca1.setEarnedCredits(100);
    ca1.generateCode();
    BOOST_CHECK_EQUAL(StageAttempt2->getFinalCode()->getCode(), "WD");
}

BOOST_AUTO_TEST_SUITE_END()


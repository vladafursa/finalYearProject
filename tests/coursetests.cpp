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
    std::cout<<"stage 1 has "<<StageAttempt1->getCreditsEarned();
    std::cout<<"stage 2 has "<<StageAttempt2->getCreditsEarned();

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
    std::cout<<"stage 1 has "<<StageAttempt1->getCreditsEarned();
    std::cout<<"stage 2 has "<<StageAttempt2->getCreditsEarned();


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

BOOST_AUTO_TEST_SUITE_END()
/*

void CourseAttempt::calculateProgression(){
    for(const auto& attempt : attempts){
        if(attempt->getStage().getLevel()==4 && attempt->getCreditsEarned()<120){
            if(attempt->getStage().getLevel()==5){
                if(classification == "Bachelor"){
                    std::vector<const ProgressionCode*> thoughtCodes;
                    thoughtCodes.push_back(&ProgressionCodes::FC);
                    thoughtCodes.push_back(&ProgressionCodes::FD);
                    thoughtCodes.push_back(&ProgressionCodes::DF);
                    thoughtCodes.push_back(&ProgressionCodes::RE);
                    thoughtCodes.push_back(&ProgressionCodes::RP);
                    thoughtCodes.push_back(&ProgressionCodes::PG);
                    attempt->setPossibleCodes(thoughtCodes);
                }
            }
        }
    }
}

void CourseAttempt::generateCode(){
    grade = gradeSystem.assignGrade(calculateAggregate());
    for(const auto& attempt : attempts){
        if (attempt->getStage().getLevel()==6){
            if(attempt->getCreditsEarned()==360){
                if (gradeSystem.isGreaterThanThreshold(grade, "1LOW")){
                    setFinalCode(&AwardCodes::C10);
                }
                else if (gradeSystem.isGreaterThanThreshold(grade, "21LOW")){
                    setFinalCode(&AwardCodes::C21);
                }
                else if (gradeSystem.isGreaterThanThreshold(grade, "22LOW")){
                    setFinalCode(&AwardCodes::C22);
                }
                else {
                    setFinalCode(&AwardCodes::C30);
                }
                attempt->setFinalCode(&ProgressionCodes::PA);
            }
            else if (attempt->getCreditsEarned()>=300 && attempt->getCreditsEarned()<360){
                if (classification == "ordinary"){
                    if (gradeSystem.isGreaterThanThreshold(grade, "1LOW")){
                        setFinalCode(&AwardCodes::DD);
                    }
                    else{
                        setFinalCode(&AwardCodes::DN);
                    }
                    attempt->setFinalCode(&ProgressionCodes::PA);
                }
                else{
                    attempt->setFinalCode(&ProgressionCodes::RD);
                }
            }
            else if (attempt->getCreditsEarned()>=240 && attempt->getCreditsEarned()<300){
                if(classification == "DipHE"){
                    if (gradeSystem.isGreaterThanThreshold(grade, "1LOW")){
                        setFinalCode(&AwardCodes::ID);
                    }
                    else{
                        setFinalCode(&AwardCodes::A2);
                    }
                    attempt->setFinalCode(&ProgressionCodes::PA);
                }else{
                    attempt->setFinalCode(&ProgressionCodes::RN);
                }
            }
            else{
                if (attempt->getCreditsEarned()>=120 && attempt->getCreditsEarned()<240)
                    if(classification=="CertHE"){
                      if (gradeSystem.isGreaterThanThreshold(grade, "1LOW")){
                          setFinalCode(&AwardCodes::CD);
                        }
                        else{
                        setFinalCode(&AwardCodes::A1);
                        }
                        attempt->setFinalCode(&ProgressionCodes::PA);
                    }
                    else{
                        attempt->setFinalCode(&ProgressionCodes::WD);
                }
            }
        }
    }
}

double CourseAttempt::calculateAggregate(){
    double aggregate = 0;
    for(const auto& attempt : attempts){
        int gradePoints = std::ceil(attempt->getAggregate());
        if (attempt->getStage().getLevel()==6){
            aggregate+=0.8*gradePoints;
        }
        if (attempt->getStage().getLevel()==5){
              aggregate+=0.2*gradePoints;
        }
        aggregate = gradeSystem.round(aggregate);
        return aggregate;
    }
}





*/

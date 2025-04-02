#include "moduleattempt.h"

//constructor
ModuleAttempt::ModuleAttempt(std::string providedStudentNumber,
              const Module& providedModule,
              int providedNumberOfAttempt,
              std::string providedType,
                             std::vector<std::reference_wrapper<AssessmentAttempt>>& providedAttempts):module(providedModule){
    studentNumber = providedStudentNumber;
    numberOfAttempt = providedNumberOfAttempt;
    type = providedType;
    attempts = providedAttempts;
}

//getters
std::string ModuleAttempt::getStudentNumber() const{
    return studentNumber;
}

const Module& ModuleAttempt::getModule() const{
    return module;
}

int ModuleAttempt::getNumberOfAttempt() const{
    return numberOfAttempt;
}

std::string ModuleAttempt::getType() const{
    return type;
}

const std::vector<std::reference_wrapper<AssessmentAttempt>>& ModuleAttempt::getAttempts() const{
    return attempts;
}

bool ModuleAttempt::getHadNec() const{
    return hadNec;
}

double ModuleAttempt::getAggregate() const{
    return aggregate;
}

bool ModuleAttempt::getPassed() const{
    return passed;
}

int ModuleAttempt::getCreditsEarned() const{
    return creditsEarned;
}

ModuleCode* ModuleAttempt::getFinalCode() const{
    return finalCode;
}

const std::vector<ModuleCode*>& ModuleAttempt::getPossibleCodes() const{
    return posibleCodes;
}

//setters
void ModuleAttempt::setStudentNumber(std::string providedStudentNumber){
    studentNumber = providedStudentNumber;
}

void ModuleAttempt::setNumberOfAttempt(int providedNumberOfAttempt){
    numberOfAttempt = providedNumberOfAttempt;
}

void ModuleAttempt::setType(std::string providedType){
    type = providedType;
}

void ModuleAttempt::setAtempts(std::vector<std::reference_wrapper<AssessmentAttempt>>& providedAttempts){
    attempts=providedAttempts;
}

void ModuleAttempt::setHadNec(bool providedHadNec){
    hadNec=providedHadNec;
}

void ModuleAttempt::setAggregate(double providedAggregate){
    aggregate=providedAggregate;
}

void ModuleAttempt::setPassed(bool providedPassed){
    passed=providedPassed;
}

void ModuleAttempt::setCreditsEarned(int providedCreditsEarned){
    creditsEarned=providedCreditsEarned;
}

void ModuleAttempt::setFinalCode(ModuleCode* providedModuleCode){
    finalCode=providedModuleCode;
}

void ModuleAttempt::setPossibleCodes(std::vector<ModuleCode*>& providedPosibleCodes){
    posibleCodes=providedPosibleCodes;
}

//calculations

//getting only latest attempts
const std::vector<std::reference_wrapper<AssessmentAttempt>>& ModuleAttempt::getFinalattempts() const{
    std::vector<std::reference_wrapper<AssessmentAttempt>>  finalAttempts;
    const auto& assessments = module.getAssessmentsWithWeights();
    const auto& assessmentsAttempts = getAttempts();
    for (const auto& assessment : assessments) {
            std::string assessmentId = assessment.first.get().getId();
            int numberOfCurrentAssessmentAttempt = 0;
            for (const auto& attempt : assessmentsAttempts){
                std::string attemptAssessmentId=attempt.get().getAssessment().getId();
                int numberOfAssessmentAttempt = attempt.get().getNumberOfAttempt();
                    if(numberOfCurrentAssessmentAttempt<numberOfAssessmentAttempt){
                        if (!finalAttempts.empty()){
                            finalAttempts.pop_back();
                        }
                        finalAttempts.push_back(attempt);
                    }
                numberOfCurrentAssessmentAttempt = numberOfAssessmentAttempt;
            }
    }
    return finalAttempts;
}

double ModuleAttempt::calculateAggregate(){
    return 0.5;
}




void generateCode();
void populatePossibleDecisions();
void calculateAggregate();
bool determinPass();
bool determinSpecialPass();

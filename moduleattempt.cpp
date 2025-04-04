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

const ModuleCode* ModuleAttempt::getFinalCode() const{
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

void ModuleAttempt::setFinalCode(const ModuleCode* providedModuleCode){
    finalCode=providedModuleCode;
}

void ModuleAttempt::setPossibleCodes(std::vector<ModuleCode*>& providedPosibleCodes){
    posibleCodes=providedPosibleCodes;
}

std::string ModuleAttempt::getGrade(){
    grade = gradeSystem.assignGrade(aggregate);
    return grade;
}

//calculations
//getting only latest attempts
std::vector<std::reference_wrapper<AssessmentAttempt>> ModuleAttempt::getFinalattempts() const {
    std::vector<std::reference_wrapper<AssessmentAttempt>> finalAttempts;
    const auto& assessments = module.getAssessmentsWithWeights();
    const auto& assessmentsAttempts = getAttempts();

    for (const auto& assessment : assessments) {
        std::string assessmentId = assessment.first.get().getId();
        AssessmentAttempt* latestAttempt = nullptr;
        int maxNumberOfAttempt = 0;

        for (const auto& attempt : assessmentsAttempts) {
            std::string attemptAssessmentId = attempt.get().getAssessment().getId();
            int numberOfAssessmentAttempt = attempt.get().getNumberOfAttempt();

            if (attemptAssessmentId == assessmentId && numberOfAssessmentAttempt > maxNumberOfAttempt) {
                maxNumberOfAttempt = numberOfAssessmentAttempt;
                latestAttempt = &attempt.get();
            }
        }
        finalAttempts.push_back(*latestAttempt);
    }
    return finalAttempts;
}


double ModuleAttempt::calculateAggregate(){
    std::vector<std::reference_wrapper<AssessmentAttempt>> finalAttempts = getFinalattempts();
    aggregate = 0;
    const auto& assessments = module.getAssessmentsWithWeights();
    for (const auto& assessment : assessments) {
        std::string assessmentId = assessment.first.get().getId();
        int weightingOfAssessment = assessment.second;

        for (const auto& attempt : finalAttempts) {
            std::string attemptAssessmentId = attempt.get().getAssessment().getId();
            int gradePoints = attempt.get().getGradePoints();

            if (attemptAssessmentId == assessmentId) {
                aggregate+=gradePoints*weightingOfAssessment/100.0;
            }
        }
    }
    aggregate = gradeSystem.round(aggregate);
    return aggregate;
}

bool ModuleAttempt::checkAllElementsPassed(){
    bool allPassed = true;
    std::vector<std::reference_wrapper<AssessmentAttempt>> finalAttempts = getFinalattempts();
    for (const auto& attempt : finalAttempts) {
        std::string grade = attempt.get().getGrade();
        if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
            allPassed=false;
        }
    }
    return allPassed;
}

void ModuleAttempt::generateCode(){
    if (checkAllElementsPassed() || determinSpecialPass()){
        passed = true;
        setFinalCode(&ModuleCodes::PA);
        creditsEarned=module.getCredits();
    }
    else{
        passed = false;
    }
}

bool ModuleAttempt::determinSpecialPass(){
    bool canPass = false;
    std::vector<std::reference_wrapper<AssessmentAttempt>> failedAttempts;
    std::vector<std::reference_wrapper<AssessmentAttempt>> finalAttempts = getFinalattempts();
    for (const auto& attempt : finalAttempts) {
        std::string attemptGrade = attempt.get().getGrade();
        if(!gradeSystem.isGreaterThanThreshold(attemptGrade, "3LOW")){
            failedAttempts.push_back(attempt);
        }
    }
    size_t numberOfFails = failedAttempts.size();
    if (gradeSystem.isGreaterThanThreshold(grade, "3LOW") && numberOfFails==1){
        std::string failedGrade = failedAttempts[0].get().getGrade();
        if (gradeSystem.isGreaterThanThreshold(failedGrade, "FMARG")){
            canPass = true;
        }
    }
    return canPass;
}

bool ModuleAttempt::getHadMisconduct(){
    hadMisconduct = false;
    for (const auto& attempt : attempts){
        if (attempt.get().getMisconduct()!=nullptr){
            hadMisconduct = true;
        }
    }
    return hadMisconduct;
}


void populatePossibleDecisions();



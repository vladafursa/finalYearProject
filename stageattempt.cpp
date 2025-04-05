#include "stageattempt.h"
#include <cmath>

//constructor
StageAttempt::StageAttempt(std::string providedStudentNumber,
             const Stage& providedStage,
                           std::vector<std::reference_wrapper<ModuleAttempt>>& providedAttempts):stage(providedStage){
    studentNumber = providedStudentNumber;
    attempts = providedAttempts;
}

//getters
std::string StageAttempt::getStudentNumber() const{
    return studentNumber;
}

const Stage& StageAttempt::getStage() const{
    return stage;
}

const std::vector<std::reference_wrapper<ModuleAttempt>>& StageAttempt::getAttempts() const{
    return attempts;
}

double StageAttempt::getAggregate() const{
    return aggregate;
}

bool StageAttempt::getPassed() const{
    return passed;
}

int StageAttempt::getCreditsEarned() const{
    return creditsEarned;
}

const ProgressionCode* StageAttempt::getFinalCode() const{
    return finalCode;
}

const std::vector<ProgressionCode*>& StageAttempt::getPossibleCodes() const{
    return posibleCodes;
}

std::string StageAttempt::getGrade(){
    grade = gradeSystem.assignGrade(aggregate);
    return grade;
}

int StageAttempt::getRemainingCompensationCredits() const{
    return remainingCompensationCredits;
}

//setters
void StageAttempt::setStudentNumber(std::string providedStudentNumber){
    studentNumber = providedStudentNumber;
}


void StageAttempt::setAtempts(std::vector<std::reference_wrapper<ModuleAttempt>>& providedAttempts){
    attempts=providedAttempts;
}

void StageAttempt::setAggregate(double providedAggregate){
    aggregate=providedAggregate;
}

void StageAttempt::setPassed(bool providedPassed){
    passed=providedPassed;
}

void StageAttempt::setCreditsEarned(int providedCreditsEarned){
    creditsEarned=providedCreditsEarned;
}

void StageAttempt::setFinalCode(const ProgressionCode* providedProgressionCode){
    finalCode=providedProgressionCode;
}

void StageAttempt::setPossibleCodes(std::vector<ProgressionCode*>& providedPosibleCodes){
    posibleCodes=providedPosibleCodes;
}

void StageAttempt::setRemainingCompensationCredits(int providedRemainingCredits){
    remainingCompensationCredits = providedRemainingCredits;
}

//calculations
//getting only latest attempts
std::vector<std::reference_wrapper<ModuleAttempt>> StageAttempt::getFinalattempts() const {
    std::vector<std::reference_wrapper<ModuleAttempt>> finalAttempts;
    const auto& modules = stage.getModules();
    const auto& moduleAttempts = getAttempts();

    for (const auto& module : modules) {
        std::string moduleCode = module.get().getCode();
        ModuleAttempt* latestAttempt = nullptr;
        int maxNumberOfAttempt = 0;

        for (const auto& attempt : moduleAttempts) {
            std::string attemptModuleCode = attempt.get().getModule().getCode();
            int numberOfModuleAttempt = attempt.get().getNumberOfAttempt();

            if (attemptModuleCode == moduleCode &&  numberOfModuleAttempt > maxNumberOfAttempt) {
                maxNumberOfAttempt =  numberOfModuleAttempt;
                latestAttempt = &attempt.get();
            }
        }
        finalAttempts.push_back(*latestAttempt);
    }
    return finalAttempts;
}


double StageAttempt::calculateAggregate(){
    std::vector<std::reference_wrapper<ModuleAttempt>> finalAttempts = getFinalattempts();
    aggregate = 0;
    const auto& modules = stage.getModules();
    for (const auto& module : modules) {
        std::string moduleCode =  module.get().getCode();
        double weightingOfModule = module.get().getCredits() / stage.getCredits();

        for (const auto& attempt : finalAttempts) {
            std::string attemptModuleCode = attempt.get().getModule().getCode();
            int gradePoints = std::ceil(attempt.get().getAggregate());

            if (attemptModuleCode == moduleCode) {
                aggregate+=gradePoints*weightingOfModule;
            }
        }
    }
    aggregate = gradeSystem.round(aggregate);
    return aggregate;
}

bool StageAttempt::checkAllModulesPassed() {
    std::vector<std::reference_wrapper<ModuleAttempt>> finalAttempts = getFinalattempts();
    int numberOfPassed = 0;

    for (const auto& attempt : finalAttempts) {
        const ModuleCode* code = attempt.get().getFinalCode();
        std::string stringCode = code->getCode();
        for (const auto* passCode : ModuleCodes::PASS_CODES) {
            if (stringCode == passCode->getCode()) {
                numberOfPassed++;
                break;
            }
        }
    }
    return numberOfPassed == finalAttempts.size();
}

//determine which can be compensated
void StageAttempt::determinCompensationPass(){
    std::vector<std::reference_wrapper<ModuleAttempt>> finalAttempts = getFinalattempts();
    aggregate = calculateAggregate();
    grade = gradeSystem.assignGrade(aggregate);
    if (gradeSystem.isGreaterThanThreshold(grade, "3LOW") && !checkAllModulesPassed()){
        for (const auto& attempt : finalAttempts){
            if(attempt.get().getGrade()=="FMARG"){
                if(attempt.get().getModule().getCredits()<remainingCompensationCredits){
                    if(attempt.get().getType() == "original"){
                        attempt.get().setPossibleDecisions(&ModuleCodes::PC);
                    }
                    else if (attempt.get().getType() == "referred"){
                        attempt.get().setPossibleDecisions(&ModuleCodes::PR);
                    }
                    else{
                        attempt.get().setPossibleDecisions(&ModuleCodes::PK);
                    }
                }
            }
        }
    }
}

void StageAttempt::applyCompensation(){
    std::vector<std::reference_wrapper<ModuleAttempt>> finalAttempts = getFinalattempts();
    int limit =  stage.getLimitOfCredits();
    for (const auto& attempt : finalAttempts) {
        attempt.get().setPassed(true);
        const ModuleCode* code = attempt.get().getFinalCode();
        std::string stringCode = code->getCode();
        if (stringCode == "PC" || stringCode == "PR" || stringCode == "PK"){
            limit = limit - attempt.get().getModule().getCredits();
        }
    }
    remainingCompensationCredits = limit;
}

void StageAttempt::applyMisconducts(){
    std::vector<std::reference_wrapper<ModuleAttempt>> finalAttempts = getFinalattempts();
    for (const auto& attempt : finalAttempts){
        if(attempt.get().getHadMisconduct() == true){
             attempt.get().applyMisconduct();
        }
    }
}


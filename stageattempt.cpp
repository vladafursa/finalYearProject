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


int StageAttempt::getCreditsEarned() {
    std::vector<std::reference_wrapper<ModuleAttempt>> finalAttempts = getFinalattempts();
    creditsEarned = 0;
    for (const auto& attempt : finalAttempts) {
        creditsEarned+=creditsEarned+attempt.get().getCreditsEarned();
    }
    return creditsEarned;
}

const ProgressionCode* StageAttempt::getFinalCode() const{
    return finalCode;
}

const std::vector<const ProgressionCode*>& StageAttempt::getPossibleCodes() const{
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

void StageAttempt::setPossibleCodes(std::vector<const ProgressionCode*>& providedPosibleCodes){
    posibleCodes=providedPosibleCodes;
}

void StageAttempt::setRemainingCompensationCredits(int providedRemainingCredits){
    remainingCompensationCredits = providedRemainingCredits;
}

//calculations
//getting only latest attempts
std::vector<std::reference_wrapper<ModuleAttempt>> StageAttempt::getFinalattempts() const {//модуль с лучшими попытками
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
            std::string moduleGrade = attempt.get().getGrade();
            if(moduleGrade =="FMARG"){
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
            if(gradeSystem.isGreaterThanThreshold(moduleGrade, "3LOW") && !attempt.get().getPassed() && attempt.get().numberOfNotPassed()<=1){
                for(const auto& assessmentAttempt : attempt.get().getFinalattempts()){
                    if (assessmentAttempt.get().getGrade()=="FMID"){
                        //compensation for module code
                        if(attempt.get().getType() == "original"){
                            attempt.get().setPossibleDecisions(&ModuleCodes::PC);
                        }
                        else if (attempt.get().getType() == "referred"){
                            attempt.get().setPossibleDecisions(&ModuleCodes::PR);
                        }
                        else{
                            attempt.get().setPossibleDecisions(&ModuleCodes::PK);
                        }

                        //compensation for assessment code
                        if(assessmentAttempt.get().getType() == "original"){
                            assessmentAttempt.get().setPossibleDecisions(&AssessmentCodes::PC);
                        }
                        else if (assessmentAttempt.get().getType() == "referred"){
                            assessmentAttempt.get().setPossibleDecisions(&AssessmentCodes::PR);
                        }
                        else{
                            assessmentAttempt.get().setPossibleDecisions(&AssessmentCodes::PK);
                        }



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
            bool assessmentCompensation = false;
            for (const auto& assessmentAttempt : attempt.get().getFinalattempts()) {
                const AssessmentCode* acode = assessmentAttempt.get().getCode();
                std::string aCode = acode->getCode();
                if (aCode == "PC" || aCode == "PR" || aCode == "PK"){
                    assessmentCompensation = true;
                    const auto& assessments = attempt.get().getModule().getAssessmentsWithWeights();
                    for (const auto& assessment : assessments) {
                        std::string assessmentId = assessment.first.get().getId();
                        int weightingOfAssessment = assessment.second;

                            std::string attemptAssessmentId = assessmentAttempt.get().getAssessment().getId();

                            if (attemptAssessmentId == assessmentId) {
                                limit=limit - attempt.get().getModule().getCredits()*weightingOfAssessment/100.0;
                        }
                    }
                }
            }
            if (assessmentCompensation == false){


            limit = limit - attempt.get().getModule().getCredits();}
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




void StageAttempt::generateCode(){
    std::vector<std::reference_wrapper<ModuleAttempt>> finalAttempts = getFinalattempts();
    if(checkAllModulesPassed()){
        if (stage.getYear()==1){
            setFinalCode(&ProgressionCodes::P1);
        }
        else if (stage.getYear()==2){
            setFinalCode(&ProgressionCodes::P2);
        }
        else {
            setFinalCode(&ProgressionCodes::SO);
        }
    }
    else if(checkFirstSeats()!=0 && checkFail()==0 && checkReferred()==0){
        for (const auto& attempt : finalAttempts) {
            const ModuleCode* code = attempt.get().getFinalCode();
            std::string stringCode = code->getCode();
            for (const auto* fsCode : ModuleCodes::FIRST_SIT_CODES) {
                if (stringCode == fsCode->getCode()) {
                    if (checkFirstSeats()==1){
                        if(stringCode=="1A"){
                            setFinalCode(&ProgressionCodes::R1);
                        }
                        if(stringCode=="1N"){
                            setFinalCode(&ProgressionCodes::F1);
                        }
                    }
                    break;
                }
            }
        }
        if (checkFirstSeats()!=1){
            posibleCodes.push_back(&ProgressionCodes::R1);
            posibleCodes.push_back(&ProgressionCodes::F1);
        }
    }

    if(creditsEarned > (stage.getCredits()-20)){
        setFinalCode(&ProgressionCodes::PD);//and not final attempt
    }
    else{
        if(checkReferred()!=0 && checkFail() ==0){
            setFinalCode(&ProgressionCodes::RF);
            posibleCodes.push_back(&ProgressionCodes::RA);
            posibleCodes.push_back(&ProgressionCodes::RN);
            posibleCodes.push_back(&ProgressionCodes::RS);
            posibleCodes.push_back(&ProgressionCodes::DF);
            posibleCodes.push_back(&ProgressionCodes::PR);
        }
        if(checkReferred()!=0 && checkFail() !=0){
            setFinalCode(&ProgressionCodes::RR);
            posibleCodes.push_back(&ProgressionCodes::DF);
            posibleCodes.push_back(&ProgressionCodes::FR);

        }
    }
    //repeat the year, referrals over the summer
}

int StageAttempt::checkFirstSeats() {
    std::vector<std::reference_wrapper<ModuleAttempt>> finalAttempts = getFinalattempts();
    int containsFirstSeat = 0;
    for (const auto& attempt : finalAttempts) {
        const ModuleCode* code = attempt.get().getFinalCode();
        std::string stringCode = code->getCode();
        for (const auto* fsCode : ModuleCodes::FIRST_SIT_CODES) {
            if (stringCode == fsCode->getCode()) {
                containsFirstSeat++;
                break;
            }
        }
    }
    return containsFirstSeat;
}

int StageAttempt::checkReferred() {
    std::vector<std::reference_wrapper<ModuleAttempt>> finalAttempts = getFinalattempts();
    int containsReferred = 0;
    for (const auto& attempt : finalAttempts) {
        const ModuleCode* code = attempt.get().getFinalCode();
        std::string stringCode = code->getCode();
        for (const auto* rfCode : ModuleCodes::REFERRED_CODES) {
            if (stringCode == rfCode->getCode()) {
                containsReferred++;
                break;
            }
        }
    }
    return containsReferred;
}

int StageAttempt::checkFail() {
    std::vector<std::reference_wrapper<ModuleAttempt>> finalAttempts = getFinalattempts();
    int containsFail = 0;
    for (const auto& attempt : finalAttempts) {
        const ModuleCode* code = attempt.get().getFinalCode();
        std::string stringCode = code->getCode();
        for (const auto* rfCode : ModuleCodes::FAIL_CODES) {
            if (stringCode == rfCode->getCode()) {
                containsFail++;
                break;
            }
        }
    }
    return containsFail;
}



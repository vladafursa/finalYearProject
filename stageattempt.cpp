#include "stageattempt.h"
#include <cmath>

//constructor
StageAttempt::StageAttempt(std::string providedStudentNumber,
                           const Stage& providedStage,
                           std::vector<std::shared_ptr<ModuleAttempt>>& providedAttempts):stage(providedStage){
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

const std::vector<std::shared_ptr<ModuleAttempt>>& StageAttempt::getAttempts() const{
    return attempts;
}

double StageAttempt::getAggregate() const{
    return aggregate;
}

bool StageAttempt::getPassed() const{
    return passed;
}


int StageAttempt::getCreditsEarned() {
    std::vector<std::shared_ptr<ModuleAttempt>> finalAttempts = getFinalattempts();
    creditsEarned = 0;
    for (const auto& attempt : finalAttempts) {
        creditsEarned+=attempt->getCreditsEarned();
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


void StageAttempt::setAtempts(std::vector<std::shared_ptr<ModuleAttempt>>& providedAttempts){
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
std::vector<std::shared_ptr<ModuleAttempt>> StageAttempt::getFinalattempts() const {
    std::vector<std::shared_ptr<ModuleAttempt>> finalAttempts;
    const auto& modules = stage.getModules();
    const auto& moduleAttempts = getAttempts();

    for (const auto& module : modules) {
        std::string moduleCode = module->getCode();
        std::shared_ptr<ModuleAttempt> latestAttempt = nullptr;
        int maxNumberOfAttempt = 0;

        for (const auto& attempt : moduleAttempts) {
            std::string attemptModuleCode = attempt->getModule().getCode();
            int numberOfModuleAttempt = attempt->getNumberOfAttempt();

            if (attemptModuleCode == moduleCode && numberOfModuleAttempt > maxNumberOfAttempt) {
                maxNumberOfAttempt = numberOfModuleAttempt;
                latestAttempt = attempt;
            }
        }

        if (latestAttempt) {
            finalAttempts.push_back(latestAttempt);
        }
    }

    return finalAttempts;
}

double StageAttempt::calculateAggregate(){
    std::vector<std::shared_ptr<ModuleAttempt>> finalAttempts = getFinalattempts();
    aggregate = 0;
    const auto& modules = stage.getModules();
    for (const auto& module : modules) {
        std::string moduleCode =  module->getCode();
        double weightingOfModule = static_cast<double>(module->getCredits()) / stage.getCredits();


        for (const auto& attempt : finalAttempts) {
            std::string attemptModuleCode = attempt->getModule().getCode();
            int gradePoints = gradeSystem.customRound(attempt->getAggregate());

            if (attemptModuleCode == moduleCode) {
                aggregate+=gradePoints*weightingOfModule;
            }
        }
    }
    aggregate = gradeSystem.round(aggregate);
    return aggregate;
}

bool StageAttempt::checkAllModulesPassed() {
    std::vector<std::shared_ptr<ModuleAttempt>> finalAttempts = getFinalattempts();
    int numberOfPassed = 0;

    for (const auto& attempt : finalAttempts) {
        const ModuleCode* code = attempt->getFinalCode();
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
    std::vector<std::shared_ptr<ModuleAttempt>> finalAttempts = getFinalattempts();
    aggregate = calculateAggregate();
    grade = gradeSystem.assignGrade(aggregate);
    if (gradeSystem.isGreaterThanThreshold(grade, "3LOW") && !checkAllModulesPassed()){
        for (const auto& attempt : finalAttempts){
            std::string moduleGrade = attempt->getGrade();
            if(moduleGrade =="FMARG"){
                if(attempt->getModule().getCredits()<remainingCompensationCredits){
                    if(attempt->getType() == "original"){
                        attempt->setPossibleDecisions(&ModuleCodes::PC);
                    }
                    else if (attempt->getType() == "referred"){
                        attempt->setPossibleDecisions(&ModuleCodes::PR);
                    }
                    else{
                        attempt->setPossibleDecisions(&ModuleCodes::PK);
                    }
                }
            }
            if(gradeSystem.isGreaterThanThreshold(moduleGrade, "3LOW") && !attempt->getPassed() && attempt->numberOfNotPassed()<=1){
                for(const auto& assessmentAttempt : attempt->getFinalattempts()){
                    if (assessmentAttempt->getGrade()=="FMID"){
                        //compensation for module code
                        if(attempt->getType() == "original"){
                            attempt->setPossibleDecisions(&ModuleCodes::PC);
                        }
                        else if (attempt->getType() == "referred"){
                            attempt->setPossibleDecisions(&ModuleCodes::PR);
                        }
                        else{
                            attempt->setPossibleDecisions(&ModuleCodes::PK);
                        }

                        //compensation for assessment code
                        if(assessmentAttempt->getType() == "original"){
                            assessmentAttempt->setPossibleDecisions(&AssessmentCodes::PC);
                        }
                        else if (assessmentAttempt->getType() == "referred"){
                            assessmentAttempt->setPossibleDecisions(&AssessmentCodes::PR);
                        }
                        else{
                            assessmentAttempt->setPossibleDecisions(&AssessmentCodes::PK);
                        }
                    }
                }
            }
        }
    }
}

void StageAttempt::applyCompensation(){
    std::vector<std::shared_ptr<ModuleAttempt>> finalAttempts = getFinalattempts();
    int limit =  stage.getLimitOfCredits();
    for (const auto& attempt : finalAttempts) {
        attempt->setPassed(true);
        const ModuleCode* code = attempt->getFinalCode();
        std::string stringCode = code->getCode();
        if (stringCode == "PC" || stringCode == "PR" || stringCode == "PK"){
            bool assessmentCompensation = false;
            for (const auto& assessmentAttempt : attempt->getFinalattempts()) {
                const AssessmentCode* acode = assessmentAttempt->getCode();
                std::string aCode = acode->getCode();
                if (aCode == "PC" || aCode == "PR" || aCode == "PK"){
                    assessmentCompensation = true;
                    const auto& assessments = attempt->getModule().getAssessmentsWithWeights();
                    for (const auto& assessment : assessments) {
                        std::string assessmentId = assessment.first.getId();
                        int weightingOfAssessment = assessment.second;

                        std::string attemptAssessmentId = assessmentAttempt->getAssessment().getId();

                        if (attemptAssessmentId == assessmentId) {
                            limit=limit - attempt->getModule().getCredits()*weightingOfAssessment/100.0;
                        }
                    }
                }
            }
            if (assessmentCompensation == false){


                limit = limit - attempt->getModule().getCredits();}
        }
    }
    remainingCompensationCredits = limit;
}

void StageAttempt::applyMisconducts(){
    std::vector<std::shared_ptr<ModuleAttempt>> finalAttempts = getFinalattempts();
    for (const auto& attempt : finalAttempts){
        if(attempt->getHadMisconduct() == true){
            attempt->applyMisconduct();
        }
    }
}




void StageAttempt::generateCode(){
    std::vector<std::shared_ptr<ModuleAttempt>>finalAttempts = getFinalattempts();
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
    else if (checkFirstSeats() != 0 && checkFail() == 0 && checkReferred() == 0) {
        bool has1A = false;
        bool has1N = false;

        for (const auto& attempt : finalAttempts) {
            const ModuleCode* code = attempt->getFinalCode();
            std::string stringCode = code->getCode();

            for (const auto* fsCode : ModuleCodes::FIRST_SIT_CODES) {
                if (stringCode == fsCode->getCode()) {
                    if (stringCode == "1A") {
                        has1A = true;
                    }
                    if (stringCode == "1N") {
                        has1N = true;
                    }
                    break;
                }
            }
        }

        if (has1A && !has1N) {
            setFinalCode(&ProgressionCodes::R1);
        } else if (has1N) {
            setFinalCode(&ProgressionCodes::F1);
        }
    }

    else if(creditsEarned >= (stage.getCredits()-20)){
        setFinalCode(&ProgressionCodes::PD);
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
        if(checkReferred()==0 && checkFail() !=0 && checkFail()!=finalAttempts.size()){
            setFinalCode(&ProgressionCodes::FR);
            posibleCodes.push_back(&ProgressionCodes::DF);
            posibleCodes.push_back(&ProgressionCodes::FY);
            posibleCodes.push_back(&ProgressionCodes::FD);
        }
        if(checkFail()==finalAttempts.size()){
            setFinalCode(&ProgressionCodes::FT);
        }
    }
}

int StageAttempt::checkFirstSeats() {
    std::vector<std::shared_ptr<ModuleAttempt>> finalAttempts = getFinalattempts();
    int containsFirstSeat = 0;
    for (const auto& attempt : finalAttempts) {
        const ModuleCode* code = attempt->getFinalCode();
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
    std::vector<std::shared_ptr<ModuleAttempt>> finalAttempts = getFinalattempts();
    int containsReferred = 0;
    for (const auto& attempt : finalAttempts) {
        const ModuleCode* code = attempt->getFinalCode();
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
    std::vector<std::shared_ptr<ModuleAttempt>> finalAttempts = getFinalattempts();
    int containsFail = 0;
    for (const auto& attempt : finalAttempts) {
        const ModuleCode* code = attempt->getFinalCode();
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

void StageAttempt::setTypes(){
    for (const auto& current : attempts) {
        if (current->getNumberOfAttempt() == 1 || ModuleCodes::FIRST_SIT_CODES.contains(current->getFinalCode())) {
            current->setType("original");
            continue;
        }

        for (const auto& prev : attempts) {
            bool sameModule= false;

            const std::string currentCode = current->getModule().getCode();

            const std::string prevCode = prev->getModule().getCode();

            sameModule = (currentCode == prevCode);

            if (sameModule &&
                prev->getNumberOfAttempt() == current->getNumberOfAttempt() - 1) {

                const ModuleCode* prevFinalCode = prev->getFinalCode();
                if (prevFinalCode != nullptr) {

                    for (const auto& code : ModuleCodes::REPEAT_CODES) {
                        if (code->getCode() == prevFinalCode->getCode()) {
                            current->setType("repeat");
                            break;
                        }
                    }
                    for (const auto& code : ModuleCodes::REFERRED_CODES) {
                        if (code->getCode() == prevFinalCode->getCode()) {
                            current->setType("referral");
                            break;
                        }
                    }
                }
                break;
            }
        }
    }
}

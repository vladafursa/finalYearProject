#include "moduleattempt.h"
#include "CodeConstants.h"
//constructor
ModuleAttempt::ModuleAttempt(std::string providedStudentNumber,
                             Module providedModule,
                             int providedNumberOfAttempt,
                             std::string providedYear,
                             std::vector<std::shared_ptr<AssessmentAttempt>>& providedAttempts)
    : module(std::move(providedModule)), attempts(providedAttempts) {
    studentNumber = providedStudentNumber;
    numberOfAttempt = providedNumberOfAttempt;
    year = providedYear;
}

//getters
std::string ModuleAttempt::getStudentNumber() const{
    return studentNumber;
}


int ModuleAttempt::getNumberOfAttempt() const{
    return numberOfAttempt;
}

std::string ModuleAttempt::getYear() const{
    return year;
}

std::string ModuleAttempt::getType() const{
    return type;
}

const std::vector<std::shared_ptr<AssessmentAttempt>>& ModuleAttempt::getAttempts() const{
    return attempts;
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

const std::vector<const ModuleCode*>& ModuleAttempt::getPossibleCodes() const{
    return posibleCodes;
}

//setters
void ModuleAttempt::setStudentNumber(std::string providedStudentNumber){
    studentNumber = providedStudentNumber;
}

void ModuleAttempt::setNumberOfAttempt(int providedNumberOfAttempt){
    numberOfAttempt = providedNumberOfAttempt;
}

void ModuleAttempt::setYear(std::string providedYear) {
    year = providedYear;
}

void ModuleAttempt::setType(std::string providedType){
    type = providedType;
}

void ModuleAttempt::setAtempts(std::vector<std::shared_ptr<AssessmentAttempt>>& providedAttempts){
    attempts=providedAttempts;
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

void ModuleAttempt::setPossibleDecisions(const ModuleCode* providedPossibleCode){
    posibleCodes.push_back(providedPossibleCode);
}


std::string ModuleAttempt::getGrade(){
    grade = gradeSystem.assignGrade(aggregate);
    return grade;
}

//calculations
//best ones
//getting only latest attempts

std::vector<std::shared_ptr<AssessmentAttempt>> ModuleAttempt::getLatestAttempts() const {
    std::vector<std::shared_ptr<AssessmentAttempt>> finalAttempts;
    const auto& assessments = module.getAssessmentsWithWeights();
    const auto& assessmentAttempts = getAttempts();

    for (const auto& assessment : assessments) {
        std::string assessmentId = assessment.first.getId();
        std::shared_ptr<AssessmentAttempt> latestAttempt = nullptr;
        int maxNumberOfAttempt = 0;

        for (const auto& attempt : assessmentAttempts) {
            std::string attemptAssessmentId = attempt->getAssessment().getId();
            int numberOfAssessmentAttempt = attempt->getNumberOfAttempt();

            if (attemptAssessmentId == assessmentId && numberOfAssessmentAttempt > maxNumberOfAttempt) {
                maxNumberOfAttempt = numberOfAssessmentAttempt;
                latestAttempt = attempt;
            }
        }

        if (latestAttempt) {
            finalAttempts.push_back(latestAttempt);
        }
    }

    return finalAttempts;
}


std::vector<std::shared_ptr<AssessmentAttempt>> ModuleAttempt::getFinalattempts() const {
    std::vector<std::shared_ptr<AssessmentAttempt>> finalAttempts;
    const auto& assessments = module.getAssessmentsWithWeights();
    const auto& assessmentsAttempts = getAttempts();

    for (const auto& assessment : assessments) {
        std::string assessmentId = assessment.first.getId();
        std::shared_ptr<AssessmentAttempt> bestAttempt = nullptr;
        int maxGradePoints = -1;

        for (const auto& attempt : assessmentsAttempts) {
            std::string attemptAssessmentId = attempt->getAssessment().getId();
            int gradePointsOfAssessmentAttempt = attempt->getGradePoints();

            if (attemptAssessmentId == assessmentId && gradePointsOfAssessmentAttempt > maxGradePoints) {
                maxGradePoints = gradePointsOfAssessmentAttempt;
                bestAttempt = attempt;
            }
        }

        if (bestAttempt) {
            finalAttempts.push_back(bestAttempt);
        }
    }

    return finalAttempts;
}



double ModuleAttempt::calculateAggregate(){
    std::vector<std::shared_ptr<AssessmentAttempt>> finalAttempts = getFinalattempts();
    aggregate = 0;
    const auto& assessments = module.getAssessmentsWithWeights();
    for (const auto& assessment : assessments) {
        std::string assessmentId = assessment.first.getId();
        int weightingOfAssessment = assessment.second;

        for (const auto& attempt : finalAttempts) {
            std::string attemptAssessmentId = attempt->getAssessment().getId();
            int gradePoints = attempt->getGradePoints();

            if (attemptAssessmentId == assessmentId) {
                aggregate+=gradePoints*weightingOfAssessment/100.0;
            }
        }
    }
    aggregate = gradeSystem.round(aggregate);
    return aggregate;
}
/*
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
        creditsEarned=module.getCredits();
        if (numberOfAttempt > 2){
            setFinalCode(&ModuleCodes::PX);
        }
        else if (type == "refered") {
            setFinalCode(&ModuleCodes::PR);
        }
        else if (type == "repeated") {
            setFinalCode(&ModuleCodes::PF);
        }
        else if (getSubmittedLate()){
            setFinalCode(&ModuleCodes::PL);
        }
        else{
            setFinalCode(&ModuleCodes::PA);
        }
    }
    else{
        passed = false;
        creditsEarned = 0;
        if (numberOfAttempt == 2){
            if (getHadNec() == false){
                setFinalCode(&ModuleCodes::FN);
            }
            else{
                if (type == "referred"){
                    setFinalCode(&ModuleCodes::F1);

                }
                else{
                    setFinalCode(&ModuleCodes::FP);
                }
            }
        }
        else if (numberOfAttempt > 2){
                setFinalCode(&ModuleCodes::FN);
        }
        else{
                setFinalCode(&ModuleCodes::FP);
        }
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

int ModuleAttempt::numberOfNotPassed(){
    int notPassed=0;
    std::vector<std::reference_wrapper<AssessmentAttempt>> finalAttempts = getFinalattempts();
    for (const auto& attempt : finalAttempts) {
        std::string attemptGrade = attempt.get().getGrade();
        if(!gradeSystem.isGreaterThanThreshold(attemptGrade, "3LOW")){
            notPassed++;
        }
    }
    return notPassed;
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

bool ModuleAttempt::getSubmittedLate(){
    submittedLate = false;
    std::vector<std::reference_wrapper<AssessmentAttempt>> finalAttempts = getFinalattempts();
    for (const auto& attempt : finalAttempts){
        if (attempt.get().isSubmittedLate() == true){
            hadMisconduct = true;
        }
    }
    return hadMisconduct;
}


void ModuleAttempt::populatePossibleDecisions(){
    if (module.getType() == "optional"){
            posibleCodes.push_back(&ModuleCodes::FO);
    }

    int notPassed = 0;
    std::vector<std::reference_wrapper<AssessmentAttempt>> finalAttempts = getFinalattempts();
    for (const auto& attempt : finalAttempts) {
            std::string grade = attempt.get().getGrade();
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
    std::vector<std::reference_wrapper<AssessmentAttempt>> finalAttempts = getLatestAttempts();//final
    const ModuleCode* code = getFinalCode();
    std::string stringCode = code->getCode();
    if(stringCode=="RR"){
        for (const auto& attempt : finalAttempts){
             std::string grade = attempt.get().getGrade();
             if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
                //final attempt
                if(attempt.get().getNumberOfAttempt()==2){
                    //RF
                    attempt.get().setPossibleDecisions(&AssessmentCodes::RF);
                }
                else if(attempt.get().getAssessment().getType()=="exam"){
                    attempt.get().setPossibleDecisions(&AssessmentCodes::RE);
                    attempt.get().setPossibleDecisions(&AssessmentCodes::RW);
                }
                else if(attempt.get().getAssessment().getType()=="coursework"){
                    attempt.get().setPossibleDecisions(&AssessmentCodes::RK);
                }
                else if(attempt.get().getAssessment().getType()=="test"){
                    attempt.get().setPossibleDecisions(&AssessmentCodes::RT);
                }
                else if(attempt.get().getAssessment().getType()=="test"){
                    attempt.get().setPossibleDecisions(&AssessmentCodes::RT);
                }
                else{
                    attempt.get().setPossibleDecisions(&AssessmentCodes::RM);
                }
                attempt.get().setPossibleDecisions(&AssessmentCodes::RN);
                attempt.get().setPossibleDecisions(&AssessmentCodes::DF);
             }
        }
    }
}

void ModuleAttempt::failElements(){
    std::vector<std::reference_wrapper<AssessmentAttempt>> finalAttempts = getLatestAttempts();
    const ModuleCode* code = getFinalCode();
    std::string stringCode = code->getCode();
    if(stringCode=="FA"){
        for (const auto& attempt : finalAttempts){
             std::string grade = attempt.get().getGrade();
             if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
                attempt.get().setPossibleDecisions(&AssessmentCodes::FA);
                attempt.get().setPossibleDecisions(&AssessmentCodes::FR);
                attempt.get().setPossibleDecisions(&AssessmentCodes::DF);
            }
        }
    if(stringCode=="FM"){
            for (const auto& attempt : finalAttempts){
                std::string grade = attempt.get().getGrade();
                if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
                    attempt.get().setPossibleDecisions(&AssessmentCodes::FW);
                    attempt.get().setPossibleDecisions(&AssessmentCodes::FR);
                    attempt.get().setPossibleDecisions(&AssessmentCodes::DF);
                }
            }
        }
    if (stringCode=="FM"){
            for (const auto& attempt : finalAttempts){
                std::string grade = attempt.get().getGrade();
                if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
                    attempt.get().setPossibleDecisions(&AssessmentCodes::FA);
                    attempt.get().setPossibleDecisions(&AssessmentCodes::FW);
                    attempt.get().setPossibleDecisions(&AssessmentCodes::FR);
                    attempt.get().setPossibleDecisions(&AssessmentCodes::DF);
                }
            }
        }
    }
    if (stringCode=="FO"){
        for (const auto& attempt : finalAttempts){
            std::string grade = attempt.get().getGrade();
            if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
                attempt.get().setPossibleDecisions(&AssessmentCodes::FO);
                attempt.get().setPossibleDecisions(&AssessmentCodes::DF);
            }
        }
    }
}


bool ModuleAttempt::getHadNec() const{
    bool needFirstSeet = false;
    for (const auto& attempt : attempts){
        const AssessmentCode* code = attempt.get().getCode();
        std::string stringCode = code->getCode();
        for (const auto* fsCode : AssessmentCodes::FIRST_SIT_CODES) {
            if (stringCode == fsCode->getCode()) {
                needFirstSeet = true;
            }
        }
    }
    return needFirstSeet;
}

void ModuleAttempt::applyMisconduct(){
    for (const auto& attempt : attempts){
        if (attempt.get().getMisconduct()!=nullptr){
            if (attempt.get().getMisconduct()->getOutcome()=="overall module grade is capped at zero"){
                grade = "ZERO";
                aggregate = 0;
                if(passed == true){
                    setFinalCode(&ModuleCodes::PJ);
                    attempt.get().setCode(&AssessmentCodes::PJ);
                }
                else{
                    if(numberOfAttempt<2){
                        setFinalCode(&ModuleCodes::FC);
                        attempt.get().setCode(&AssessmentCodes::FC);
                    }
                }
            }
            else if(attempt.get().getMisconduct()->getOutcome()=="no credit given for the module"){
                creditsEarned=0;
                setFinalCode(&ModuleCodes::FN);
                attempt.get().setCode(&AssessmentCodes::FN);
            }
            else if(attempt.get().getMisconduct()->getOutcome()=="termination of studies"){
                creditsEarned=0;
                setFinalCode(&ModuleCodes::WD);
            }
            else {
               attempt.get().applyMisconduct();
            }
        }
    }
}


void ModuleAttempt::transferMisconduct(){
    for (size_t i = 0; i < attempts.size(); ++i) {
        auto& first = attempts[i].get();
        std::string firstAssessmentId = first.getAssessment().getId();
        int firstAssessmentNumber = first.getNumberOfAttempt();
        if (first.getMisconduct() != nullptr) {
            for (size_t j = i + 1; j < attempts.size(); ++j) {
                auto& second = attempts[j].get();
                std::string secondAssessmentId = second.getAssessment().getId();
                int secondAssessmentNumber = second.getNumberOfAttempt();
                if (firstAssessmentId == secondAssessmentId && firstAssessmentNumber<secondAssessmentNumber) {
                    second.setMisconduct(first.getMisconduct());
                }
            }
        }
    }
}

*/

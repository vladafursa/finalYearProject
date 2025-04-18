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
            std::string attemptAssessmentId;
            if(attempt->getOriginalAttempt()!=nullptr){
                attemptAssessmentId = attempt->getOriginalAttempt()->getId();
            }
            else{
                attemptAssessmentId = attempt->getAssessment().getId();
            }
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
            std::string attemptAssessmentId;
            if(attempt->getOriginalAttempt()!=nullptr){
                attemptAssessmentId = attempt->getOriginalAttempt()->getId();
            }
            else{
                attemptAssessmentId = attempt->getAssessment().getId();
            }

            int gradePointsOfAssessmentAttempt = attempt->getGradePoints();

            if (attemptAssessmentId == assessmentId && gradePointsOfAssessmentAttempt >= maxGradePoints) {
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
            std::string attemptAssessmentId;

            if(attempt->getOriginalAttempt()!=nullptr){
                if(numberOfRepeated()!=finalAttempts.size()){//if all repeated, new weighting
                    attemptAssessmentId = attempt->getOriginalAttempt()->getId();
                }
                else{
                    attemptAssessmentId = attempt->getAssessment().getId();
                }
            }
            else{
                attemptAssessmentId = attempt->getAssessment().getId();
            }
            int gradePoints = attempt->getGradePoints();

            if (attemptAssessmentId == assessmentId) {
                aggregate+=gradePoints*weightingOfAssessment/100.0;
            }
        }
    }
    aggregate = gradeSystem.round(aggregate);
    return aggregate;
}


int ModuleAttempt::numberOfNotPassed(){
    int notPassed=0;
    std::vector<std::shared_ptr<AssessmentAttempt>> finalAttempts = getFinalattempts();
    for (const auto& attempt : finalAttempts) {
        std::string attemptGrade = attempt->getGrade();
        if(!gradeSystem.isGreaterThanThreshold(attemptGrade, "3LOW")){
            notPassed++;
        }
    }
    return notPassed;
}


void ModuleAttempt::assignTypes() {
    for (const auto& current : attempts) {
        if (current->getNumberOfAttempt() == 1 || AssessmentCodes::FIRST_SIT_CODES.contains(current->getFinalCode())) {
            current->setType("original");
            continue;
        }

        for (const auto& prev : attempts) {
            bool sameAssessment = false;

            const std::string& currentCode = current->getOriginalAttempt() != nullptr
                                                 ? current->getOriginalAttempt()->getId()
                                                 : current->getAssessment().getId();

            const std::string& prevCode = prev->getOriginalAttempt() != nullptr
                                              ? prev->getOriginalAttempt()->getId()
                                              : prev->getAssessment().getId();

            sameAssessment = (currentCode == prevCode);

            if (sameAssessment &&
                prev->getNumberOfAttempt() == current->getNumberOfAttempt() - 1) {

                const AssessmentCode* prevFinalCode = prev->getFinalCode();
                if (prevFinalCode != nullptr) {

                    for (const auto& code : AssessmentCodes::REPEAT_CODES) {
                        if (code->getCode() == prevFinalCode->getCode()) {
                            current->setType("repeat");
                            break;
                        }
                    }
                    for (const auto& code : AssessmentCodes::REFERRED_CODES) {
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



int ModuleAttempt::numberOfRepeated(){
    int numberOfRepeated=0;
    std::vector<std::shared_ptr<AssessmentAttempt>> finalAttempts = getLatestAttempts();
    for (const auto& attempt : finalAttempts) {
        if(attempt->getType() == "repeat"){
            numberOfRepeated++;
        }
    }
    return numberOfRepeated;
}


bool ModuleAttempt::checkAllElementsPassed(){
    bool allPassed = true;
    std::vector<std::shared_ptr<AssessmentAttempt>> finalAttempts = getFinalattempts();
    for (const auto& attempt : finalAttempts) {
        std::string grade = attempt->getGrade();
        if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
            allPassed=false;
        }
    }
    return allPassed;
}


bool ModuleAttempt::determinSpecialPass(){
    bool canPass = false;
    std::vector<std::shared_ptr<AssessmentAttempt>> failedAttempts;
    std::vector<std::shared_ptr<AssessmentAttempt>> finalAttempts = getFinalattempts();
    for (const auto& attempt : finalAttempts) {
        std::string attemptGrade = attempt->getGrade();
        if(!gradeSystem.isGreaterThanThreshold(attemptGrade, "3LOW")){
            failedAttempts.push_back(attempt);
        }
    }
    size_t numberOfFails = failedAttempts.size();
    if (gradeSystem.isGreaterThanThreshold(grade, "3LOW") && numberOfFails==1){
        std::string failedGrade = failedAttempts[0]->getGrade();
        if (gradeSystem.isGreaterThanThreshold(failedGrade, "FMARG")){
            canPass = true;
        }
    }
    return canPass;
}

bool ModuleAttempt::getSubmittedLate(){
    submittedLate = false;
    std::vector<std::shared_ptr<AssessmentAttempt>> finalAttempts = getFinalattempts();
    for (const auto& attempt : finalAttempts){
        if (attempt->isSubmittedLate() == true){
            submittedLate = true;
        }
    }
    return submittedLate;
}

bool ModuleAttempt::getHadMisconduct(){
    hadMisconduct = false;
    for (const auto& attempt : attempts){
        if (attempt->getMisconduct()!=nullptr){
            hadMisconduct = true;
        }
    }
    return hadMisconduct;
}

bool ModuleAttempt::getHadNec() const{
    bool hadNec = false;
    for (const auto& attempt : attempts){
        if (attempt->getNec()!=nullptr){
            hadNec = true;
        }
    }
    return hadNec;
}


bool ModuleAttempt::needFirstSeet() const{
    bool needFirstSeet = false;
    for (const auto& attempt : attempts){
        if(attempt->getFinalCode()!=nullptr){
            const AssessmentCode* code = attempt->getFinalCode();
            std::string stringCode = code->getCode();
            for (const auto* fsCode : AssessmentCodes::FIRST_SIT_CODES) {
                if (stringCode == fsCode->getCode()) {
                    needFirstSeet = true;
                }
            }
        }
    }
    return needFirstSeet;
}


void ModuleAttempt::applyMisconduct(){
    for (const auto& attempt : attempts){
        if (attempt->getMisconduct()!=nullptr){
            if (attempt->getMisconduct()->getOutcome()=="overall module grade is capped at zero"){
                grade = "ZERO";
                aggregate = 0;
                if(passed == true){
                    setFinalCode(&ModuleCodes::PJ);
                    attempt->setCode(&AssessmentCodes::PJ);
                }
                else{
                    if(numberOfAttempt<2){
                        setFinalCode(&ModuleCodes::FC);
                        attempt->setCode(&AssessmentCodes::FC);
                    }
                }
            }
            else if(attempt->getMisconduct()->getOutcome()=="no credit given for the module"){
                creditsEarned=0;
                setFinalCode(&ModuleCodes::FN);
                attempt->setCode(&AssessmentCodes::FN);
            }
            else if(attempt->getMisconduct()->getOutcome()=="termination of studies"){
                creditsEarned=0;
                setFinalCode(&ModuleCodes::WD);
            }
            else {
                attempt->applyMisconduct();
            }
        }
    }
}



void ModuleAttempt::generateCode(){
    if (checkAllElementsPassed() || determinSpecialPass()){
        passed = true;
        creditsEarned=module.getCredits();
        if (numberOfAttempt > 2){
            setFinalCode(&ModuleCodes::PX);
        }
        else if (type == "referral") {
            setFinalCode(&ModuleCodes::PR);
        }
        else if (type == "repeat") {
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
        populatePossibleDecisions();
        if (numberOfAttempt == 2){
            if (getHadNec() == false){
                setFinalCode(&ModuleCodes::FN);
            }
            else{
                if (type == "referral"){
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


void ModuleAttempt::populatePossibleDecisions(){
    if (module.getType() == "optional"){
        posibleCodes.push_back(&ModuleCodes::FO);
    }

    int notPassed = 0;
    int needFirstSit=0;
    std::vector<std::shared_ptr<AssessmentAttempt>> finalAttempts = getFinalattempts();
    for (const auto& attempt : finalAttempts) {
        std::string grade = attempt->getGrade();
        if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
            notPassed++;
        }

        if(attempt->getFinalCode()!=nullptr){
            const AssessmentCode* code = attempt->getFinalCode();
            std::string stringCode = code->getCode();
            for (const auto* fsCode : AssessmentCodes::FIRST_SIT_CODES) {
                if (stringCode == fsCode->getCode()) {
                    needFirstSit++;
                }
            }
        }
    }

    if (needFirstSit == notPassed){
        for (const auto& attempt : finalAttempts) {
            setFinalCode(&ModuleCodes::S1);
        }
    }
    else{
        if (notPassed>1){
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
        }
}

void ModuleAttempt::referElements(){
    std::vector<std::shared_ptr<AssessmentAttempt>> finalAttempts = getLatestAttempts();//final
    const ModuleCode* code = getFinalCode();
    std::string stringCode = code->getCode();
    if(stringCode=="RR"){
        for (const auto& attempt : finalAttempts){
            std::string grade = attempt->getGrade();
            if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
                //final attempt
                if(attempt->getNumberOfAttempt()==2){
                    //RF
                    attempt->setPossibleDecisions(&AssessmentCodes::RF);
                }
                else if(attempt->getAssessment().getType()=="Exam"){
                    attempt->setPossibleDecisions(&AssessmentCodes::RE);
                    attempt->setPossibleDecisions(&AssessmentCodes::RW);
                }
                else if(attempt->getAssessment().getType()=="Coursework"){
                    attempt->setPossibleDecisions(&AssessmentCodes::RK);
                }
                else if(attempt->getAssessment().getType()=="Test"){
                    attempt->setPossibleDecisions(&AssessmentCodes::RT);
                }
                else{
                    attempt->setPossibleDecisions(&AssessmentCodes::RM);
                }
                attempt->setPossibleDecisions(&AssessmentCodes::RN);
                attempt->setPossibleDecisions(&AssessmentCodes::DF);
            }
        }
    }
}

void ModuleAttempt::failElements(){
    std::vector<std::shared_ptr<AssessmentAttempt>> finalAttempts = getLatestAttempts();
    const ModuleCode* code = getFinalCode();
    std::string stringCode = code->getCode();
    if(stringCode=="FA"){
        for (const auto& attempt : finalAttempts){
            std::string grade = attempt->getGrade();
            if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
                attempt->setPossibleDecisions(&AssessmentCodes::FA);
                attempt->setPossibleDecisions(&AssessmentCodes::FR);
                attempt->setPossibleDecisions(&AssessmentCodes::DF);
            }
        }
    }
    if(stringCode=="FM"){
        for (const auto& attempt : finalAttempts){
            std::string grade = attempt->getGrade();
            if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
                attempt->setPossibleDecisions(&AssessmentCodes::FW);
                attempt->setPossibleDecisions(&AssessmentCodes::FR);
                attempt->setPossibleDecisions(&AssessmentCodes::DF);
            }
        }
    }
    if (stringCode=="FR"){
        for (const auto& attempt : finalAttempts){
            std::string grade = attempt->getGrade();
            if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
                attempt->setPossibleDecisions(&AssessmentCodes::FA);
                attempt->setPossibleDecisions(&AssessmentCodes::FW);
                attempt->setPossibleDecisions(&AssessmentCodes::FR);
                attempt->setPossibleDecisions(&AssessmentCodes::DF);
            }
        }
    }

    if (stringCode=="FO"){
        for (const auto& attempt : finalAttempts){
            std::string grade = attempt->getGrade();
            if(!gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
                attempt->setPossibleDecisions(&AssessmentCodes::FO);
                attempt->setPossibleDecisions(&AssessmentCodes::DF);
            }
        }
    }
}


void ModuleAttempt::transferMisconduct(){
    for (size_t i = 0; i < attempts.size(); ++i) {
        auto& first = attempts[i];
        std::string firstAssessmentId;
        if(first->getOriginalAttempt()!=nullptr){
            firstAssessmentId = first->getOriginalAttempt()->getId();
        }
        else{
            firstAssessmentId = first->getAssessment().getId();
        }

        int firstAssessmentNumber = first->getNumberOfAttempt();
        if (first->getMisconduct() != nullptr) {
            for (size_t j = i + 1; j < attempts.size(); ++j) {
                auto& second = attempts[j];
                std::string secondAssessmentId = second->getOriginalAttempt()->getId();
                int secondAssessmentNumber = second->getNumberOfAttempt();
                if (firstAssessmentId == secondAssessmentId && firstAssessmentNumber<secondAssessmentNumber) {
                    second->setMisconduct(first->getMisconduct());
                }
            }
        }
    }
}


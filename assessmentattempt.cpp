#include "assessmentattempt.h"

//constructors

AssessmentAttempt::AssessmentAttempt(std::string providedStudentNumber,
                const Assessment& providedAssessment,
                int providedNumberOfAttempt,
                bool providedSubmittedLate,
                int providedGradePoints,
                const AssessmentCode* providedCode,
                const NEC* providedNec,
                const Misconduct* providedMisconduct,
                const Assessment* providedOriginalAttempt): assessment(providedAssessment) {

    studentNumber=providedStudentNumber;
    numberOfAttempt=providedNumberOfAttempt;
    submittedLate = providedSubmittedLate;
    gradePoints = providedGradePoints;
    code = providedCode;
    nec = providedNec;
    misconduct = providedMisconduct;
    originalAttempt = providedOriginalAttempt;
}

//getters
std::string AssessmentAttempt::getStudentNumber() const{
    return studentNumber;
}

const Assessment& AssessmentAttempt::getAssessment() const {
    return assessment;
}

int AssessmentAttempt::getNumberOfAttempt() const{
    return numberOfAttempt;
}

std::string AssessmentAttempt::getType() const{
    return type;
}

bool AssessmentAttempt::isSubmittedLate() const{
    return submittedLate;
}

int AssessmentAttempt::getGradePoints() const{
    return gradePoints;
}

std::string AssessmentAttempt::getGrade(){
    grade = gradeSystem.assignGrade(gradePoints);
    return grade;
}

const AssessmentCode* AssessmentAttempt::getCode() const{
    return code;
}

const NEC* AssessmentAttempt::getNec() const{
    return nec;
}

const Misconduct* AssessmentAttempt::getMisconduct() const{
    return misconduct;
}

//setters
void AssessmentAttempt::setStudentNumber(const std::string providedStudentNumber){
    studentNumber=providedStudentNumber;
}

void AssessmentAttempt::setNumberOfAttempt(int providedNumberOfAttempt){
    numberOfAttempt=providedNumberOfAttempt;
}

void AssessmentAttempt::setType(const std::string providedType){
    type=providedType;
}

void AssessmentAttempt::setSubmittedLate(bool providedSubmittedLate){
    submittedLate = providedSubmittedLate;
}

void AssessmentAttempt::setGradePoints(int providedGradePoints){
    gradePoints = providedGradePoints;
}

void AssessmentAttempt::setGrade(std::string providedGrade){
    grade = providedGrade;
}

void AssessmentAttempt::setCode(const AssessmentCode* providedCode){
    code = providedCode;
}

void AssessmentAttempt::setNec(const NEC* providedNec){
    nec = providedNec;
}

void AssessmentAttempt::setMisconduct(const Misconduct* providedMisconduct){
    misconduct = providedMisconduct;
}

const std::vector<const AssessmentCode*>& AssessmentAttempt::getPossibleCodes() const{
    return posibleCodes;
}

void AssessmentAttempt::setPossibleDecisions(const AssessmentCode* providedPossibleCode){
    posibleCodes.push_back(providedPossibleCode);
}

void AssessmentAttempt::populatePossibleDecisions(){
    //nec
    if(nec!=nullptr){
        const AssessmentCode* code = getCode();
        std::string stringCode = code->getCode();
        if(nec->getType()=="next opportunity" && (stringCode=="NN" || stringCode=="NS")){//only if not submitted
            setCode(&AssessmentCodes::S1);
            posibleCodes.push_back(&AssessmentCodes::S2);
            posibleCodes.push_back(&AssessmentCodes::S3);
            posibleCodes.push_back(&AssessmentCodes::S4);
        }
    }
    if(submittedLate == true && gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
         setCode(&AssessmentCodes::PL);
    }

    if(type=="referral"){
         if(gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
            setCode(&AssessmentCodes::PR);
        }
         else{
            setCode(&AssessmentCodes::FE);
        }
    }
    if(type=="repeat" && gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
         setCode(&AssessmentCodes::PY);
    }
    if(numberOfAttempt==2 && !gradeSystem.isGreaterThanThreshold(grade, "3LOW") && nec==nullptr){
        setCode(&AssessmentCodes::FN);
    }

}

void AssessmentAttempt::applyMisconduct(){
    if(misconduct!=nullptr){
        if(misconduct->getOutcome()=="the assessment is capped at low 3"){
            if (gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
            setGrade("3LOW");
            setGradePoints(4);
            setCode(&AssessmentCodes::PB);
            }
            else{
             setCode(&AssessmentCodes::FC);//???????
            }
        }
        if(misconduct->getOutcome()=="the assessment is capped at zero"){
        if (gradeSystem.isGreaterThanThreshold(grade, "3LOW")){
            setGrade("ZERO");
            setGradePoints(0);
            setCode(&AssessmentCodes::PJ);
        }else{
             setCode(&AssessmentCodes::FC);
            }
        }
    }
}



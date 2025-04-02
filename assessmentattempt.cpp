#include "assessmentattempt.h"

//constructors

AssessmentAttempt::AssessmentAttempt(std::string providedStudentNumber,
                const Assessment& providedAssessment,
                int providedNumberOfAttempt,
                std::string providedType,
                bool providedSubmittedLate,
                int providedGrade,
                const AssessmentCode* providedCode,
                const NEC* providedNec,
                const Misconduct* providedMisconduct): assessment(providedAssessment) {

    studentNumber=providedStudentNumber;
    numberOfAttempt=providedNumberOfAttempt;
    type=providedType;
    submittedLate = providedSubmittedLate;
    grade = providedGrade;
    code = providedCode;
    nec = providedNec;
    misconduct = providedMisconduct;
}

//getters
std::string AssessmentAttempt::getStudentNumber() const{
    return studentNumber;
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

int AssessmentAttempt::getGrade() const{
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

void AssessmentAttempt::setGrade(int providedGrade){
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

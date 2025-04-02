#include "misconduct.h"

//constructors
Misconduct::Misconduct()
{

}
Misconduct::Misconduct(std::string providedCaseID, std::string providedStudentNumber, std::string providedType, std::string providedOutcome){
    caseID=providedCaseID;
    studentNumber=providedStudentNumber;
    type=providedType;
    outcome=providedOutcome;
}

//getters
std::string Misconduct::getCaseID() const{
    return caseID;
}

std::string Misconduct::getStudentNumber() const{
    return studentNumber;
}

std::string Misconduct::getType() const{
    return type;
}

std::string Misconduct::getOutcome() const{
    return outcome;
}
//setters
void Misconduct::setCaseID(std::string providedCaseID){
    caseID=providedCaseID;
}

void Misconduct::setStudentNumber( std::string providedStudentNumber){
    studentNumber=providedStudentNumber;
}

void Misconduct::setType(std::string providedType){
    type=providedType;
}

void Misconduct::setOutcome(std::string providedOutcome){
    outcome=providedOutcome;
}

#include "nec.h"

NEC::NEC()
{

}
NEC::NEC(std::string providedReferenceNumber, std::string providedStudentNumber, bool providedUpheld, std::string providedType){
    referenceNumber=providedReferenceNumber;
    studentNumber=providedStudentNumber;
    upheld=providedUpheld;
    type=providedType;
}

// getters
std::string NEC::getReferenceNumber() const{
    return referenceNumber;
}
std::string NEC::getStudentNumber() const{
    return studentNumber;
}
bool NEC::getUphend() const{
    return upheld;
}
std::string NEC::getType() const{
    return type;
}

// setters
void NEC::setReferenceNumber(std::string providedReferenceNumber){
    referenceNumber=providedReferenceNumber;
}
void NEC::setStudentNumber(std::string providedStudentNumber){
     studentNumber=providedStudentNumber;
}
void NEC::setUphend(bool providedUpheld){
     upheld=providedUpheld;
}
void NEC::setType(std::string providedType){
      type=providedType;
}

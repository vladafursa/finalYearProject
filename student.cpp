#include "student.h"


Student::Student(std::string providedStudentNumber, std::string providedName, std::string providedCourse, bool providedEnrolled, std::string providedEnrollmentDate, bool providedT4Status, bool providedInternationalStatus){
    studentNumber = providedStudentNumber;
    name = providedName;
    course = providedCourse;
    fullyEnrolled = providedEnrolled;
    dateEnrolled = providedEnrollmentDate;
    T4 = providedT4Status;
    international = providedInternationalStatus;
}

//getters
std::string Student::getStudentNumber() const{
    return studentNumber;
}

std::string Student::getName() const{
    return name;
}
std::string Student::getCourse() const{
    return course;
}

bool Student::isFullyEnrolled() const {
    return fullyEnrolled;
}
std::string Student::getDateEnrolled() const{
    return dateEnrolled;
}

bool Student::isT4() const{
    return T4;
}
bool Student::isInternational() const{
    return international;
}


//setters
void Student::setStudentNumber(std::string providedStudentNumber){
    studentNumber = providedStudentNumber;
}

void Student::setName(std::string providedName){
    name = providedName;
}

void Student::setCourse(std::string providedCourse){
    course = providedCourse;
}

void Student::setFullyEnrolled(bool providedEnrolled){
    fullyEnrolled = providedEnrolled;
}

void Student::setDateEnrolled(std::string providedEnrollmentDate) {
    dateEnrolled = providedEnrollmentDate;
}

void Student::setT4(bool providedT4Status){
    T4 = providedT4Status;
}

void Student::setInternational(bool providedInternationalStatus) {
    international = providedInternationalStatus;
}

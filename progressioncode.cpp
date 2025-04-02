#include "progressioncode.h"

ProgressionCode::ProgressionCode()
{

}
//inherited constructor
ProgressionCode::ProgressionCode(const std::string providedCode, const std::string providedDescription, const bool providedStudentRecordCreated, const bool providedProgresstoNextStage, bool providedProgresstoNextYear): Code(providedCode, providedDescription){
    studentRecordCreated=providedStudentRecordCreated;
    progressToNextStage=providedProgresstoNextStage;
    progresstoNextYear=providedProgresstoNextYear;
}
//getters
bool ProgressionCode::getStudentRecordCreated() const{
    return studentRecordCreated;
}
bool ProgressionCode::getProgressToNextStage() const{
    return progressToNextStage;
}
bool ProgressionCode::getProgressToNextYear() const{
    return progresstoNextYear;
}
//setters
void  ProgressionCode::setStudentRecordCreated(bool providedStudentRecordCreated){
    studentRecordCreated=providedStudentRecordCreated;
}
void  ProgressionCode::setProgressToNextStage(bool providedProgresstoNextStage){
    progressToNextStage=providedProgresstoNextStage;
}
void ProgressionCode::setProgressToNextYear(bool providedProgresstoNextYear){
    progresstoNextYear=providedProgresstoNextYear;
}

//debugging
void ProgressionCode::display() const{
    Code::display();
    std::cout<<"created student record? "<<studentRecordCreated<<" can progress to next stage? "<<progressToNextStage<<" can progress to next year? "<<progresstoNextYear<<std::endl;
}

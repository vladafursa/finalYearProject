#include "assessment.h"
//constructors
Assessment::Assessment(){

}

Assessment::Assessment(std::string assessmentID, std::string assessmentType, std::string assessmentName){
    id = assessmentID;
    type = assessmentType;
    name = assessmentName;
}

//setters
void Assessment::setID(std::string assessmentID){
    id = assessmentID;
}

void Assessment::setType(std::string assessmentType){
    type = assessmentType;
}

void Assessment::setName(std::string assessmentName){
    name = assessmentName;
}

//getters
std::string Assessment::getId() const{
    return id;
}

std::string Assessment::getType() const{
    return type;
}

std::string Assessment::getName() const{
    return name;
}


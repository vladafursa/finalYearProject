#include "module.h"


Module::Module(std::string providedCode,
                     std::string providedName,
                     int providedCredits){

    code = providedCode;
    name = providedName;
    credits = providedCredits;
}

//getters
std::string Module::getCode() const{
    return code;
}

std::string Module::getName() const{
    return name;
}

std::string Module::getYear() const{
    return year;
}

std::string Module::getType() const{
    return type;
}

int Module::getCredits() const{
    return credits;
}

const AssessmentWeightsMap& Module::getAssessmentsWithWeights() const{
    return assessmentsWithWeights;
}

// setters
void Module::setCode(std::string providedCode){
    code = providedCode;
}

void Module::setName(std::string providedName){
    name = providedName;
}

void Module::setYear(std::string providedYear){
    year = providedYear;
}

void Module::setType(std::string providedType){
    type = providedType;
}

void Module::setCredits(int providedCredits){
    credits = providedCredits;
}

void Module::setAssessmentWeights(AssessmentWeightsMap& providedAssessmentWeights){
    assessmentsWithWeights = providedAssessmentWeights;
}


void Module::addAssessment(Assessment& assessment, int weight) {
    assessmentsWithWeights[std::ref(assessment)] = weight;
}

#include "course.h"

//constructor
Course::Course(std::string providedName,
       const std::vector<std::reference_wrapper<Stage>>& providedStages,
       std::string providedStartClassification,
               std::string providedType){
    name = providedName;
    stages = providedStages;
    startClassification = providedStartClassification;
    type = providedType;
}

//getters
std::string Course::getName() const {
    return name;
}

const std::vector<std::reference_wrapper<Stage>>& Course::getStages() const {
    return stages;
}

std::string Course::getStartClassification() const {
    return startClassification;
}

std::string Course::getType() const {
    return type;
}

//setters
void Course::setName(std::string providedName) {
    name = providedName;
}

void Course::setStages(const std::vector<std::reference_wrapper<Stage>>& providedStages) {
    stages = providedStages;
}

void Course::setStartClassification(std::string providedStartClassification) {
    startClassification = providedStartClassification;
}

void Course::setType( std::string providedType) {
    type = providedType;
}

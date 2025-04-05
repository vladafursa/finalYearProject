#include "stage.h"


Stage::Stage(int providedCredits, int providedYear, int providedLevel, const std::vector<std::reference_wrapper<Module>>& providedModule, int providedLimitOfCredits){
    credits = providedCredits;
    year = providedYear;
    level = providedLevel;
    modules = providedModule;
    limitOfCredits = providedLimitOfCredits;
}

//getters
int Stage::getCredits() const{
    return credits;
}

int Stage::getYear() const{
    return year;
}

int Stage::getLevel() const{
    return level;
}

const std::vector<std::reference_wrapper<Module>>& Stage::getModules() const{
    return modules;
}

int Stage::getLimitOfCredits() const{
    return limitOfCredits;
}

//setters
void Stage::setCredits(int providedCredits){
    credits = providedCredits;
}

void Stage::setYear(int providedYear){
    year = providedYear;
}

void Stage::setLevel(int providedLevel){
    level = providedLevel;
}

void Stage::setModules(const std::vector<std::reference_wrapper<Module>>& providedModule){
    modules = providedModule;
}

void Stage::setLimitOfCredits(int providedLimitOfCredits){
    limitOfCredits = providedLimitOfCredits;
}

#include "stage.h"


Stage::Stage(std::string providedId, int providedCredits, int providedYear, int providedLevel, const std::vector<std::shared_ptr<Module>>& providedModule, int providedLimitOfCredits){
    id =  providedId;
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

const std::vector<std::shared_ptr<Module>>& Stage::getModules() const{
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

void Stage::setModules(const std::vector<std::shared_ptr<Module>>& providedModule){
    modules = providedModule;
}

void Stage::setLimitOfCredits(int providedLimitOfCredits){
    limitOfCredits = providedLimitOfCredits;
}

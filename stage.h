#ifndef STAGE_H
#define STAGE_H
#include "module.h"

class Stage
{
private:
    int credits;
    int year;
    int level;
    std::vector<std::reference_wrapper<Module>> modules;
    int limitOfCredits;
public:
    //constructor
    Stage(int providedCredits, int providedYear, int providedLevel, const std::vector<std::reference_wrapper<Module>>& providedModule, int providedLimitOfCredits);

    //getters
    int getCredits() const;
    int getYear() const;
    int getLevel() const;
    const std::vector<std::reference_wrapper<Module>>& getModules() const;
    int getLimitOfCredits() const;

    //setters
    void setCredits(int providedCredits);
    void setYear(int providedYear);
    void setLevel(int providedLevel);
    void setModules(const std::vector<std::reference_wrapper<Module>>& providedModule);
    void setLimitOfCredits(int providedLimitOfCredits);
};

#endif // STAGE_H

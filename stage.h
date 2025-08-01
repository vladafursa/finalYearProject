#ifndef STAGE_H
#define STAGE_H
#include "module.h"

class Stage
{
private:
    std::string id;
    int credits;
    int year;
    int level;
    std::vector<std::shared_ptr<Module>> modules;
    int limitOfCredits;
public:
    //constructor
    Stage(std::string providedId, int providedCredits, int providedYear, int providedLevel, const std::vector<std::shared_ptr<Module>>& providedModule, int providedLimitOfCredits);

    //getters
    std::string getId() const{
        return id;
    }
    int getCredits() const;
    int getYear() const;
    int getLevel() const;
    const std::vector<std::shared_ptr<Module>>& getModules() const;
    int getLimitOfCredits() const;

    //setters
    void setId(std::string providedId){
        id = providedId;
    }
    void setCredits(int providedCredits);
    void setYear(int providedYear);
    void setLevel(int providedLevel);
    void setModules(const std::vector<std::shared_ptr<Module>>& providedModule);
    void setLimitOfCredits(int providedLimitOfCredits);
};

#endif // STAGE_H

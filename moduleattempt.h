#ifndef MODULEATTEMPT_H
#define MODULEATTEMPT_H
#include "module.h"
#include <iostream>
#include <string>
#include <vector>
#include "assessmentattempt.h"
#include "modulecode.h"
#include "CodeConstants.h"

class ModuleAttempt
{
private:
    std::string studentNumber;
    const Module& module;
    int numberOfAttempt;
    std::string type;
    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    bool hadNec;
    double aggregate;
    bool passed;
    int creditsEarned;
    ModuleCode* finalCode;
    std::vector<ModuleCode*> posibleCodes;
public:
    //constructor
    ModuleAttempt(std::string providedStudentNumber,
                  const Module& providedModule,
                  int providedNumberOfAttempt,
                  std::string providedType,
                  std::vector<std::reference_wrapper<AssessmentAttempt>>& providedAttempts);

    //getters
    std::string getStudentNumber() const;
    const Module& getModule() const;
    int getNumberOfAttempt() const;
    std::string getType() const;
    const std::vector<std::reference_wrapper<AssessmentAttempt>>& getAttempts() const;
    bool getHadNec() const;
    double getAggregate() const;
    bool getPassed() const;
    int getCreditsEarned() const;
    ModuleCode* getFinalCode() const;
    const std::vector<ModuleCode*>& getPossibleCodes() const;

    //setters
    void setStudentNumber(std::string providedStudentNumber);
    void setNumberOfAttempt(int providedNumberOfAttempt);
    void setType(std::string providedType);
    void setAtempts(std::vector<std::reference_wrapper<AssessmentAttempt>>& providedAttempts);
    void setHadNec(bool providedHadNec);
    void setAggregate(double providedAggregate);
    void setPassed(bool providedPassed);
    void setCreditsEarned(int providedCreditsEarned);
    void setFinalCode(ModuleCode* providedModuleCode);
    void setPossibleCodes(std::vector<ModuleCode*>& providedPosibleCodes);

    //calculations
    const std::vector<std::reference_wrapper<AssessmentAttempt>>& getFinalattempts() const;
    double calculateAggregate();
    void generateCode();
    void populatePossibleDecisions();
    bool determinPass();
    bool determinSpecialPass();
};

#endif // MODULEATTEMPT_H

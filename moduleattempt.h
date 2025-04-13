#ifndef MODULEATTEMPT_H
#define MODULEATTEMPT_H
#include "module.h"
#include <iostream>
#include <string>
#include <vector>
#include "assessmentattempt.h"
#include "modulecode.h"
#include "CodeConstants.h"
#include "grades.h"

class ModuleAttempt
{
private:
    std::string studentNumber;
    const Module& module;
    int numberOfAttempt;
    std::string type;
    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    bool hadMisconduct;
    bool submittedLate;
    double aggregate;
    bool passed;
    int creditsEarned;
    const ModuleCode* finalCode;
    std::vector<const ModuleCode*> posibleCodes;
    Grades gradeSystem;
    std::string grade;
public:
    //constructor
    ModuleAttempt(std::string providedStudentNumber,
                  const Module& providedModule,
                  int providedNumberOfAttempt,
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
    const ModuleCode* getFinalCode() const;
    const std::vector<const ModuleCode*>& getPossibleCodes() const;
    std::string getGrade();
    bool getHadMisconduct();
    bool getSubmittedLate();

    //setters
    void setStudentNumber(std::string providedStudentNumber);
    void setNumberOfAttempt(int providedNumberOfAttempt);
    void setType(std::string providedType);
    void setAtempts(std::vector<std::reference_wrapper<AssessmentAttempt>>& providedAttempts);
    void setAggregate(double providedAggregate);
    void setPassed(bool providedPassed);
    void setCreditsEarned(int providedCreditsEarned);
    void setFinalCode(const ModuleCode* providedModuleCode);
    void setGrade(std::string providedGrade);
    void setPossibleDecisions(const ModuleCode* providedPossibleCode);

    //calculations
    std::vector<std::reference_wrapper<AssessmentAttempt>> getFinalattempts() const;
    double calculateAggregate();
    bool checkAllElementsPassed();
    void generateCode();
    void populatePossibleDecisions();
    bool determinPass();
    bool determinSpecialPass();
    void applyMisconduct();
    void referElements();
    void failElements();
    void transferMisconduct();
    int numberOfNotPassed();
    std::vector<std::reference_wrapper<AssessmentAttempt>> getLatestAttempts() const;
};

#endif // MODULEATTEMPT_H

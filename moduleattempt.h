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
#include <memory>

class ModuleAttempt
{
private:
    std::string studentNumber;
    Module module;
    int numberOfAttempt;
    std::string type;
    std::vector<std::shared_ptr<AssessmentAttempt>> attempts;
    bool hadMisconduct;
    bool submittedLate;
    double aggregate;
    bool passed;
    int creditsEarned;
    const ModuleCode* finalCode;
    std::vector<const ModuleCode*> posibleCodes;
    Grades gradeSystem;
    std::string grade;
    std::string year;
public:
    //constructor
    ModuleAttempt(std::string providedStudentNumber,
                  Module providedModule,
                  int providedNumberOfAttempt,
                  std::string providedYear,
                  std::vector<std::shared_ptr<AssessmentAttempt>>& providedAttempts);

    //getters
    std::string getStudentNumber() const;
    const Module& getModule() const noexcept {
        return module;
    }
    int getNumberOfAttempt() const;
    std::string getYear() const;
    std::string getType() const;
    const std::vector<std::shared_ptr<AssessmentAttempt>>& getAttempts() const;
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
    void setYear(std::string providedYear);
    void setType(std::string providedType);
    void setAtempts(std::vector<std::shared_ptr<AssessmentAttempt>>& providedAttempts);
    void setAggregate(double providedAggregate);
    void setPassed(bool providedPassed);
    void setCreditsEarned(int providedCreditsEarned);
    void setFinalCode(const ModuleCode* providedModuleCode);
    void setGrade(std::string providedGrade);
    void setPossibleDecisions(const ModuleCode* providedPossibleCode);

    //calculations
    std::vector<std::shared_ptr<AssessmentAttempt>> getFinalattempts() const;
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
    std::vector<std::shared_ptr<AssessmentAttempt>> getLatestAttempts() const;
    void assignTypes();
    int numberOfRepeated();
};

#endif // MODULEATTEMPT_H

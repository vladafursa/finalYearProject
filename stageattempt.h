#ifndef STAGEATTEMPT_H
#define STAGEATTEMPT_H
#include "moduleattempt.h"
#include "stage.h"

class StageAttempt
{
private:
    std::string studentNumber;
    const Stage& stage;
    std::vector<std::shared_ptr<ModuleAttempt>> attempts;
    double aggregate;
    bool passed;
    int creditsEarned;
    const ProgressionCode* finalCode;
    std::vector<const ProgressionCode*> posibleCodes;
    Grades gradeSystem;
    std::string grade;
    int remainingCompensationCredits;
public:
    StageAttempt(std::string providedStudentNumber,
                  const Stage& providedStage,
                  std::vector<std::shared_ptr<ModuleAttempt>>& providedAttempts);

    //getters
    std::string getStudentNumber() const;
    const Stage& getStage() const;
    const std::vector<std::shared_ptr<ModuleAttempt>>& getAttempts() const;
    double getAggregate() const;
    bool getPassed() const;
    int getCreditsEarned();
    const ProgressionCode* getFinalCode() const;
    const std::vector<const ProgressionCode*>& getPossibleCodes() const;
    std::string getGrade();
    int getRemainingCompensationCredits() const;

    //setters
    void setStudentNumber(std::string providedStudentNumber);
    void setAtempts(std::vector<std::shared_ptr<ModuleAttempt>>& providedAttempts);
    void setAggregate(double providedAggregate);
    void setPassed(bool providedPassed);
    void setCreditsEarned(int providedCreditsEarned);
    void setFinalCode(const ProgressionCode* providedProgressionCode);
    void setPossibleCodes( std::vector<const ProgressionCode*>& providedPosibleCodes);
    void setGrade(std::string providedGrade);
    void setRemainingCompensationCredits(int providedRemainingCredits);

    //calculations
    std::vector<std::shared_ptr<ModuleAttempt>> getFinalattempts() const;
    double calculateAggregate();
    bool checkAllModulesPassed();
    void generateCode();
    void populatePossibleDecisions();
    bool determinPass();
    void determinCompensationPass();
    void applyCompensation();
    void applyMisconducts();
    int checkReferred();
    int checkFirstSeats() ;
    int checkFail() ;

};

#endif // STAGEATTEMPT_H

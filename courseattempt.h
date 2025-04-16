#ifndef COURSEATTEMPT_H
#define COURSEATTEMPT_H
#include <iostream>
#include <string>
#include <vector>
#include "stage.h"
#include "stageattempt.h"
#include "course.h"

class CourseAttempt
{
private:
    std::string studentNumber;
    const Course& course;
    std::vector<std::shared_ptr<StageAttempt>> attempts;
    double weightedAwarsClassification;
    double majorityClassification;
    std::string classification;
    const AwardCode* finalCode;
    std::vector<AwardCode*> posibleCodes;
    Grades gradeSystem;
    std::string grade;

public:
    CourseAttempt(std::string providedStudentNumber,
                 const Course& providedCourse,
                 std::vector<std::shared_ptr<StageAttempt>>& providedAttempts);

    std::string getStudentNumber() const;
    const Course& getCourse() const;
    const std::vector<std::shared_ptr<StageAttempt>>& getAttempts() const;
    double getWeightedAwarsClassification() const;
    const AwardCode* getFinalCode() const;
    const std::vector<AwardCode*>& getPossibleCodes() const;
    std::string getGrade();

    //setters
    void setStudentNumber(std::string providedStudentNumber);
    void setAtempts(std::vector<std::shared_ptr<StageAttempt>>& providedAttempts);
    void setWeightedAwarsClassification(double providedWeightedAwarsClassification);
    void setFinalCode(const AwardCode* providedProgressionCode);
    void setPossibleCodes(std::vector<AwardCode*>& providedPosibleCodes);
    void setGrade(std::string providedGrade);

    double calculateAggregate();
    bool checkAllModulesPassed();
    void generateCode();
    void populatePossibleDecisions();
    void calculateProgression();
};

#endif // COURSEATTEMPT_H

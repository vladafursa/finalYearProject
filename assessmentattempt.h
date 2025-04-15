#ifndef ASSESSMENTATTEMPT_H
#define ASSESSMENTATTEMPT_H
#include "assessment.h"
#include <iostream>
#include <string>
#include "assessmentcode.h"
#include "CodeConstants.h"
#include "nec.h"
#include "misconduct.h"
#include "grades.h"

class AssessmentAttempt
{
private:
    std::string studentNumber;
    const Assessment& assessment;
    int numberOfAttempt;
    std::string type;
    bool submittedLate;
    int gradePoints;
    std::string grade;
    const AssessmentCode* finalCode;
    //optional
    const AssessmentCode* code;
    std::vector<const AssessmentCode*> posibleCodes;
    const NEC* nec;
    const Misconduct* misconduct;
    Grades gradeSystem;
    const Assessment* originalAttempt;
public:
    //constructors
    AssessmentAttempt(std::string providedStudentNumber,
            const Assessment& providedAssessment,
            int providedNumberOfAttempt,
            bool providedSubmittedLate,
            int providedGradePoints,
            const AssessmentCode* providedCode = nullptr,//optional
            const NEC* providedNec = nullptr,//optional
            const Misconduct* providedMisconduct = nullptr,
            const Assessment* providedOriginalAttempt = nullptr);//optional

    //getters
    std::string getStudentNumber() const;
    const Assessment& getAssessment() const;
    int getNumberOfAttempt() const;
    std::string getType();
    bool isSubmittedLate() const;
    int getGradePoints() const;
    std::string getGrade();
    const AssessmentCode* getFinalCode() const;
    const AssessmentCode* getCode() const;
    const NEC* getNec() const;
    const Misconduct* getMisconduct() const;
    const std::vector<const AssessmentCode*>& getPossibleCodes() const;
    const Assessment* getOriginalAttempt() const {
        return originalAttempt;
    }

    //setters
    void setStudentNumber(const std::string providedStudentNumber);
    void setNumberOfAttempt(int providedNumberOfAttempt);
    void setType(const std::string providedType);
    void setSubmittedLate(bool providedSubmittedLate);
    void setGradePoints(int providedGradePoints);
    void setGrade(std::string providedGrade);
    void setCode(const AssessmentCode* providedCode);
    void setFinalCode(const AssessmentCode* providedCode);
    void setNec(const NEC* providedNec);
    void setMisconduct(const Misconduct* providedMisconduct);
    void setPossibleDecisions(const  AssessmentCode* providedPossibleCode);
    void applyMisconduct();
    void populatePossibleDecisions();
};

#endif // ASSESSMENTATTEMPT_H

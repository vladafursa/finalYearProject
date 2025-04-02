#ifndef ASSESSMENTATTEMPT_H
#define ASSESSMENTATTEMPT_H
#include "assessment.h"
#include <iostream>
#include <string>
#include "assessmentcode.h"
#include "CodeConstants.h"
#include "nec.h"
#include "misconduct.h"

class AssessmentAttempt
{
private:
    std::string studentNumber;
    const Assessment& assessment;
    int numberOfAttempt;
    std::string type;
    bool submittedLate;
    int grade;
    //optional
    const AssessmentCode* code;
    const NEC* nec;
    const Misconduct* misconduct;

public:
    //constructors
    AssessmentAttempt(std::string providedStudentNumber,
            const Assessment& providedAssessment,
            int providedNumberOfAttempt,
            std::string providedType,
            bool providedSubmittedLate,
            int providedGrade,
            const AssessmentCode* providedCode = nullptr,//optional
            const NEC* providedNec = nullptr,//optional
            const Misconduct* providedMisconduct = nullptr);//optional
    //getters
    std::string getStudentNumber() const;
    int getNumberOfAttempt() const;
    std::string getType() const;
    bool isSubmittedLate() const;
    int getGrade() const;
    const AssessmentCode* getCode() const;
    const NEC* getNec() const;
    const Misconduct* getMisconduct() const;
    //setters
    void setStudentNumber(const std::string providedStudentNumber);
    void setNumberOfAttempt(int providedNumberOfAttempt);
    void setType(const std::string providedType);
    void setSubmittedLate(bool providedSubmittedLate);
    void setGrade(int providedGrade);
    void setCode(const AssessmentCode* providedCode);
    void setNec(const NEC* providedNec);
    void setMisconduct(const Misconduct* providedMisconduct);
};

#endif // ASSESSMENTATTEMPT_H

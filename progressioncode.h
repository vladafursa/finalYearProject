#ifndef PROGRESSIONCODE_H
#define PROGRESSIONCODE_H
#include "code.h"


class ProgressionCode:public Code
{
private:
    bool studentRecordCreated;
    bool progressToNextStage;
    bool progresstoNextYear;
    using Code::Code;

public:
    //constructors
    ProgressionCode();
    ProgressionCode(const std::string providedCode, const std::string providedDescription, const bool providedStudentRecordCreated, const bool providedProgresstoNextStage, bool providedProgresstoNextYear);
    //getters
    bool getStudentRecordCreated() const;
    bool getProgressToNextStage() const;
    bool getProgressToNextYear() const;
    //setters
    void setStudentRecordCreated(bool providedStudentRecordCreated);
    void setProgressToNextStage(bool providedProgresstoNextStage);
    void setProgressToNextYear(bool providedProgresstoNextYear);
    //debugging
    void display() const override;
};

#endif // PROGRESSIONCODE_H


#ifndef EXAMBOARD_H
#define EXAMBOARD_H
#include <pqxx/pqxx>
#include <iostream>
#include "assessment.h"
#include "assessmentattempt.h"
#include "student.h"
#include <algorithm>
#include "nec.h"
#include "misconduct.h"
#include "module.h"

class examBoard
{
private:
    std::vector<Assessment> assessments;
    std::vector<Student> students;
    std::vector<Module> modules;
public:
    examBoard();
    std::vector<Assessment> retrieveAssessments();
    std::vector<Student> retrieveStudents();
    std::vector<Module> retrieveModules();
    const Assessment& retrieveAssessmentByID(std::string providedID);
    std::vector<AssessmentAttempt> retrieveAssessmentAttemptsForStudent(std::string studentNumber);
};

#endif // EXAMBOARD_H

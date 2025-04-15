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
#include "moduleattempt.h"
#include "stage.h"
#include "stageattempt.h"
#include "course.h"
#include"courseattempt.h"
#include "nec.h"
#include "studentrecord.h"
class examBoard
{
private:
    std::vector<Assessment> assessments;
    std::vector<Student> students;
    std::vector<Module> modules;
    std::vector<Stage> stages;
    std::vector<Course> courses;
    std::vector<AssessmentAttempt> assessmentAttempts;
    std::vector<AssessmentAttempt> allAssessmentAttempts;
    std::vector<NEC> nec;
    std::vector<StudentRecord> studentRecords;
public:
    examBoard();
    void preLoadInfoData();
    std::vector<StudentRecord> loadStudentRecords();
    std::vector<NEC> retrieveNec();
    const NEC* retrieveNecForStudent(std::string referenceNumber);
    std::vector<Assessment> retrieveAssessments();
    std::vector<Student> retrieveStudents();
    std::vector<Module> retrieveModules();
    std::vector<Module> retrieveSpecificForStageModules(std::string stageId);
    std::vector<Stage> retrieveSpecificForCourseStages(std::string courseCode);
    std::vector<Stage> retrieveStages();
    std::vector<Course> retrieveCourses();
    const Assessment& retrieveAssessmentByID(std::string providedID);
    const Stage& retrieveStageByID(std::string providedID);
    const Course& retrieveCourseByID(std::string providedID);
    const Module& retrieveModuleByCode(std::string providedCode);
    std::string retrieveModuleType(std::string studentNumber, std::string moduleCode);
    std::vector<AssessmentAttempt> retrieveAssessmentAttemptsForStudent(std::string studentNumber);
    std::vector<std::shared_ptr<AssessmentAttempt>> retrieveAssessmentAttemptsForStudentForSpecificMpdule(std::string studentNumber, std::string code);
    AssessmentWeightsMap retrieveAssessmentWeightsForModule(const std::string moduleCode, const std::string year);
    std::vector<ModuleAttempt> retrieveModuleAttemptsForStudent(std::string studentNumber);
    std::shared_ptr<const Assessment> retrieveAssessmentPointerByID(std::string providedID) ;
    Assessment retrieveAssessmentObjectById(std::string providedID) ;
    std::vector<StageAttempt> retrieveStageAttemptsForStudent(std::string studentNumber);
    std::vector<std::shared_ptr<ModuleAttempt>> retrieveModuleAttemptsForStudentForSpecificStage(std::string studentNumber, std::string stageId);
    CourseAttempt* retrieveStudentCourseAttept(std::string studentNumber);

};
#endif // EXAMBOARD_H

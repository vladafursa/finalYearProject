#ifndef STUDENTRECORD_H
#define STUDENTRECORD_H
#include "student.h"
#include "courseattempt.h"

class StudentRecord
{
private:
    const Student& student;
    CourseAttempt* courseAttempt;
public:
    StudentRecord(const Student& providedStudent, CourseAttempt* providedCourseAttempt)
        : student(providedStudent), courseAttempt(providedCourseAttempt) {}
    const Student& getStudent() const { return student; }
    CourseAttempt* getCourseAttempt() const { return courseAttempt; }
    void prepareData() const {
        const std::vector<std::shared_ptr<StageAttempt>>& stageAttempts =courseAttempt->getAttempts();
        for(const auto& stage: stageAttempts){
            stage->setTypes();
            const std::vector<std::shared_ptr<ModuleAttempt>>& moduleAttempts =stage->getAttempts();
            for(const auto & module: moduleAttempts){
                module->assignTypes();
                const std::vector<std::shared_ptr<AssessmentAttempt>>& assessmentAttempts =module->getAttempts();
                for(const auto& assessment: assessmentAttempts){
                    assessment->getGrade();
                    assessment->populatePossibleDecisions();
                }
                module->transferMisconduct();
                module->calculateAggregate();
                module->getGrade();
                module->generateCode();
            }
            stage->determinCompensationPass();
            stage->generateCode();
            stage->applyMisconducts();
            stage->applyCompensation();
            stage->calculateAggregate();
        }
        courseAttempt->calculateProgression();
        courseAttempt->calculateAggregate();
        courseAttempt->generateCode();
    }


};


#endif // STUDENTRECORD_H

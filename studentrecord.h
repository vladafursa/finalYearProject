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
};


#endif // STUDENTRECORD_H

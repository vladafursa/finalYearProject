#ifndef STUDENT_H
#define STUDENT_H
#include <string>
using namespace std;

class Student
{
private:
    std::string studentNumber;
    std::string name;
    std::string course;
    bool fullyEnrolled;
    std::string dateEnrolled;
    bool T4;
    bool international;
public:
    //constructor
    Student(std::string providedStudentNumber, std::string providedName, std::string providedCourse, bool providedEnrolled, std::string providedEnrollmentDate, bool providedT4Status, bool providedInternationalStatus);
    //getters
    std::string getStudentNumber() const;
    std::string getName() const;
    std::string getCourse() const;
    bool isFullyEnrolled() const;
    std::string getDateEnrolled() const;
    bool isT4() const;
    bool isInternational() const;


    //setters
    void setStudentNumber(std::string providedStudentNumber);
    void setName(std::string providedName);
    void setCourse(std::string providedCourse);
    void setFullyEnrolled(bool providedEnrolled);
    void setDateEnrolled(std::string providedEnrollmentDate);
    void setT4(bool providedT4Status);
    void setInternational(bool providedInternationalStatus);
};

#endif // STUDENT_H

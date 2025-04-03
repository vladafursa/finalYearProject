#include <iostream>
#include "assessment.h"
#include "assessmentattempt.h"
#include "module.h"
#include "moduleattempt.h"
using namespace std;

int main()
{
    Assessment coursework("1","coursework","coding classes");
    Assessment exam("2", "exam", "check knowledge about classes");
    AssessmentAttempt attemptCoursework("T1", coursework, 1, "original", false, 3);
    AssessmentAttempt attemptRepeatCoursework("T1", coursework, 2, "original", false, 12);
    AssessmentAttempt attemptExam("T1", exam, 1, "original", false, 10);
    AssessmentWeightsMap assessments;

    assessments.emplace(std::ref(coursework), 60);
    assessments.emplace(std::ref(exam), 40);
    Module module1("1111", "some module", "202425", "core", 20, assessments);
    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(attemptCoursework);
    attempts.push_back(attemptRepeatCoursework);
    attempts.push_back(attemptExam);
    ModuleAttempt attempt1("T1", module1, 1, "original", attempts);
    std::vector<std::reference_wrapper<AssessmentAttempt>> finalAttempts = attempt1.getFinalattempts();
    for (const auto& attempt : finalAttempts) {
        std::cout << "Attempt details: " << attempt.get().getAssessment().getName()<<" "<< attempt.get().getNumberOfAttempt()<< " "
                  <<attempt.get().getGrade()<<std::endl;

    }
    double result = attempt1.calculateAggregate();
    std::cout<<"outcome: "<<result<<std::endl;
    attempt1.generateCode();
    std::cout<<attempt1.getFinalCode()->getCode();
    return 0;
}

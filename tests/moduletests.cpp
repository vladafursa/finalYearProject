#include <boost/test/unit_test.hpp>
#include "../assessment.h"
#include <iostream>
#include "../assessment.h"
#include "../assessmentattempt.h"
#include "../misconduct.h"
#include <unordered_map>
#include "../StdExtension.h"
#include <functional>
#include "../module.h"
#include "../moduleattempt.h"

using namespace std;
#include <vector>

//defining courseworks and exams
const Assessment cwk1("11","coursework","coding tax system");
const Assessment cwk2("12","coursework","refactoring tax system");
const Assessment cwk3("13","coursework","evalating tax system program");

const Assessment ex1("21", "exam", "check knowledge about OOP");
const Assessment ex2("22", "exam", "check knowledge about SQL");
const Assessment ex3("23", "exam", "check knowledge about cloud computing");


//misconducts
const Misconduct m1("1", "T1", "serious", "3LOW");

//defining assessment attempts
AssessmentAttempt normalAttemptCoursework("T1", cwk1, 1, "original", false, 10);
AssessmentAttempt failAttemptCoursework("T1", cwk2, 1, "original", false, 2);
AssessmentAttempt repeatAttemptCoursework("T1", cwk2, 2, "original", false, 12);
AssessmentAttempt attemptExam("T1", ex1, 1, "original", false, 3);
AssessmentAttempt failAttemptExam("T1", ex1, 2, "original", false, 8);
AssessmentAttempt attemptMisconductCoursework("T1", cwk3, 1, "original", false, 3, nullptr, nullptr, &m1);


BOOST_AUTO_TEST_SUITE( moduleTests )


//testing populating map
BOOST_AUTO_TEST_CASE(assessmentWeightsMapTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk1), 60);
    assessmentList1.emplace(std::ref(ex1), 40);

    BOOST_CHECK_EQUAL(assessmentList1.size(), 2);
}

//testing getting only final attempts
BOOST_AUTO_TEST_CASE(allFirstTryTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk1), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);
    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(normalAttemptCoursework);
    attempts.push_back(attemptExam);
    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);

    int expectedResult = 2;
    int actualResult = moduleAttempt1.getFinalattempts().size();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(oneFailAttemptTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk2), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);
    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(failAttemptCoursework);
    attempts.push_back(repeatAttemptCoursework);
    attempts.push_back(attemptExam);
    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);

    int expectedResult = 2;
    int actualResult = moduleAttempt1.getFinalattempts().size();

    BOOST_CHECK_EQUAL(actualResult, expectedResult);
}

//check which attempt was added
BOOST_AUTO_TEST_CASE(checkWhichAddedOneFailTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk2), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(failAttemptCoursework));
    attempts.push_back(std::ref(repeatAttemptCoursework));
    attempts.push_back(std::ref(attemptExam));
    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);

    bool found = false;
    for (const auto& attempt : moduleAttempt1.getFinalattempts()) {
        if (attempt.get().getAssessment().getName() == repeatAttemptCoursework.getAssessment().getName() &&
            attempt.get().getNumberOfAttempt() == repeatAttemptCoursework.getNumberOfAttempt()) {
            found = true;
            break;
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(checkWhichAddedALlFailTest) {
    AssessmentWeightsMap assessmentList1;
    assessmentList1.emplace(std::ref(cwk2), 60);
    assessmentList1.emplace(std::ref(ex1), 40);
    Module mod1("1111", "some module", "202425", "core", 20, assessmentList1);

    std::vector<std::reference_wrapper<AssessmentAttempt>> attempts;
    attempts.push_back(std::ref(failAttemptCoursework));
    attempts.push_back(std::ref(repeatAttemptCoursework));
    attempts.push_back(std::ref(attemptExam));
    attempts.push_back(std::ref(failAttemptExam));
    ModuleAttempt moduleAttempt1("T1", mod1, 1, "original", attempts);

    bool found = false;
    for (const auto& attempt : moduleAttempt1.getFinalattempts()) {
        if (attempt.get().getAssessment().getName() == repeatAttemptCoursework.getAssessment().getName() &&
            attempt.get().getNumberOfAttempt() == repeatAttemptCoursework.getNumberOfAttempt()) {
            found = true;
            break;
        }
    }
    BOOST_CHECK(found);
}


//check aggregates


BOOST_AUTO_TEST_SUITE_END()
/*

#include <iostream>
#include "assessment.h"
#include "assessmentattempt.h"
#include "module.h"
#include "moduleattempt.h"
#include "misconduct.h"
using namespace std;

int main()
{


    double result = attempt1.calculateAggregate();
    attempt1.getGrade();
    std::cout<<"result: "<<result<<std::endl;
    std::cout<<"outcome: "<<attempt1.checkAllElementsPassed()<<std::endl;
    std::cout<< "special outcome: "<<attempt1.determinSpecialPass()<<std::endl;
    attempt1.generateCode();
    std::cout<<"code: "<<attempt1.getFinalCode()->getCode();
    std::cout<<attempt1.getHadMisconduct();
assessmentList1.emplace(std::ref(cwk1), 60);
assessmentList1.emplace(std::ref(ex1), 40);
const Module module1("1111", "AI", "202425", "core", 20, assessmentList1);

*/

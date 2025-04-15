#include <boost/test/unit_test.hpp>
#include <functional>
#include "../assessment.h"
#include "../assessmentattempt.h"
using namespace std;
#include <vector>

//defining courseworks and exams
const Assessment cwk1("11","coursework","coding tax system");
const Assessment ex1("21", "exam", "check knowledge about OOP");


//misconducts
const Misconduct m1("1", "T1", "usual", "the assessment is capped at low 3");
const Misconduct m2("1", "T1", "usual", "the assessment is capped at zero");

//nec
const NEC nextOpportunityUpheldNEC("N1", "T1", true, "next opportunity");
const NEC nextOpportunityNotUpheldNEC("N1", "T1", true, "next opportunity");
const NEC weekUpheldNEC("N1", "T1", true, "1 week");
BOOST_AUTO_TEST_SUITE( assessmentTests )


//misconduct tests

//grade grade changes
//check that grade is not changed when there is no misconducts
BOOST_AUTO_TEST_CASE(noMisconductGradeTest) {

    AssessmentAttempt noMisconductAttempt("T1", cwk1, 1, false, 16);
    noMisconductAttempt.getGrade();
    noMisconductAttempt.applyMisconduct();

    std::string actualResult = noMisconductAttempt.getGrade();
    std::string expectedResult = "1EXC";

    BOOST_CHECK_EQUAL( actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(capAtLow3MisconductGradeTest) {

    AssessmentAttempt capAtLow3MisconductAttempt("T1", cwk1, 1, false, 16, nullptr, nullptr, &m1, nullptr);
    capAtLow3MisconductAttempt.getGrade();
    capAtLow3MisconductAttempt.applyMisconduct();

    std::string actualResultCode = capAtLow3MisconductAttempt.getGrade();
    std::string expectedResultCode = "3LOW";

    int actualResultPoints = capAtLow3MisconductAttempt.getGradePoints();
    int expectedResultPoints = 4;

    BOOST_CHECK_EQUAL( actualResultCode, expectedResultCode);
    BOOST_CHECK_EQUAL( actualResultPoints, expectedResultPoints);
}

BOOST_AUTO_TEST_CASE(capAtZeroMisconductGradeTest) {

    AssessmentAttempt capAtZeroMisconductAttempt("T1", cwk1, 1, false, 16, nullptr, nullptr, &m2, nullptr);
    capAtZeroMisconductAttempt.getGrade();
    capAtZeroMisconductAttempt.applyMisconduct();

    std::string actualResultCode = capAtZeroMisconductAttempt.getGrade();
    std::string expectedResultCode  = "ZERO";

    int actualResultPoints = capAtZeroMisconductAttempt.getGradePoints();
    int expectedResultPoints = 0;

    BOOST_CHECK_EQUAL( actualResultCode, expectedResultCode);
    BOOST_CHECK_EQUAL( actualResultPoints, expectedResultPoints);
}

//code changes tests
BOOST_AUTO_TEST_CASE(noMisconductCodeTest) {

    AssessmentAttempt noMisconductAttempt("T1", cwk1, 1, false, 16);
    noMisconductAttempt.getGrade();
    noMisconductAttempt.applyMisconduct();

    std::string actualResult = noMisconductAttempt.getFinalCode()->getCode();
    std::string expectedResult = "";

    BOOST_CHECK_EQUAL( actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(capAtLow3MisconductPassTest) {

    AssessmentAttempt capAtLow3MisconductPassAttempt("T1", cwk1, 1, false, 16, nullptr, nullptr, &m1, nullptr);
    capAtLow3MisconductPassAttempt.getGrade();
    capAtLow3MisconductPassAttempt.applyMisconduct();

    std::string actualResult = capAtLow3MisconductPassAttempt.getFinalCode()->getCode();
    std::string expectedResult = "PB";

    BOOST_CHECK_EQUAL( actualResult, expectedResult);
}

//is it like this???
BOOST_AUTO_TEST_CASE(capAtLow3MisconductNotPassTest) {

    AssessmentAttempt capAtLow3MisconductNotPassAttempt("T1", cwk1, 1, false, 3, nullptr, nullptr, &m1, nullptr);
    capAtLow3MisconductNotPassAttempt.getGrade();
    capAtLow3MisconductNotPassAttempt.applyMisconduct();

    std::string actualResult = capAtLow3MisconductNotPassAttempt.getFinalCode()->getCode();
    std::string expectedResult = "FC";

    BOOST_CHECK_EQUAL( actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(capAtZeroMisconductPassTest) {

    AssessmentAttempt capAtZeroMisconductPassAttempt("T1", cwk1, 1, false, 16, nullptr, nullptr, &m2, nullptr);
    capAtZeroMisconductPassAttempt.getGrade();
    capAtZeroMisconductPassAttempt.applyMisconduct();

    std::string actualResult = capAtZeroMisconductPassAttempt.getFinalCode()->getCode();
    std::string expectedResult = "PJ";

    BOOST_CHECK_EQUAL( actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(capAtZeroMisconductNotPassTest) {

    AssessmentAttempt capAtZeroMisconductNotPassAttempt("T1", cwk1, 1, false, 2, nullptr, nullptr, &m2, nullptr);
    capAtZeroMisconductNotPassAttempt.getGrade();
    capAtZeroMisconductNotPassAttempt.applyMisconduct();

    std::string actualResult = capAtZeroMisconductNotPassAttempt.getFinalCode()->getCode();
    std::string expectedResult = "FC";

    BOOST_CHECK_EQUAL( actualResult, expectedResult);
}

//type tests
BOOST_AUTO_TEST_CASE(originalTypeTest) {
    AssessmentAttempt firstTimeAttempt("T1", cwk1, 1, false, 10, nullptr, nullptr, nullptr, nullptr);

    std::string actualResult = firstTimeAttempt.getType();
    std::string expectedResult = "original";

    BOOST_CHECK_EQUAL( actualResult, expectedResult);
}


BOOST_AUTO_TEST_CASE(nextOpportunityUpheldTest) {
    AssessmentAttempt nextOpportunityUpheldAttempt("T1", cwk1, 1, false, 0, &AssessmentCodes::NN, &nextOpportunityUpheldNEC, nullptr, nullptr);

    nextOpportunityUpheldAttempt.populatePossibleDecisions();

    std::string actualResult = nextOpportunityUpheldAttempt.getFinalCode()->getCode();
    std::string expectedResult = "1S";

    BOOST_CHECK_EQUAL( actualResult, expectedResult);

    const std::vector<const AssessmentCode*>& posibleCodes = nextOpportunityUpheldAttempt.getPossibleCodes();
    BOOST_CHECK_EQUAL(posibleCodes.size(), 3);

    BOOST_CHECK_EQUAL( posibleCodes[0]->getCode(), "1A");
    BOOST_CHECK_EQUAL( posibleCodes[1]->getCode(), "1N");
    BOOST_CHECK_EQUAL( posibleCodes[2]->getCode(), "1O");

}



BOOST_AUTO_TEST_CASE(submittedLateButPassTest) {
    AssessmentAttempt lateSubmissionPassAttempt("T1", cwk1, 1, true, 14);
    lateSubmissionPassAttempt.getGrade();
    lateSubmissionPassAttempt.populatePossibleDecisions();

    std::string actualResult = lateSubmissionPassAttempt.getFinalCode()->getCode();
    std::string expectedResult = "PL";

    BOOST_CHECK_EQUAL( actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(passReferralTest) {
    AssessmentAttempt passReferralAttempt("T1", cwk1, 2, true, 14);
    passReferralAttempt.getGrade();
    passReferralAttempt.setType("referral");
    passReferralAttempt.populatePossibleDecisions();

    std::string actualResult = passReferralAttempt.getFinalCode()->getCode();
    std::string expectedResult = "PR";

    BOOST_CHECK_EQUAL( actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(failReferralTest) {
    AssessmentAttempt failReferralAttempt("T1", cwk1, 2, false, 0, nullptr, &weekUpheldNEC, nullptr, nullptr);
    failReferralAttempt.getGrade();
    failReferralAttempt.setType("referral");
    failReferralAttempt.populatePossibleDecisions();

    std::string actualResult = failReferralAttempt.getFinalCode()->getCode();
    std::string expectedResult = "FE";

    BOOST_CHECK_EQUAL( actualResult, expectedResult);
}


BOOST_AUTO_TEST_CASE(passRepeatTest) {
    AssessmentAttempt passRepeatAttempt("T1", cwk1, 2, true, 14);
    passRepeatAttempt.getGrade();
    passRepeatAttempt.setType("repeat");
    passRepeatAttempt.populatePossibleDecisions();

    std::string actualResult = passRepeatAttempt.getFinalCode()->getCode();
    std::string expectedResult = "PY";

    BOOST_CHECK_EQUAL( actualResult, expectedResult);
}

BOOST_AUTO_TEST_CASE(failRepeatTest) {
    AssessmentAttempt failRepeatAttempt("T1", cwk1, 2, false, 0, nullptr, nullptr, nullptr, nullptr);
    failRepeatAttempt.getGrade();
    failRepeatAttempt.populatePossibleDecisions();

    std::string actualResult = failRepeatAttempt.getFinalCode()->getCode();
    std::string expectedResult = "FN";

    BOOST_CHECK_EQUAL( actualResult, expectedResult);
}

BOOST_AUTO_TEST_SUITE_END()


#include <boost/test/unit_test.hpp>
#include "../grades.h"
#include <string>
#include <iostream>

//defining variable
Grades gradeSystem;
const std::string threshold = "3LOW";
const double percentageAccuracy =0.1;

BOOST_AUTO_TEST_SUITE( roundGradePointTests )

//typical input
BOOST_AUTO_TEST_CASE( typicalInputTest )
{
    double gradePoint = 12.67;
    double expectedRounding = 12.7;

    double realRounding = gradeSystem.round(gradePoint);
    BOOST_CHECK_CLOSE( realRounding, expectedRounding, percentageAccuracy );
}

//no rounding needed
BOOST_AUTO_TEST_CASE( integerTest )
{
    double gradePoint = 14;
    double expectedRounding = 14;

    double realRounding = gradeSystem.round(gradePoint);

    BOOST_CHECK_CLOSE( realRounding, expectedRounding, percentageAccuracy );
}


//boundaries
BOOST_AUTO_TEST_CASE( closeMiddleTest )
{
    double gradePoint = 14.45;
    double expectedRounding = 14.5;

    double realRounding = gradeSystem.round(gradePoint);

    BOOST_CHECK_CLOSE( realRounding, expectedRounding, percentageAccuracy );
}

BOOST_AUTO_TEST_CASE( closeDownTest )
{
    double gradePoint = 14.41;
    double expectedRounding = 14.4;

    double realRounding = gradeSystem.round(gradePoint);

    BOOST_CHECK_CLOSE( realRounding, expectedRounding, percentageAccuracy );
}

BOOST_AUTO_TEST_CASE( closeUpperTest )
{
    double gradePoint = 14.499;
    double expectedRounding = 14.5;

    double realRounding = gradeSystem.round(gradePoint);

    BOOST_CHECK_CLOSE( realRounding, expectedRounding, percentageAccuracy );
}

//edge cases
BOOST_AUTO_TEST_CASE( unusualUpperTest )
{
    double gradePoint = 14.449;
    double expectedRounding = 14.5;

    double realRounding = gradeSystem.round(gradePoint);

    BOOST_CHECK_CLOSE( realRounding, expectedRounding, percentageAccuracy );
}

BOOST_AUTO_TEST_CASE( unusualDownTest )
{
    double gradePoint = 14.444;
    double expectedRounding = 14.4;

    double realRounding = gradeSystem.round(gradePoint);

    BOOST_CHECK_CLOSE( realRounding, expectedRounding, percentageAccuracy );
}

//no rounding needed
BOOST_AUTO_TEST_CASE( noRoundingNeededTest )
{
    double gradePoint = 14.4;
    double expectedRounding = 14.4;

    double realRounding = gradeSystem.round(gradePoint);

    BOOST_CHECK_CLOSE( realRounding, expectedRounding, percentageAccuracy );
}

//borders
BOOST_AUTO_TEST_CASE( zeroTest )
{
    double gradePoint = 0;
    double expectedRounding = 0;

    double realRounding = gradeSystem.round(gradePoint);

    BOOST_CHECK_CLOSE( realRounding, expectedRounding, percentageAccuracy );
}


BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE( checkIfGradeWasCorrectlyAssignedTests )

BOOST_AUTO_TEST_CASE( normalGradeTest )
{
    double intGrade = 14.7;
    std::string expectedResult = "1HIGH";

    std::string actualResult =  gradeSystem.assignGrade(intGrade);

    BOOST_CHECK_EQUAL(expectedResult, actualResult);
}

//boarder tests
BOOST_AUTO_TEST_CASE( upperBorderGradeTest )
{
    double intGrade = 14.6;
    std::string expectedResult = "1HIGH";

    std::string actualResult =  gradeSystem.assignGrade(intGrade);

    BOOST_CHECK_EQUAL(expectedResult, actualResult);
}

BOOST_AUTO_TEST_CASE( lowerBorderGradeTest )
{
    double intGrade = 14.4;
    std::string expectedResult = "1MID";

    std::string actualResult =  gradeSystem.assignGrade(intGrade);

    BOOST_CHECK_EQUAL(expectedResult, actualResult);
}

BOOST_AUTO_TEST_CASE( onBorderGradeTest )
{
    double intGrade = 14.5;
    std::string expectedResult = "1HIGH";

    std::string actualResult =  gradeSystem.assignGrade(intGrade);

    BOOST_CHECK_EQUAL(expectedResult, actualResult);
}

//testing extremes
BOOST_AUTO_TEST_CASE( maxGradeTest )
{
    double intGrade = 16;
    std::string expectedResult = "1EXC";

    std::string actualResult =  gradeSystem.assignGrade(intGrade);

    BOOST_CHECK_EQUAL(expectedResult, actualResult);
}

BOOST_AUTO_TEST_CASE( zeroGradeTest )
{
    double intGrade = 0;
    std::string expectedResult = "ZERO";

    std::string actualResult =  gradeSystem.assignGrade(intGrade);

    BOOST_CHECK_EQUAL(expectedResult, actualResult);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( checkComparisonWithThresholdTests )

//testing usual case
BOOST_AUTO_TEST_CASE( usualTest )
{
    std::string normalGrade = "21MID";
    bool expectedResult = true;

    bool actualResult = gradeSystem.isGreaterThanThreshold(normalGrade, threshold);


    BOOST_CHECK_EQUAL( actualResult, expectedResult );
}

//testing boundaries
BOOST_AUTO_TEST_CASE( thresholdTest )
{
    bool expectedResult = true;

    bool actualResult = gradeSystem.isGreaterThanThreshold(threshold, threshold);


    BOOST_CHECK_EQUAL( actualResult, expectedResult );
}

BOOST_AUTO_TEST_CASE( closeToThresholdTest )
{
    std::string closeGrade = "3MID";
    bool expectedResult = true;

    bool actualResult = gradeSystem.isGreaterThanThreshold(closeGrade, threshold);


    BOOST_CHECK_EQUAL( actualResult, expectedResult );
}

BOOST_AUTO_TEST_CASE( closeToThresholdDownTest )
{
    std::string closeGrade = "FMARG";
    bool expectedResult = false;

    bool actualResult = gradeSystem.isGreaterThanThreshold(closeGrade, threshold);


    BOOST_CHECK_EQUAL( actualResult, expectedResult );
}

//edge cases
BOOST_AUTO_TEST_CASE( zeroTest )
{
    std::string zeroGrade = "ZERO";
    bool expectedResult = false;

    bool actualResult = gradeSystem.isGreaterThanThreshold(zeroGrade, threshold);


    BOOST_CHECK_EQUAL( actualResult, expectedResult );
}

BOOST_AUTO_TEST_CASE( maxGradeTest )
{

    std::string highestGrade = "1EXC";
    bool expectedResult = true;

    bool actualResult = gradeSystem.isGreaterThanThreshold(highestGrade, threshold);


    BOOST_CHECK_EQUAL( actualResult, expectedResult );
}


BOOST_AUTO_TEST_SUITE_END()

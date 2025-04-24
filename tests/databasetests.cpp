#include <boost/test/unit_test.hpp>
#include <chrono>
#include "../examboard.h"
/*
BOOST_AUTO_TEST_CASE(student_record_loading_performance)
{
    using namespace std::chrono;

    examBoard board;

    auto start = high_resolution_clock::now();

    std::vector<StudentRecord> result = board.loadStudentRecords();

    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;

    BOOST_TEST_MESSAGE("Load time: " << elapsed.count() << " seconds");

    const double MAX_ALLOWED_TIME = 2.0; // ⏱️ Change this as needed

    BOOST_CHECK_MESSAGE(elapsed.count() < MAX_ALLOWED_TIME,
                        "Too slow! Took " << elapsed.count() << " seconds to load " << result.size() << " records.");
}
*/

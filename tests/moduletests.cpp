#include <boost/test/unit_test.hpp>
#include "../assessment.h"



BOOST_AUTO_TEST_SUITE( courseworkTests )


const Assessment coursework("1","code","CWK");

//testing extremes
BOOST_AUTO_TEST_CASE( test )
{
    std::string res = "1";
    std::string res1 = coursework.getId();
    BOOST_CHECK_EQUAL( res , res1 );
}

BOOST_AUTO_TEST_SUITE_END()

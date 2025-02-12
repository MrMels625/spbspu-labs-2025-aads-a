#include <boost/test/unit_test.hpp>
#include <sstream>
#include "credentials.hpp"

BOOST_AUTO_TEST_CASE(credential_test)
{
  std::ostringstream out;
  brevnov::out_credentials(out);
  BOOST_TEST(out.str() == "brevnov.nikita");
}

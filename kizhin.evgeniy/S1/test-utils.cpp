#include "test-utils.hpp"

void kizhin::testInvariants(const ListT& list)
{
  BOOST_TEST(list.empty() == (list.size() == 0));
  BOOST_TEST(list.empty() == (list.begin() == list.end()));
  BOOST_TEST(std::distance(list.begin(), list.end()) == list.size());
  if (list.empty()) {
    return;
  }
  const ListT::const_iterator beforeEnd = std::next(list.begin(), list.size() - 1);
  BOOST_TEST(std::addressof(list.front()) == std::addressof(*list.begin()));
  BOOST_TEST(std::addressof(list.back()) == std::addressof(*beforeEnd));
}


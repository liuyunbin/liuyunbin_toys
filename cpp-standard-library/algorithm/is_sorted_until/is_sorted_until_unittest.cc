
#include "is_sorted_until.h"

#include <algorithm>
#include <cctype>
#include <forward_list>
#include <list>
#include <numeric>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_is_sorted_until) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    auto x =
        std::is_sorted_until(forward_list_1.cbegin(), forward_list_1.cend());
    auto y = liuyunbin::is_sorted_until(forward_list_1.cbegin(),
                                        forward_list_1.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
    auto x =
        std::is_sorted_until(forward_list_1.cbegin(), forward_list_1.cend());
    auto y = liuyunbin::is_sorted_until(forward_list_1.cbegin(),
                                        forward_list_1.cend());
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    auto x = std::is_sorted_until(list_1.cbegin(), list_1.cend());
    auto y = liuyunbin::is_sorted_until(list_1.cbegin(), list_1.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};
    auto x = std::is_sorted_until(list_1.cbegin(), list_1.cend());
    auto y = liuyunbin::is_sorted_until(list_1.cbegin(), list_1.cend());
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    auto x = std::is_sorted_until(vector_1.cbegin(), vector_1.cend());
    auto y = liuyunbin::is_sorted_until(vector_1.cbegin(), vector_1.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};
    auto x = std::is_sorted_until(vector_1.cbegin(), vector_1.cend());
    auto y = liuyunbin::is_sorted_until(vector_1.cbegin(), vector_1.cend());
    EXPECT_EQ(x, y);
  }
}

// Copyright (C) 2025 Albin Johansson

#include <limits>
#include <optional>

#include <gtest/gtest.h>
#include <safely/ops/rem.hpp>

#include "common/types.hpp"

namespace safely::tests {
namespace {

using detail::add_unchecked;

template <typename T>
class RemTest : public testing::Test
{};

TYPED_TEST_SUITE(RemTest, IntegerTypes, );

TYPED_TEST(RemTest, Rem)
{
  using T = TypeParam;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // Division by zero
  EXPECT_EQ(rem(T {0}, T {0}), std::nullopt);
  EXPECT_EQ(rem(T {1}, T {0}), std::nullopt);
  EXPECT_EQ(rem(t_min, T {0}), std::nullopt);
  EXPECT_EQ(rem(t_max, T {0}), std::nullopt);

  // 1 % 1 = 0
  EXPECT_EQ(rem(T {1}, T {1}), T {0});

  // 2 % 1 = 0
  EXPECT_EQ(rem(T {2}, T {1}), T {0});

  // 100 % 4 = 0
  EXPECT_EQ(rem(T {100}, T {4}), T {0});

  // 7 % 2 = 1
  EXPECT_EQ(rem(T {7}, T {2}), T {1});

  // 1 % 2 = 1
  EXPECT_EQ(rem(T {1}, T {2}), T {1});

  // 8 % 3 = 2
  EXPECT_EQ(rem(T {8}, T {3}), T {2});

  // MAX % MAX = 0
  EXPECT_EQ(rem(t_max, t_max), T {0});
}

template <typename T>
class RemSignedTest : public testing::Test
{};

TYPED_TEST_SUITE(RemSignedTest, SignedIntegerTypes, );

TYPED_TEST(RemSignedTest, Rem)
{
  using T = TypeParam;
  constexpr auto t_min = std::numeric_limits<T>::min();

  // MIN % -1 => OVERFLOW
  EXPECT_EQ(rem(t_min, T {-1}), std::nullopt);

  // MIN % MIN = 0
  EXPECT_EQ(rem(t_min, t_min), T {0});
}

}  // namespace
}  // namespace safely::tests

// Copyright (C) 2025 Albin Johansson

#include <limits>

#include <gtest/gtest.h>
#include <safely/ops/add.hpp>

#include "common/types.hpp"

namespace safely::tests {
namespace {

template <typename T>
class AddTest : public testing::Test
{};

TYPED_TEST_SUITE(AddTest, IntegerTypes);

TYPED_TEST(AddTest, OK)
{
  using T = TypeParam;
  constexpr auto t_min = Limits<T>::min();
  constexpr auto t_max = Limits<T>::max();

  T sum {};

  // 0 + 0 = 0
  ASSERT_EQ(add(T {0}, T {0}, sum), errc::ok);
  EXPECT_EQ(sum, T {0});

  // 0 + 1 = 1
  ASSERT_EQ(add(T {0}, T {1}, sum), errc::ok);
  EXPECT_EQ(sum, T {1});

  // 1 + 2 = 3
  ASSERT_EQ(add(T {1}, T {2}, sum), errc::ok);
  EXPECT_EQ(sum, T {3});

  // (MAX - 1) + 1 = MAX
  ASSERT_EQ(add(static_cast<T>(t_max - T {1}), T {1}, sum), errc::ok);
  EXPECT_EQ(sum, t_max);

  // MAX + 0 = MAX
  ASSERT_EQ(add(t_max, T {0}, sum), errc::ok);
  EXPECT_EQ(sum, t_max);

  // MIN + 0 = MIN
  ASSERT_EQ(add(t_min, T {0}, sum), errc::ok);
  EXPECT_EQ(sum, t_min);
}

TYPED_TEST(AddTest, Overflow)
{
  using T = TypeParam;
  constexpr auto t_max = Limits<T>::max();

  T sum {};

  // MAX + 1 => OVERFLOW
  EXPECT_EQ(add(t_max, T {1}, sum), errc::overflow);

  // 1 + MAX => OVERFLOW
  EXPECT_EQ(add(T {1}, t_max, sum), errc::overflow);

  // MAX + MAX => OVERFLOW
  EXPECT_EQ(add(t_max, t_max, sum), errc::overflow);
}

template <typename T>
class AddSignedTest : public testing::Test
{};

TYPED_TEST_SUITE(AddSignedTest, SignedIntegerTypes);

TYPED_TEST(AddSignedTest, OK)
{
  using T = TypeParam;
  constexpr auto t_min = Limits<T>::min();
  constexpr auto t_max = Limits<T>::max();

  T sum {};

  // MIN + MAX = -1
  ASSERT_EQ(add(t_min, t_max, sum), errc::ok);
  EXPECT_EQ(sum, T {-1});
}

TYPED_TEST(AddSignedTest, Underflow)
{
  using T = TypeParam;
  constexpr auto t_min = Limits<T>::min();
  constexpr auto t_max = Limits<T>::max();

  T sum {};

  // MIN + -1 => OVERFLOW
  EXPECT_EQ(add(t_min, T {-1}, sum), errc::overflow);

  // -1 + MIN => OVERFLOW
  EXPECT_EQ(add(T {-1}, t_min, sum), errc::overflow);

  // MIN + MIN => OVERFLOW
  EXPECT_EQ(add(t_min, t_min, sum), errc::overflow);
}

}  // namespace
}  // namespace safely::tests

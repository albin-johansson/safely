// Copyright (C) 2025 Albin Johansson

#include <limits>

#include <gtest/gtest.h>
#include <safely/ops/add.hpp>

#include "common/types.hpp"

namespace safely::tests {
namespace {

template <typename T>
class AddSatTest : public testing::Test
{};

TYPED_TEST_SUITE(AddSatTest, IntegerTypes);

TYPED_TEST(AddSatTest, AddSat)
{
  using T = TypeParam;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // 0 + 0 = 0
  EXPECT_EQ(add_sat(T {0}, T {0}), T {0});

  // 0 + 1 = 1
  EXPECT_EQ(add_sat(T {0}, T {1}), T {1});

  // 1 + 2 = 3
  EXPECT_EQ(add_sat(T {1}, T {2}), T {3});

  // (MAX - 1) + 1 = MAX
  EXPECT_EQ(add_sat(static_cast<T>(t_max - T {1}), T {1}), t_max);

  // MAX + 0 = MAX
  EXPECT_EQ(add_sat(t_max, T {0}), t_max);

  // MIN + 0 = MIN
  EXPECT_EQ(add_sat(t_min, T {0}), t_min);

  // MAX + 1 = MAX
  EXPECT_EQ(add_sat(t_max, T {1}), t_max);

  // MAX + 2 = MAX
  EXPECT_EQ(add_sat(t_max, T {2}), t_max);

  // 1 + MAX = MAX
  EXPECT_EQ(add_sat(T {1}, t_max), t_max);

  // MAX + MAX = MAX
  EXPECT_EQ(add_sat(t_max, t_max), t_max);
}

template <typename T>
class AddSatSignedTest : public testing::Test
{};

TYPED_TEST_SUITE(AddSatSignedTest, SignedIntegerTypes);

TYPED_TEST(AddSatSignedTest, AddSat)
{
  using T = TypeParam;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // -1 + 1 = 0
  EXPECT_EQ(add_sat(T {-1}, T {1}), T {0});

  // -1 + -2 = -3
  EXPECT_EQ(add_sat(T {-1}, T {-2}), T {-3});

  // -100 + 100 = 0
  EXPECT_EQ(add_sat(T {-100}, T {100}), T {0});

  // MIN + MAX = -1
  EXPECT_EQ(add_sat(t_min, t_max), T {-1});

  // MIN + -1 = MIN
  EXPECT_EQ(add_sat(t_min, T {-1}), t_min);

  // MIN + -2 = MIN
  EXPECT_EQ(add_sat(t_min, T {-2}), t_min);

  // -1 + MIN = MIN
  EXPECT_EQ(add_sat(T {-1}, t_min), t_min);

  // MIN + MIN = MIN
  EXPECT_EQ(add_sat(t_min, t_min), t_min);
}

}  // namespace
}  // namespace safely::tests

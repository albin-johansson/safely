// Copyright (C) 2025 Albin Johansson

#include <limits>

#include <gtest/gtest.h>
#include <safely/ops/mul.hpp>

#include "common/types.hpp"

namespace safely::tests {
namespace {

template <typename T>
class MulSat : public testing::Test
{};

TYPED_TEST_SUITE(MulSat, IntegerTypes, );

TYPED_TEST(MulSat, MulSat)
{
  using T = TypeParam;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // 1 * 0 = 0
  EXPECT_EQ(mul_sat(T {1}, T {0}), T {0});

  // 0 * 1 = 0
  EXPECT_EQ(mul_sat(T {0}, T {1}), T {0});

  // 1 * 2 = 2
  EXPECT_EQ(mul_sat(T {1}, T {2}), T {2});

  // 6 * 7 = 41
  EXPECT_EQ(mul_sat(T {6}, T {7}), T {42});

  // MIN * 1 = MIN
  EXPECT_EQ(mul_sat(t_min, T {1}), t_min);

  // MAX * 1 = MAX
  EXPECT_EQ(mul_sat(t_max, T {1}), t_max);

  // (MIN / 2) * 2 = MIN
  EXPECT_EQ(mul_sat(static_cast<T>(t_min / T {2}), T {2}), t_min);

  // (MAX / 2) * 2 = MAX - 1
  EXPECT_EQ(mul_sat(static_cast<T>(t_max / T {2}), T {2}),
            static_cast<T>(t_max - T {1}));

  // ((MAX / 2) + 1) * 2 = MAX <saturated>
  EXPECT_EQ(
      mul_sat(static_cast<T>(static_cast<T>(t_max / T {2}) + T {1}), T {2}),
      t_max);

  // MAX * 2 = MAX <saturated>
  EXPECT_EQ(mul_sat(t_max, T {2}), t_max);

  // MAX * MAX = MAX <saturated>
  EXPECT_EQ(mul_sat(t_max, t_max), t_max);
}

template <typename T>
class MulSatSignedTest : public testing::Test
{};

TYPED_TEST_SUITE(MulSatSignedTest, SignedIntegerTypes, );

TYPED_TEST(MulSatSignedTest, MulSat)
{
  using T = TypeParam;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // -1 * 2 = -2
  EXPECT_EQ(mul_sat(T {-1}, T {2}), T {-2});

  // -5 * -3 = 15
  EXPECT_EQ(mul_sat(T {-5}, T {-3}), T {15});

  // MAX * -1 = -MAX
  EXPECT_EQ(mul_sat(t_max, T {-1}), -t_max);

  // ((MIN / 2) - 1) * 2 = MIN <saturated>
  EXPECT_EQ(
      mul_sat(static_cast<T>(static_cast<T>(t_min / T {2}) - T {1}), T {2}),
      t_min);

  // -1 * MIN = MAX <saturated>
  EXPECT_EQ(mul_sat(T {-1}, t_min), t_max);

  // 2 * MIN = MIN <saturated>
  EXPECT_EQ(mul_sat(T {2}, t_min), t_min);

  // MIN * 2 = MIN <saturated>
  EXPECT_EQ(mul_sat(t_min, T {2}), t_min);

  // MIN * MAX = MIN <saturated>
  EXPECT_EQ(mul_sat(t_min, t_max), t_min);

  // MIN * MIN = MAX <saturated>
  EXPECT_EQ(mul_sat(t_min, t_min), t_max);
}

}  // namespace
}  // namespace safely::tests

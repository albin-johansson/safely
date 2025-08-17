// Copyright (C) 2025 Albin Johansson

#include <limits>

#include <gtest/gtest.h>
#include <safely/ops/sub.hpp>

#include "common/types.hpp"

namespace safely::tests {
namespace {

template <typename T>
class SubSatTest : public testing::Test
{};

TYPED_TEST_SUITE(SubSatTest, IntegerTypes, );

TYPED_TEST(SubSatTest, SubSat)
{
  using T = TypeParam;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // 0 - 0 = 0
  EXPECT_EQ(sub_sat(T {0}, T {0}), T {0});

  // 1 - 0 = 1
  EXPECT_EQ(sub_sat(T {1}, T {0}), T {1});

  // 3 - 2 = 1
  EXPECT_EQ(sub_sat(T {3}, T {2}), T {1});

  // MAX - 1 = (MAX - 1)
  EXPECT_EQ(sub_sat(t_max, T {1}), static_cast<T>(t_max - T {1}));

  // MIN - 0 = MIN
  EXPECT_EQ(sub_sat(t_min, T {0}), t_min);

  // MAX - 0 = MAX
  EXPECT_EQ(sub_sat(t_max, T {0}), t_max);

  // MIN - 1 = MIN <saturated>
  EXPECT_EQ(sub_sat(t_min, T {1}), t_min);

  // MIN - 2 = MIN <saturated>
  EXPECT_EQ(sub_sat(t_min, T {2}), t_min);

  // MIN - MAX = MIN <saturated>
  EXPECT_EQ(sub_sat(t_min, t_max), t_min);

  // MAX - MAX = 0
  EXPECT_EQ(sub_sat(t_max, t_max), T {0});
}

template <typename T>
class SubSatSignedTest : public SubSatTest<T>
{};

TYPED_TEST_SUITE(SubSatSignedTest, SignedIntegerTypes, );

TYPED_TEST(SubSatSignedTest, SubSat)
{
  using T = TypeParam;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // -1 - 0 = -1
  EXPECT_EQ(sub_sat(T {-1}, T {0}), T {-1});

  // -3 - (-2) = -1
  EXPECT_EQ(sub_sat(T {-3}, T {-2}), T {-1});

  // -100 - (-100) = 0
  EXPECT_EQ(sub_sat(T {-100}, T {-100}), T {0});

  // MIN - MIN = 0
  EXPECT_EQ(sub_sat(t_min, t_min), T {0});

  // MAX - (-1) = MAX <saturated>
  EXPECT_EQ(sub_sat(t_max, T {-1}), t_max);

  // MAX - (-2) = MAX <saturated>
  EXPECT_EQ(sub_sat(t_max, T {-2}), t_max);
}

}  // namespace
}  // namespace safely::tests

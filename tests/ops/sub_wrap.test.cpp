// Copyright (C) 2025 Albin Johansson

#include <limits>

#include <gtest/gtest.h>
#include <safely/ops/sub.hpp>

#include "common/types.hpp"

namespace safely::tests {
namespace {

template <typename T>
class SubWrapTest : public testing::Test
{};

TYPED_TEST_SUITE(SubWrapTest, IntegerTypes, );

TYPED_TEST(SubWrapTest, SubWrap)
{
  using T = TypeParam;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // 0 - 0 = 0
  EXPECT_EQ(sub_wrap(T {0}, T {0}), T {0});

  // 1 - 0 = 1
  EXPECT_EQ(sub_wrap(T {1}, T {0}), T {1});

  // 3 - 2 = 1
  EXPECT_EQ(sub_wrap(T {3}, T {2}), T {1});

  // MAX - 1 = (MAX - 1)
  EXPECT_EQ(sub_wrap(t_max, T {1}), static_cast<T>(t_max - T {1}));

  // MIN - 0 = MIN
  EXPECT_EQ(sub_wrap(t_min, T {0}), t_min);

  // MAX - 0 = MAX
  EXPECT_EQ(sub_wrap(t_max, T {0}), t_max);

  // MIN - 1 = MAX
  EXPECT_EQ(sub_wrap(t_min, T {1}), t_max);

  // MIN - 2 = MAX - 1
  EXPECT_EQ(sub_wrap(t_min, T {2}), static_cast<T>(t_max - T {1}));

  // MAX - MAX = 0
  EXPECT_EQ(sub_wrap(t_max, t_max), T {0});

  // MIN - MAX = 1
  EXPECT_EQ(sub_wrap(t_min, t_max), T {1});
}

template <typename T>
class SubWrapSignedTest : public SubWrapTest<T>
{};

TYPED_TEST_SUITE(SubWrapSignedTest, SignedIntegerTypes, );

TYPED_TEST(SubWrapSignedTest, SubWrap)
{
  using T = TypeParam;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // -1 - 0 = -1
  EXPECT_EQ(sub_wrap(T {-1}, T {0}), T {-1});

  // -3 - (-2) = -1
  EXPECT_EQ(sub_wrap(T {-3}, T {-2}), T {-1});

  // MIN - MIN = 0
  EXPECT_EQ(sub_wrap(t_min, t_min), T {0});

  // MAX - (-1) = MIN
  EXPECT_EQ(sub_wrap(t_max, T {-1}), t_min);

  // MAX - (-2) = MIN + 1
  EXPECT_EQ(sub_wrap(t_max, T {-2}), static_cast<T>(t_min + T {1}));
}

}  // namespace
}  // namespace safely::tests

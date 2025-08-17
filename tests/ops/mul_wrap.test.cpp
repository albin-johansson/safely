// Copyright (C) 2025 Albin Johansson

#include <limits>

#include <gtest/gtest.h>
#include <safely/ops/mul.hpp>

#include "common/types.hpp"

namespace safely::tests {
namespace {

template <typename T>
class MulWrapTest : public testing::Test
{};

TYPED_TEST_SUITE(MulWrapTest, IntegerTypes, );

TYPED_TEST(MulWrapTest, MulWrap)
{
  using T = TypeParam;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // 1 * 0 = 0
  EXPECT_EQ(mul_wrap(T {1}, T {0}), T {0});

  // 0 * 1 = 0
  EXPECT_EQ(mul_wrap(T {0}, T {1}), T {0});

  // 1 * 2 = 2
  EXPECT_EQ(mul_wrap(T {1}, T {2}), T {2});

  // 6 * 7 = 41
  EXPECT_EQ(mul_wrap(T {6}, T {7}), T {42});

  // MIN * 1 = MIN
  EXPECT_EQ(mul_wrap(t_min, T {1}), t_min);

  // MAX * 1 = MAX
  EXPECT_EQ(mul_wrap(t_max, T {1}), t_max);

  // (MIN / 2) * 2 = MIN
  EXPECT_EQ(mul_wrap(static_cast<T>(t_min / T {2}), T {2}), t_min);

  // (MAX / 2) * 2 = MAX - 1
  EXPECT_EQ(mul_wrap(static_cast<T>(t_max / T {2}), T {2}),
            static_cast<T>(t_max - T {1}));

  // ((MAX / 2) + 1) * 2 = MIN <wrapped>
  EXPECT_EQ(
      mul_wrap(static_cast<T>(static_cast<T>(t_max / T {2}) + T {1}), T {2}),
      t_min);

  // MAX * MAX = 1 <wrapped>
  EXPECT_EQ(mul_wrap(t_max, t_max), T {1});

  // MAX * 3 = MAX - 2 <wrapped>
  EXPECT_EQ(mul_wrap(t_max, T {3}), t_max - T {2});
}

template <typename T>
class MulWrapSignedTest : public testing::Test
{};

TYPED_TEST_SUITE(MulWrapSignedTest, SignedIntegerTypes, );

TYPED_TEST(MulWrapSignedTest, MulWrap)
{
  using T = TypeParam;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // -1 * 2 = -2
  EXPECT_EQ(mul_wrap(T {-1}, T {2}), T {-2});

  // -5 * -3 = 15
  EXPECT_EQ(mul_wrap(T {-5}, T {-3}), T {15});

  // MAX * -1 = -MAX
  EXPECT_EQ(mul_wrap(t_max, T {-1}), -t_max);

  // MIN * 2 = 0 <wrapped>
  EXPECT_EQ(mul_wrap(t_min, T {2}), T {0});

  // MAX * 2 = -2 <wrapped>
  EXPECT_EQ(mul_wrap(t_max, T {2}), T {-2});

  // MAX * 4 = -4 <wrapped>
  EXPECT_EQ(mul_wrap(t_max, T {4}), T {-4});

  // MIN * MIN = 0 <wrapped>
  EXPECT_EQ(mul_wrap(t_min, t_min), T {0});
}

template <typename T>
class MulWrapUnsignedTest : public testing::Test
{};

TYPED_TEST_SUITE(MulWrapUnsignedTest, UnsignedIntegerTypes, );

TYPED_TEST(MulWrapUnsignedTest, MulWrap)
{
  using T = TypeParam;
  constexpr auto t_max = std::numeric_limits<T>::max();

  // MAX * 2 = MAX - 1 <wrapped>
  EXPECT_EQ(mul_wrap(t_max, T {2}), t_max - T {1});

  // MAX * 4 = MAX - 3 <wrapped>
  EXPECT_EQ(mul_wrap(t_max, T {4}), t_max - T {3});
}

}  // namespace
}  // namespace safely::tests

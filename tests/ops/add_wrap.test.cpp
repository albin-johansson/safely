// Copyright (C) 2025 Albin Johansson

#include <limits>

#include <gtest/gtest.h>
#include <safely/ops/add.hpp>

#include "common/types.hpp"

namespace safely::tests {
namespace {

template <typename T>
class AddWrapTest : public testing::Test
{};

TYPED_TEST_SUITE(AddWrapTest, IntegerTypes, );

TYPED_TEST(AddWrapTest, AddWrap)
{
  using T = TypeParam;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // 0 + 0 = 0
  EXPECT_EQ(add_wrap(T {0}, T {0}), T {0});

  // 0 + 1 = 1
  EXPECT_EQ(add_wrap(T {0}, T {1}), T {1});

  // 1 + 2 = 3
  EXPECT_EQ(add_wrap(T {1}, T {2}), T {3});

  // (MAX - 1) + 1 = MAX
  EXPECT_EQ(add_wrap(static_cast<T>(t_max - T {1}), T {1}), t_max);

  // MAX + 0 = MAX
  EXPECT_EQ(add_wrap(t_max, T {0}), t_max);

  // MIN + 0 = MIN
  EXPECT_EQ(add_wrap(t_min, T {0}), t_min);

  // MAX + 1 = MIN <wrapped>
  EXPECT_EQ(add_wrap(t_max, T {1}), t_min);

  // MAX + 2 = MIN + 1 <wrapped>
  EXPECT_EQ(add_wrap(t_max, T {2}), static_cast<T>(t_min + T {1}));

  // 1 + MAX = MIN <wrapped>
  EXPECT_EQ(add_wrap(T {1}, t_max), t_min);

  // MIN + MIN = 0 <wrapped>
  EXPECT_EQ(add_wrap(t_min, t_min), T {0});
}

template <typename T>
class AddWrapSignedTest : public testing::Test
{};

TYPED_TEST_SUITE(AddWrapSignedTest, SignedIntegerTypes, );

TYPED_TEST(AddWrapSignedTest, AddWrap)
{
  using T = TypeParam;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // -1 + 1 = 0
  EXPECT_EQ(add_wrap(T {-1}, T {1}), T {0});

  // -1 + -2 = -3
  EXPECT_EQ(add_wrap(T {-1}, T {-2}), T {-3});

  // -100 + 100 = 0
  EXPECT_EQ(add_wrap(T {-100}, T {100}), T {0});

  // MIN + MAX = -1
  EXPECT_EQ(add_wrap(t_min, t_max), T {-1});

  // MIN + -1 = MAX <wrapped>
  EXPECT_EQ(add_wrap(t_min, T {-1}), t_max);

  // MIN + -2 = MAX - 1 <wrapped>
  EXPECT_EQ(add_wrap(t_min, T {-2}), static_cast<T>(t_max - T {1}));

  // -1 + MIN = MAX <wrapped>
  EXPECT_EQ(add_wrap(T {-1}, t_min), t_max);

  // MAX + MAX = -2 <wrapped>
  EXPECT_EQ(add_wrap(t_max, t_max), T {-2});
}

template <typename T>
class AddWrapUnsignedTest : public testing::Test
{};

TYPED_TEST_SUITE(AddWrapUnsignedTest, UnsignedIntegerTypes, );

TYPED_TEST(AddWrapUnsignedTest, AddWrap)
{
  using T = TypeParam;
  constexpr auto t_max = std::numeric_limits<T>::max();

  // MAX + MAX = MAX - 1 <wrapped>
  EXPECT_EQ(add_wrap(t_max, t_max), static_cast<T>(t_max - T {1}));
}

}  // namespace
}  // namespace safely::tests

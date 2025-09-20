// Copyright (C) 2025 Albin Johansson

#include <limits>
#include <optional>

#include <gtest/gtest.h>
#include <safely/ops/div.hpp>

#include "common/types.hpp"

namespace safely::tests {
namespace {

template <typename T>
class DivTest : public testing::Test
{};

TYPED_TEST_SUITE(DivTest, IntegerTypes, );

TYPED_TEST(DivTest, Div)
{
  using T = TypeParam;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // Division by zero
  EXPECT_EQ(div(T {0}, T {0}), std::nullopt);
  EXPECT_EQ(div(T {1}, T {0}), std::nullopt);
  EXPECT_EQ(div(t_min, T {0}), std::nullopt);
  EXPECT_EQ(div(t_max, T {0}), std::nullopt);

  // 1 / 2 = 0
  EXPECT_EQ(div(T {1}, T {2}), T {0});

  // 2 / 1 = 2
  EXPECT_EQ(div(T {2}, T {1}), T {2});

  // 100 / 4 = 25
  EXPECT_EQ(div(T {100}, T {4}), T {25});

  // MAX / MAX = 1
  EXPECT_EQ(div(t_max, t_max), T {1});
}

template <typename T>
class DivSignedTest : public testing::Test
{};

TYPED_TEST_SUITE(DivSignedTest, SignedIntegerTypes, );

TYPED_TEST(DivSignedTest, Div)
{
  using T = TypeParam;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // -1 / 2 = 0
  EXPECT_EQ(div(T {-1}, T {2}), T {0});

  // 1 / -2 = 0
  EXPECT_EQ(div(T {1}, T {-2}), T {0});

  // -100 / 4 = -25
  EXPECT_EQ(div(T {-100}, T {4}), T {-25});

  // 100 / -4 = -25
  EXPECT_EQ(div(T {100}, T {-4}), T {-25});

  // -100 / -4 = 25
  EXPECT_EQ(div(T {-100}, T {-4}), T {25});

  // (MIN + 1) / -1 = MAX
  EXPECT_EQ(div(static_cast<T>(t_min + T {1}), T {-1}), t_max);

  // MIN / MAX = -1
  EXPECT_EQ(div(t_min, t_max), T {-1});

  // MAX / MIN = 0
  EXPECT_EQ(div(t_max, t_min), T {0});

  // MIN / MIN = 1
  EXPECT_EQ(div(t_min, t_min), T {1});

  // MIN / -1 => OVERFLOW
  EXPECT_EQ(div(t_min, T {-1}), std::nullopt);
}

}  // namespace
}  // namespace safely::tests

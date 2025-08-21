// Copyright (C) 2025 Albin Johansson

#include <limits>
#include <optional>

#include <gtest/gtest.h>
#include <safely/ops/add.hpp>

#include "common/types.hpp"

namespace safely::tests {
namespace {

template <typename T>
class AddOverflowTest : public testing::Test
{
 public:
  static void test_ok(const T lhs, const T rhs, const T expected_sum)
  {
    const auto sum = add(lhs, rhs);
    ASSERT_NE(sum, std::nullopt) << +lhs << " + " << +rhs;
    EXPECT_EQ(*sum, expected_sum);
  }

  static void test_err(const T lhs, const T rhs)
  {
    const auto sum = add(lhs, rhs);
    EXPECT_EQ(sum, std::nullopt) << +lhs << " + " << +rhs;
  }
};

TYPED_TEST_SUITE(AddOverflowTest, IntegerTypes, );

TYPED_TEST(AddOverflowTest, AddOverflow)
{
  using T = TypeParam;
  using Self = AddOverflowTest<T>;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // 0 + 0 = 0
  Self::test_ok(T {0}, T {0}, T {0});

  // 0 + 1 = 1
  Self::test_ok(T {0}, T {1}, T {1});

  // 1 + 2 = 3
  Self::test_ok(T {1}, T {2}, T {3});

  // (MAX - 1) + 1 = MAX
  Self::test_ok(static_cast<T>(t_max - T {1}), T {1}, t_max);

  // MAX + 0 = MAX
  Self::test_ok(t_max, T {0}, t_max);

  // MIN + 0 = MIN
  Self::test_ok(t_min, T {0}, t_min);

  // MAX + 1 => OVERFLOW
  Self::test_err(t_max, T {1});

  // MAX + 2 => OVERFLOW
  Self::test_err(t_max, T {2});

  // 1 + MAX => OVERFLOW
  Self::test_err(T {1}, t_max);

  // MAX + MAX => OVERFLOW
  Self::test_err(t_max, t_max);
}

template <typename T>
class AddOverflowSignedTest : public AddOverflowTest<T>
{};

TYPED_TEST_SUITE(AddOverflowSignedTest, SignedIntegerTypes, );

TYPED_TEST(AddOverflowSignedTest, AddOverflow)
{
  using T = TypeParam;
  using Self = AddOverflowSignedTest<T>;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // -1 + 1 = 0
  Self::test_ok(T {-1}, T {1}, T {0});

  // -1 + -2 = -3
  Self::test_ok(T {-1}, T {-2}, T {-3});

  // -100 + 100 = 0
  Self::test_ok(T {-100}, T {100}, T {0});

  // MIN + MAX = -1
  Self::test_ok(t_min, t_max, T {-1});

  // MIN + -1 => OVERFLOW
  Self::test_err(t_min, T {-1});

  // MIN + -2 => OVERFLOW
  Self::test_err(t_min, T {-2});

  // -1 + MIN => OVERFLOW
  Self::test_err(T {-1}, t_min);

  // MIN + MIN => OVERFLOW
  Self::test_err(t_min, t_min);
}

}  // namespace
}  // namespace safely::tests

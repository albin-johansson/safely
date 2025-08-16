// Copyright (C) 2025 Albin Johansson

#include <limits>

#include <gtest/gtest.h>
#include <safely/ops/add.hpp>

#include "common/types.hpp"

namespace safely::tests {
namespace {

template <typename T>
class AddTest : public testing::Test
{
 public:
  static void test_ok(const T lhs, const T rhs, const T expected_sum)
  {
    T sum {};
    ASSERT_EQ(add(lhs, rhs, sum), errc::ok);
    EXPECT_EQ(sum, expected_sum);
  }

  static void test_err(const T lhs, const T rhs, const errc expected_error)
  {
    T sum {};
    EXPECT_EQ(add(lhs, rhs, sum), expected_error);
  }
};

TYPED_TEST_SUITE(AddTest, IntegerTypes);

TYPED_TEST(AddTest, Add)
{
  using T = TypeParam;
  using Self = AddTest<T>;
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
  Self::test_err(t_max, T {1}, errc::overflow);

  // MAX + 2 => OVERFLOW
  Self::test_err(t_max, T {2}, errc::overflow);

  // 1 + MAX => OVERFLOW
  Self::test_err(T {1}, t_max, errc::overflow);

  // MAX + MAX => OVERFLOW
  Self::test_err(t_max, t_max, errc::overflow);
}

template <typename T>
class AddSignedTest : public testing::Test
{};

TYPED_TEST_SUITE(AddSignedTest, SignedIntegerTypes);

TYPED_TEST(AddSignedTest, Add)
{
  using T = TypeParam;
  using Self = AddTest<T>;
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
  Self::test_err(t_min, T {-1}, errc::overflow);

  // MIN + -2 => OVERFLOW
  Self::test_err(t_min, T {-2}, errc::overflow);

  // -1 + MIN => OVERFLOW
  Self::test_err(T {-1}, t_min, errc::overflow);

  // MIN + MIN => OVERFLOW
  Self::test_err(t_min, t_min, errc::overflow);
}

}  // namespace
}  // namespace safely::tests

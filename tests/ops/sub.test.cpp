// Copyright (C) 2025 Albin Johansson

#include <limits>

#include <gtest/gtest.h>
#include <safely/ops/sub.hpp>

#include "common/types.hpp"

namespace safely::tests {
namespace {

template <typename T>
class SubTest : public testing::Test
{
 public:
  static void test_ok(const T lhs, const T rhs, const T expected_diff)
  {
    const auto diff = sub(lhs, rhs);
    ASSERT_TRUE(diff.has_value()) << +lhs << " - " << +rhs;
    EXPECT_EQ(*diff, expected_diff);
  }

  static void test_err(const T lhs, const T rhs)
  {
    const auto diff = sub(lhs, rhs);
    EXPECT_EQ(diff, std::nullopt) << +lhs << " - " << +rhs;
  }
};

TYPED_TEST_SUITE(SubTest, IntegerTypes, );

TYPED_TEST(SubTest, Sub)
{
  using T = TypeParam;
  using Self = SubTest<T>;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // 0 - 0 = 0
  Self::test_ok(T {0}, T {0}, T {0});

  // 1 - 0 = 1
  Self::test_ok(T {1}, T {0}, T {1});

  // 3 - 2 = 1
  Self::test_ok(T {3}, T {2}, T {1});

  // MAX - 1 = (MAX - 1)
  Self::test_ok(t_max, T {1}, static_cast<T>(t_max - T {1}));

  // MIN - 0 = MIN
  Self::test_ok(t_min, T {0}, t_min);

  // MAX - 0 = MAX
  Self::test_ok(t_max, T {0}, t_max);

  // MIN - 1 => OVERFLOW
  Self::test_err(t_min, T {1});

  // MIN - 2 => OVERFLOW
  Self::test_err(t_min, T {2});

  // MIN - MAX => OVERFLOW
  Self::test_err(t_min, t_max);
}

template <typename T>
class SubSignedTest : public SubTest<T>
{};

TYPED_TEST_SUITE(SubSignedTest, SignedIntegerTypes, );

TYPED_TEST(SubSignedTest, Sub)
{
  using T = TypeParam;
  using Self = SubSignedTest<T>;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // -1 - 0 = -1
  Self::test_ok(T {-1}, T {0}, T {-1});

  // -3 - (-2) = -1
  Self::test_ok(T {-3}, T {-2}, T {-1});

  // MIN - MIN = 0
  Self::test_ok(t_min, t_min, T {0});

  // MAX - (-1) => OVERFLOW
  Self::test_err(t_max, T {-1});

  // MAX - (-2) => OVERFLOW
  Self::test_err(t_max, T {-2});
}

}  // namespace
}  // namespace safely::tests

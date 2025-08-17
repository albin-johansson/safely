// Copyright (C) 2025 Albin Johansson

#include <limits>

#include <gtest/gtest.h>
#include <safely/ops/mul.hpp>

#include "common/types.hpp"

namespace safely::tests {
namespace {

template <typename T>
class MulTest : public testing::Test
{
 public:
  static void test_ok(const T lhs, const T rhs, const T expected_product)
  {
    T product {};
    EXPECT_FALSE(mul(lhs, rhs, product)) << +lhs << " * " << +rhs;
    EXPECT_EQ(product, expected_product);
  }

  static void test_err(const T lhs, const T rhs)
  {
    T product {};
    EXPECT_TRUE(mul(lhs, rhs, product)) << +lhs << " * " << +rhs;
  }
};

TYPED_TEST_SUITE(MulTest, IntegerTypes, );

TYPED_TEST(MulTest, Mul)
{
  using T = TypeParam;
  using Self = MulTest<T>;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // 1 * 0 = 0
  Self::test_ok(T {1}, T {0}, T {0});

  // 0 * 1 = 0
  Self::test_ok(T {0}, T {1}, T {0});

  // 1 * 2 = 2
  Self::test_ok(T {1}, T {2}, T {2});

  // 6 * 7 = 41
  Self::test_ok(T {6}, T {7}, T {42});

  // MIN * 1 = MIN
  Self::test_ok(t_min, T {1}, t_min);

  // MAX * 1 = MAX
  Self::test_ok(t_max, T {1}, t_max);

  // (MIN / 2) * 2 = MIN
  Self::test_ok(static_cast<T>(t_min / T {2}), T {2}, t_min);

  // (MAX / 2) * 2 = MAX - 1
  Self::test_ok(static_cast<T>(t_max / T {2}),
                T {2},
                static_cast<T>(t_max - T {1}));

  // ((MAX / 2) + 1) * 2 => OVERFLOW
  Self::test_err(static_cast<T>(static_cast<T>(t_max / T {2}) + T {1}), T {2});

  // MAX * 2 => OVERFLOW
  Self::test_err(t_max, T {2});

  // MAX * MAX => OVERFLOW
  Self::test_err(t_max, t_max);
}

template <typename T>
class MulSignedTest : public MulTest<T>
{};

TYPED_TEST_SUITE(MulSignedTest, SignedIntegerTypes, );

TYPED_TEST(MulSignedTest, Mul)
{
  using T = TypeParam;
  using Self = MulSignedTest<T>;
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  // -1 * 2 = -2
  Self::test_ok(T {-1}, T {2}, T {-2});

  // -5 * -3 = 15
  Self::test_ok(T {-5}, T {-3}, T {15});

  // MAX * -1 = -MAX
  Self::test_ok(t_max, T {-1}, -t_max);

  // ((MIN / 2) - 1) * 2 => OVERFLOW
  Self::test_err(static_cast<T>(static_cast<T>(t_min / T {2}) - T {1}), T {2});

  // -1 * MIN => OVERFLOW
  Self::test_err(T {-1}, t_min);

  // 2 * MIN => OVERFLOW
  Self::test_err(T {2}, t_min);

  // MIN * 2 => OVERFLOW
  Self::test_err(t_min, T {2});

  // MIN * MAX => OVERFLOW
  Self::test_err(t_min, t_max);

  // MIN * MIN => OVERFLOW
  Self::test_err(t_min, t_min);
}

}  // namespace
}  // namespace safely::tests

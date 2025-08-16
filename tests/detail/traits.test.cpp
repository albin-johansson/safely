// Copyright (C) 2025 Albin Johansson

#include <gtest/gtest.h>
#include <safely/detail/traits.hpp>
#include <safely/primitives.hpp>

namespace safely::tests {
namespace {

TEST(Traits, IsInteger)
{
  EXPECT_FALSE(detail::is_integer_v<bool>);
  EXPECT_FALSE(detail::is_integer_v<char>);
  EXPECT_FALSE(detail::is_integer_v<float>);
  EXPECT_FALSE(detail::is_integer_v<double>);
  EXPECT_FALSE(detail::is_integer_v<long double>);

  EXPECT_TRUE(detail::is_integer_v<i8>);
  EXPECT_TRUE(detail::is_integer_v<i16>);
  EXPECT_TRUE(detail::is_integer_v<i32>);
  EXPECT_TRUE(detail::is_integer_v<i64>);

  EXPECT_TRUE(detail::is_integer_v<u8>);
  EXPECT_TRUE(detail::is_integer_v<u16>);
  EXPECT_TRUE(detail::is_integer_v<u32>);
  EXPECT_TRUE(detail::is_integer_v<u64>);
}

TEST(Traits, IsSignedInteger)
{
  EXPECT_FALSE(detail::is_signed_integer_v<bool>);
  EXPECT_FALSE(detail::is_signed_integer_v<char>);
  EXPECT_FALSE(detail::is_signed_integer_v<float>);
  EXPECT_FALSE(detail::is_signed_integer_v<double>);
  EXPECT_FALSE(detail::is_signed_integer_v<long double>);

  EXPECT_TRUE(detail::is_signed_integer_v<i8>);
  EXPECT_TRUE(detail::is_signed_integer_v<i16>);
  EXPECT_TRUE(detail::is_signed_integer_v<i32>);
  EXPECT_TRUE(detail::is_signed_integer_v<i64>);

  EXPECT_FALSE(detail::is_signed_integer_v<u8>);
  EXPECT_FALSE(detail::is_signed_integer_v<u16>);
  EXPECT_FALSE(detail::is_signed_integer_v<u32>);
  EXPECT_FALSE(detail::is_signed_integer_v<u64>);
}

TEST(Traits, IsUnsignedInteger)
{
  EXPECT_FALSE(detail::is_unsigned_integer_v<bool>);
  EXPECT_FALSE(detail::is_unsigned_integer_v<char>);
  EXPECT_FALSE(detail::is_unsigned_integer_v<float>);
  EXPECT_FALSE(detail::is_unsigned_integer_v<double>);
  EXPECT_FALSE(detail::is_unsigned_integer_v<long double>);

  EXPECT_FALSE(detail::is_unsigned_integer_v<i8>);
  EXPECT_FALSE(detail::is_unsigned_integer_v<i16>);
  EXPECT_FALSE(detail::is_unsigned_integer_v<i32>);
  EXPECT_FALSE(detail::is_unsigned_integer_v<i64>);

  EXPECT_TRUE(detail::is_unsigned_integer_v<u8>);
  EXPECT_TRUE(detail::is_unsigned_integer_v<u16>);
  EXPECT_TRUE(detail::is_unsigned_integer_v<u32>);
  EXPECT_TRUE(detail::is_unsigned_integer_v<u64>);
}

}  // namespace
}  // namespace safely::tests

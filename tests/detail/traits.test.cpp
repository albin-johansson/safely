// Copyright (C) 2025 Albin Johansson

#include <gtest/gtest.h>
#include <safely/detail/traits.hpp>

namespace safely::tests {
namespace {

TEST(Traits, IsInteger)
{
  EXPECT_FALSE(detail::is_integer_v<bool>);
  EXPECT_FALSE(detail::is_integer_v<char>);
  EXPECT_FALSE(detail::is_integer_v<float>);
  EXPECT_FALSE(detail::is_integer_v<double>);
  EXPECT_FALSE(detail::is_integer_v<long double>);

  EXPECT_TRUE(detail::is_integer_v<signed char>);
  EXPECT_TRUE(detail::is_integer_v<signed short>);
  EXPECT_TRUE(detail::is_integer_v<signed int>);
  EXPECT_TRUE(detail::is_integer_v<signed long>);
  EXPECT_TRUE(detail::is_integer_v<signed long long>);

  EXPECT_TRUE(detail::is_integer_v<unsigned char>);
  EXPECT_TRUE(detail::is_integer_v<unsigned short>);
  EXPECT_TRUE(detail::is_integer_v<unsigned int>);
  EXPECT_TRUE(detail::is_integer_v<unsigned long>);
  EXPECT_TRUE(detail::is_integer_v<unsigned long long>);
}

TEST(Traits, IsSignedInteger)
{
  EXPECT_FALSE(detail::is_signed_integer_v<bool>);
  EXPECT_FALSE(detail::is_signed_integer_v<char>);
  EXPECT_FALSE(detail::is_signed_integer_v<float>);
  EXPECT_FALSE(detail::is_signed_integer_v<double>);
  EXPECT_FALSE(detail::is_signed_integer_v<long double>);

  EXPECT_TRUE(detail::is_signed_integer_v<signed char>);
  EXPECT_TRUE(detail::is_signed_integer_v<signed short>);
  EXPECT_TRUE(detail::is_signed_integer_v<signed int>);
  EXPECT_TRUE(detail::is_signed_integer_v<signed long>);
  EXPECT_TRUE(detail::is_signed_integer_v<signed long long>);

  EXPECT_FALSE(detail::is_signed_integer_v<unsigned char>);
  EXPECT_FALSE(detail::is_signed_integer_v<unsigned short>);
  EXPECT_FALSE(detail::is_signed_integer_v<unsigned int>);
  EXPECT_FALSE(detail::is_signed_integer_v<unsigned long>);
  EXPECT_FALSE(detail::is_signed_integer_v<unsigned long long>);
}

TEST(Traits, IsUnsignedInteger)
{
  EXPECT_FALSE(detail::is_unsigned_integer_v<bool>);
  EXPECT_FALSE(detail::is_unsigned_integer_v<char>);
  EXPECT_FALSE(detail::is_unsigned_integer_v<float>);
  EXPECT_FALSE(detail::is_unsigned_integer_v<double>);
  EXPECT_FALSE(detail::is_unsigned_integer_v<long double>);

  EXPECT_FALSE(detail::is_unsigned_integer_v<signed char>);
  EXPECT_FALSE(detail::is_unsigned_integer_v<signed short>);
  EXPECT_FALSE(detail::is_unsigned_integer_v<signed int>);
  EXPECT_FALSE(detail::is_unsigned_integer_v<signed long>);
  EXPECT_FALSE(detail::is_unsigned_integer_v<signed long long>);

  EXPECT_TRUE(detail::is_unsigned_integer_v<unsigned char>);
  EXPECT_TRUE(detail::is_unsigned_integer_v<unsigned short>);
  EXPECT_TRUE(detail::is_unsigned_integer_v<unsigned int>);
  EXPECT_TRUE(detail::is_unsigned_integer_v<unsigned long>);
  EXPECT_TRUE(detail::is_unsigned_integer_v<unsigned long long>);
}

}  // namespace
}  // namespace safely::tests

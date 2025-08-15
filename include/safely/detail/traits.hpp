// Copyright (C) 2025 Albin Johansson

#pragma once

namespace safely::detail {

template <typename T>
inline constexpr bool is_integer_v = false;

template <>
inline constexpr bool is_integer_v<unsigned char> = true;

template <>
inline constexpr bool is_integer_v<unsigned short> = true;

template <>
inline constexpr bool is_integer_v<unsigned int> = true;

template <>
inline constexpr bool is_integer_v<unsigned long> = true;

template <>
inline constexpr bool is_integer_v<unsigned long long> = true;

template <>
inline constexpr bool is_integer_v<signed char> = true;

template <>
inline constexpr bool is_integer_v<signed short> = true;

template <>
inline constexpr bool is_integer_v<signed int> = true;

template <>
inline constexpr bool is_integer_v<signed long> = true;

template <>
inline constexpr bool is_integer_v<signed long long> = true;

template <typename T>
inline constexpr bool is_signed_integer_v = false;

template <>
inline constexpr bool is_signed_integer_v<signed char> = true;

template <>
inline constexpr bool is_signed_integer_v<signed short> = true;

template <>
inline constexpr bool is_signed_integer_v<signed int> = true;

template <>
inline constexpr bool is_signed_integer_v<signed long> = true;

template <>
inline constexpr bool is_signed_integer_v<signed long long> = true;

template <typename T>
inline constexpr bool is_unsigned_integer_v = false;

template <>
inline constexpr bool is_unsigned_integer_v<unsigned char> = true;

template <>
inline constexpr bool is_unsigned_integer_v<unsigned short> = true;

template <>
inline constexpr bool is_unsigned_integer_v<unsigned int> = true;

template <>
inline constexpr bool is_unsigned_integer_v<unsigned long> = true;

template <>
inline constexpr bool is_unsigned_integer_v<unsigned long long> = true;

}  // namespace safely::detail

// Copyright (C) 2025 Albin Johansson

#pragma once

#include <type_traits>

#include <safely/primitives.hpp>

namespace safely::detail {

template <typename T>
inline constexpr bool is_integer_v = false;

template <>
inline constexpr bool is_integer_v<u8> = true;

template <>
inline constexpr bool is_integer_v<u16> = true;

template <>
inline constexpr bool is_integer_v<u32> = true;

template <>
inline constexpr bool is_integer_v<u64> = true;

template <>
inline constexpr bool is_integer_v<i8> = true;

template <>
inline constexpr bool is_integer_v<i16> = true;

template <>
inline constexpr bool is_integer_v<i32> = true;

template <>
inline constexpr bool is_integer_v<i64> = true;

template <typename T>
inline constexpr bool is_signed_integer_v = false;

template <>
inline constexpr bool is_signed_integer_v<i8> = true;

template <>
inline constexpr bool is_signed_integer_v<i16> = true;

template <>
inline constexpr bool is_signed_integer_v<i32> = true;

template <>
inline constexpr bool is_signed_integer_v<i64> = true;

template <typename T>
inline constexpr bool is_unsigned_integer_v = false;

template <>
inline constexpr bool is_unsigned_integer_v<u8> = true;

template <>
inline constexpr bool is_unsigned_integer_v<u16> = true;

template <>
inline constexpr bool is_unsigned_integer_v<u32> = true;

template <>
inline constexpr bool is_unsigned_integer_v<u64> = true;

// Used to obtain a suitable arithmetic type for T.
// This is mainly used to avoid issues with implicit signed integer promotions
// when dealing with small types such as char and short.
template <typename T>
using arithmetic_t =
    std::conditional_t<std::is_signed_v<T>,
                       std::conditional_t<sizeof(T) < sizeof(int), int, T>,
                       std::conditional_t<sizeof(T) < sizeof(uint), uint, T>>;

template <typename T>
[[nodiscard]] constexpr auto to_arithmetic(const T value) noexcept
    -> arithmetic_t<T>
{
  return static_cast<arithmetic_t<T>>(value);
}

template <typename T>
[[nodiscard]] constexpr auto to_unsigned(const T value) noexcept
    -> std::make_unsigned_t<T>
{
  return static_cast<std::make_unsigned_t<T>>(value);
}

template <typename T>
[[nodiscard]] constexpr auto to_signed(const T value) noexcept
    -> std::make_signed_t<T>
{
  return static_cast<std::make_signed_t<T>>(value);
}

}  // namespace safely::detail

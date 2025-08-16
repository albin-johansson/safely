// Copyright (C) 2025 Albin Johansson

#pragma once

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

}  // namespace safely::detail

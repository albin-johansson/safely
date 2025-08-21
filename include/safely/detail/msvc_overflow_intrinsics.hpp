// Copyright (C) 2025 Albin Johansson

#pragma once

#include <optional>
#include <type_traits>

#include <safely/detail/traits.hpp>
#include <safely/predef.hpp>
#include <safely/primitives.hpp>

#if SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS
  #include <intrin.h>
#endif

namespace safely::detail {

#if SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS

template <typename T, signed_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto msvc_add_overflow(const T lhs,
                                               const T rhs,
                                               T& sum) noexcept -> bool
{
  if constexpr (std::is_same_v<T, i8>) {
    return _add_overflow_i8(0, lhs, rhs, &sum);
  }
  else if constexpr (std::is_same_v<T, i16>) {
    return _add_overflow_i16(0, lhs, rhs, &sum);
  }
  else if constexpr (std::is_same_v<T, i32>) {
    return _add_overflow_i32(0, lhs, rhs, &sum);
  }
  else /* if constexpr (std::is_same_v<T, i64>) */ {
    static_assert(std::is_same_v<T, i64>);
    return _add_overflow_i64(0, lhs, rhs, &sum);
  }
}

template <typename T, unsigned_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto msvc_add_overflow(const T lhs,
                                               const T rhs,
                                               T& sum) noexcept -> bool
{
  if constexpr (std::is_same_v<T, u8>) {
    return _addcarry_u8(0, lhs, rhs, &sum);
  }
  else if constexpr (std::is_same_v<T, u16>) {
    return _addcarry_u16(0, lhs, rhs, &sum);
  }
  else if constexpr (std::is_same_v<T, u32>) {
    return _addcarry_u32(0, lhs, rhs, &sum);
  }
  else /* if constexpr (std::is_same_v<T, u64>) */ {
    static_assert(std::is_same_v<T, u64>);
    return _addcarry_u64(0, lhs, rhs, &sum);
  }
}

template <typename T, signed_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto msvc_sub_overflow(const T lhs,
                                               const T rhs,
                                               T& diff) noexcept -> bool
{
  if constexpr (std::is_same_v<T, i8>) {
    return _sub_overflow_i8(0, lhs, rhs, &diff);
  }
  else if constexpr (std::is_same_v<T, i16>) {
    return _sub_overflow_i16(0, lhs, rhs, &diff);
  }
  else if constexpr (std::is_same_v<T, i32>) {
    return _sub_overflow_i32(0, lhs, rhs, &diff);
  }
  else /* if constexpr (std::is_same_v<T, i64>) */ {
    static_assert(std::is_same_v<T, i64>);
    return _sub_overflow_i64(0, lhs, rhs, &diff);
  }
}

template <typename T, unsigned_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto msvc_sub_overflow(const T lhs,
                                               const T rhs,
                                               T& diff) noexcept -> bool
{
  if constexpr (std::is_same_v<T, u8>) {
    return _subborrow_u8(0, lhs, rhs, &diff);
  }
  else if constexpr (std::is_same_v<T, u16>) {
    return _subborrow_u16(0, lhs, rhs, &diff);
  }
  else if constexpr (std::is_same_v<T, u32>) {
    return _subborrow_u32(0, lhs, rhs, &diff);
  }
  else /* if constexpr (std::is_same_v<T, u64>) */ {
    static_assert(std::is_same_v<T, u64>);
    return _subborrow_u64(0, lhs, rhs, &diff);
  }
}

template <typename T, signed_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto msvc_mul_overflow(const T lhs,
                                               const T rhs,
                                               T& product) noexcept -> bool
{
  if constexpr (std::is_same_v<T, i8>) {
    return _mul_overflow_i8(lhs, rhs, &product);
  }
  else if constexpr (std::is_same_v<T, i16>) {
    return _mul_overflow_i16(lhs, rhs, &product);
  }
  else if constexpr (std::is_same_v<T, i32>) {
    return _mul_overflow_i32(lhs, rhs, &product);
  }
  else /* if constexpr (std::is_same_v<T, i64>) */ {
    static_assert(std::is_same_v<T, i64>);
    return _mul_overflow_i64(lhs, rhs, &product);
  }
}

template <typename T, unsigned_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto msvc_mul_overflow(const T lhs,
                                               const T rhs,
                                               T& product) noexcept -> bool
{
  if constexpr (std::is_same_v<T, u8>) {
    return _mul_full_overflow_u8(0, lhs, rhs, &product);
  }
  else if constexpr (std::is_same_v<T, u16>) {
    return _mul_full_overflow_u16(0, lhs, rhs, &product);
  }
  else if constexpr (std::is_same_v<T, u32>) {
    return _mul_full_overflow_u32(0, lhs, rhs, &product);
  }
  else /* if constexpr (std::is_same_v<T, u64>) */ {
    static_assert(std::is_same_v<T, u64>);
    return _mul_full_overflow_u64(0, lhs, rhs, &product);
  }
}

#endif

}  // namespace safely::detail

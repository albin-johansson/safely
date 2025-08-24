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
    i16 i16_product {};
    const auto overflow = _mul_full_overflow_i8(lhs, rhs, &i16_product);

    if (!overflow) SAFELY_ATTR_LIKELY {
      product = static_cast<i8>(i16_product);
    }

    return overflow;
  }
  else if constexpr (std::is_same_v<T, i16>) {
    i16 product_hi {};
    return _mul_full_overflow_i16(lhs, rhs, &product, &product_hi);
  }
  else if constexpr (std::is_same_v<T, i32>) {
    i32 product_hi {};
    return _mul_full_overflow_i32(lhs, rhs, &product, &product_hi);
  }
  else /* if constexpr (std::is_same_v<T, i64>) */ {
    static_assert(std::is_same_v<T, i64>);

    i64 product_hi {};
    return _mul_full_overflow_i64(lhs, rhs, &product, &product_hi);
  }
}

template <typename T, unsigned_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto msvc_mul_overflow(const T lhs,
                                               const T rhs,
                                               T& product) noexcept -> bool
{
  if constexpr (std::is_same_v<T, u8>) {
    u16 u16_product {};
    const auto overflow = _mul_full_overflow_u8(lhs, rhs, &u16_product);

    if (!overflow) SAFELY_ATTR_LIKELY {
      product = static_cast<u8>(u16_product);
    }

    return overflow;
  }
  else if constexpr (std::is_same_v<T, u16>) {
    u16 product_hi {};
    return _mul_full_overflow_u16(lhs, rhs, &product, &product_hi);
  }
  else if constexpr (std::is_same_v<T, u32>) {
    u32 product_hi {};
    return _mul_full_overflow_u32(lhs, rhs, &product, &product_hi);
  }
  else /* if constexpr (std::is_same_v<T, u64>) */ {
    static_assert(std::is_same_v<T, u64>);

    u64 product_hi {};
    return _mul_full_overflow_u64(lhs, rhs, &product, &product_hi);
  }
}

#endif

}  // namespace safely::detail

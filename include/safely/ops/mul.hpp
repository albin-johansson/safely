// Copyright (C) 2025 Albin Johansson

#pragma once

#include <limits>
#include <optional>

#include <safely/detail/msvc_overflow_intrinsics.hpp>
#include <safely/detail/traits.hpp>
#include <safely/detail/unchecked.hpp>
#include <safely/predef.hpp>

#if SAFELY_HAS_STDCKDINT
  #include <stdbool.h>
  #include <stdckdint.h>
#endif

namespace safely {
namespace detail {

// See SEI CERT C Coding Standard INT32-C.
template <typename T, signed_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto generic_mul_check_overflow(const T lhs,
                                                        const T rhs) noexcept
    -> bool
{
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  const auto is_lhs_positive = lhs > 0;
  const auto is_rhs_positive = rhs > 0;

  if (is_lhs_positive) {
    return is_rhs_positive ? lhs > div_unchecked(t_max, rhs)
                           : rhs < div_unchecked(t_min, lhs);
  }

  if (is_rhs_positive) {
    return lhs < div_unchecked(t_min, rhs);
  }

  return lhs != 0 && rhs < div_unchecked(t_max, lhs);
}

// See SEI CERT C Coding Standard INT30-C.
template <typename T, unsigned_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto generic_mul_check_overflow(const T lhs,
                                                        const T rhs) noexcept
    -> bool
{
  constexpr auto t_max = std::numeric_limits<T>::max();

  return rhs != 0 && lhs > div_unchecked(t_max, rhs);
}

template <typename T, integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto generic_mul(const T lhs, const T rhs) noexcept
    -> std::optional<T>
{
  if (generic_mul_check_overflow(lhs, rhs)) SAFELY_ATTR_UNLIKELY {
    return std::nullopt;
  }

  return mul_unchecked(lhs, rhs);
}

template <typename T, signed_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto generic_mul_wrap(const T lhs, const T rhs) noexcept
    -> T
{
  // Note, this static_cast is implementation defined.
  return static_cast<T>(mul_unchecked(to_unsigned(lhs), to_unsigned(rhs)));
}

template <typename T, unsigned_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto generic_mul_wrap(const T lhs, const T rhs) noexcept
    -> T
{
  return mul_unchecked(lhs, rhs);
}

}  // namespace detail

/// Performs checked integer multiplication.
///
/// \tparam T An integer type.
///
/// \param[in] lhs The first factor.
/// \param[in] rhs The second factor.
///
/// \return
/// The product if successful; an empty optional otherwise.
template <typename T, detail::integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto mul(const T lhs, const T rhs) noexcept
    -> std::optional<T>
{
  std::optional<T> result {};

#if SAFELY_HAS_STDCKDINT
  T product {};
  if (!ckd_mul(&product, lhs, rhs)) {
    result = product;
  }
#elif SAFELY_HAS_BUILTIN_ADD_OVERFLOW
  T product {};
  if (!__builtin_mul_overflow(lhs, rhs, &product)) {
    result = product;
  }
#elif SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS
  T product {};
  if (!detail::msvc_mul_overflow(lhs, rhs, product)) {
    result = product;
  }
#else
  result = detail::generic_mul(lhs, rhs);
#endif

  return result;
}

/// Performs checked integer multiplication, wrapping on overflow.
///
/// \tparam T An integer type.
///
/// \param[in] lhs The first factor.
/// \param[in] rhs The second factor.
///
/// \return
/// The (potentially wrapped) product.
template <typename T, detail::integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto mul_wrap(const T lhs, const T rhs) noexcept -> T
{
  T product {};

#if SAFELY_HAS_STDCKDINT
  (void) ckd_mul(&product, lhs, rhs);
#elif SAFELY_HAS_BUILTIN_ADD_OVERFLOW
  (void) __builtin_mul_overflow(lhs, rhs, &product);
#elif SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS
  (void) detail::msvc_mul_overflow(lhs, rhs, product);
#else
  product = detail::generic_mul_wrap(lhs, rhs);
#endif

  return product;
}

/// Performs checked integer multiplication, saturating on overflow.
///
/// \tparam T An integer type.
///
/// \param[in] lhs The first factor.
/// \param[in] rhs The second factor.
///
/// \return
/// The (potentially saturated) product.
template <typename T, detail::integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto mul_sat(const T lhs, const T rhs) noexcept -> T
{
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  if (const auto product = mul(lhs, rhs)) {
    return *product;
  }

  if constexpr (detail::is_unsigned_integer_v<T>) {
    return t_max;
  }
  else {
    return lhs < 0 != rhs < 0 ? t_min : t_max;
  }
}

}  // namespace safely

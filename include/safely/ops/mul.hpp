// Copyright (C) 2025 Albin Johansson

#pragma once

#include <limits>
#include <type_traits>

#include <safely/detail/msvc_overflow_intrinsics.hpp>
#include <safely/detail/traits.hpp>
#include <safely/predef.hpp>

#if SAFELY_HAS_STDCKDINT
  #include <stdbool.h>
  #include <stdckdint.h>
#endif

namespace safely {
namespace detail {

// See SEI CERT C Coding Standard INT32-C.
template <typename T, std::enable_if_t<is_signed_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_mul_check_overflow(const T lhs,
                                                        const T rhs) noexcept
    -> bool
{
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  const auto is_lhs_positive = lhs > 0;
  const auto is_rhs_positive = rhs > 0;

  if (is_lhs_positive) {
    return is_rhs_positive ? (lhs > t_max / rhs) : (rhs < t_min / lhs);
  }

  if (is_rhs_positive) {
    return lhs < t_min / rhs;
  }

  return lhs != 0 && (rhs < t_max / lhs);
}

// See SEI CERT C Coding Standard INT30-C.
template <typename T, std::enable_if_t<is_unsigned_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_mul_check_overflow(const T lhs,
                                                        const T rhs) noexcept
    -> bool
{
  constexpr auto t_max = std::numeric_limits<T>::max();

  return rhs != 0 && lhs > t_max / rhs;
}

template <typename T, std::enable_if_t<is_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_mul(const T lhs,
                                         const T rhs,
                                         T& product) noexcept -> bool
{
  const auto overflow = generic_mul_check_overflow(lhs, rhs);

  if (!overflow) SAFELY_ATTR_LIKELY {
    product = static_cast<T>(lhs * rhs);
  }

  return overflow;
}

template <typename T, std::enable_if_t<is_signed_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_mul_wrap(const T lhs, const T rhs) noexcept
    -> T
{
  using UT = std::make_unsigned_t<T>;

  // This assumes that signed integers use two's complement.
  const auto u_lhs = static_cast<UT>(lhs);
  const auto u_rhs = static_cast<UT>(rhs);

  // Note, this cast is implementation defined.
  return static_cast<T>(u_lhs * u_rhs);
}

template <typename T, std::enable_if_t<is_unsigned_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_mul_wrap(const T lhs, const T rhs) noexcept
    -> T
{
  return static_cast<T>(lhs * rhs);
}

}  // namespace detail

/// Multiplies two integers.
///
/// \param[in]  lhs     The first factor.
/// \param[in]  rhs     The second factor.
/// \param[out] product The destination of the result. This variable is left in
///                     an unspecified state if the multiplication would
///                     overflow.
///
/// \return
/// `true` if the multiplication would overflow; `false` otherwise.
template <typename T, std::enable_if_t<detail::is_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto mul(const T lhs, const T rhs, T& product) noexcept
    -> bool
{
#if SAFELY_HAS_STDCKDINT
  return ckd_mul(&product, lhs, rhs);
#elif SAFELY_HAS_BUILTIN_ADD_OVERFLOW
  return __builtin_mul_overflow(lhs, rhs, &product);
#elif SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS
  return detail::msvc_mul_overflow(lhs, rhs, product);
#else
  return detail::generic_mul(lhs, rhs, product);
#endif
}

/// Multiplies two integers, wrapping on overflow.
///
/// \param[in] lhs The first factor.
/// \param[in] rhs The second factor.
///
/// \return
/// The (potentially wrapped) product.
template <typename T, std::enable_if_t<detail::is_integer_v<T>, int> = 0>
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

/// Multiplies two integers, saturating on overflow.
///
/// \param[in] lhs The first factor.
/// \param[in] rhs The second factor.
///
/// \return
/// The (potentially saturated) product.
template <typename T, std::enable_if_t<detail::is_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto mul_sat(const T lhs, const T rhs) noexcept -> T
{
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  if (T product {}; !mul(lhs, rhs, product)) {
    return product;
  }

  if constexpr (detail::is_unsigned_integer_v<T>) {
    return t_max;
  }
  else {
    return (lhs < 0) != (rhs < 0) ? t_min : t_max;
  }
}

}  // namespace safely

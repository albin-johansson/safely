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
[[nodiscard]] constexpr auto generic_sub_check_overflow(const T lhs,
                                                        const T rhs) noexcept
    -> bool
{
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  if (rhs > T {0} && lhs < static_cast<T>(t_min + rhs)) SAFELY_ATTR_UNLIKELY {
    return true;
  }

  if (rhs < T {0} && lhs > static_cast<T>(t_max + rhs)) SAFELY_ATTR_UNLIKELY {
    return true;
  }

  return false;
}

// See SEI CERT C Coding Standard INT30-C.
template <typename T, std::enable_if_t<is_unsigned_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_sub_check_overflow(const T lhs,
                                                        const T rhs) noexcept
    -> bool
{
  if (rhs > lhs) SAFELY_ATTR_UNLIKELY {
    return true;
  }

  return false;
}

template <typename T, std::enable_if_t<is_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_sub(const T lhs,
                                         const T rhs,
                                         T& diff) noexcept -> bool
{
  const auto overflow = generic_sub_check_overflow(lhs, rhs);

  if (!overflow) SAFELY_ATTR_LIKELY {
    diff = static_cast<T>(lhs - rhs);
  }

  return overflow;
}

template <typename T, std::enable_if_t<is_signed_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_sub_wrap(const T lhs, const T rhs) noexcept
    -> T
{
  using UT = arithmetic_t<std::make_unsigned_t<T>>;

  // This assumes that signed integers use two's complement.
  const auto u_lhs = static_cast<UT>(lhs);
  const auto u_rhs = static_cast<UT>(rhs);

  // Note, this cast is implementation defined.
  return static_cast<T>(u_lhs - u_rhs);
}

template <typename T, std::enable_if_t<is_unsigned_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_sub_wrap(const T lhs, const T rhs) noexcept
    -> T
{
  return static_cast<T>(to_arithmetic(lhs) - to_arithmetic(rhs));
}

}  // namespace detail

/// Performs checked subtraction of two integers.
///
/// \param[in]  lhs  The first term.
/// \param[in]  rhs  The second term.
/// \param[out] diff The destination of the result. This variable is left in an
///                  unspecified state if the subtraction would overflow.
///
/// \return
/// `true` if the subtraction would overflow; `false` otherwise.
template <typename T, std::enable_if_t<detail::is_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto sub(const T lhs, const T rhs, T& diff) noexcept
    -> bool
{
#if SAFELY_HAS_STDCKDINT
  return ckd_sub(&diff, lhs, rhs);
#elif SAFELY_HAS_BUILTIN_SUB_OVERFLOW
  return __builtin_sub_overflow(lhs, rhs, &diff);
#elif SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS
  return detail::msvc_sub_overflow(lhs, rhs, diff);
#else
  return detail::generic_sub(lhs, rhs, diff);
#endif
}

/// Performs subtraction of two integers, wrapping on overflow.
///
/// \param[in] lhs The first term.
/// \param[in] rhs The second term.
///
/// \return
/// The (potentially wrapped) difference.
template <typename T, std::enable_if_t<detail::is_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto sub_wrap(const T lhs, const T rhs) noexcept -> T
{
  T diff {};

#if SAFELY_HAS_STDCKDINT
  (void) ckd_sub(&diff, lhs, rhs);
#elif SAFELY_HAS_BUILTIN_SUB_OVERFLOW
  (void) __builtin_sub_overflow(lhs, rhs, &diff);
#elif SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS
  (void) detail::msvc_sub_overflow(lhs, rhs, diff);
#else
  diff = detail::generic_sub_wrap(lhs, rhs);
#endif

  return diff;
}

/// Performs subtraction of two integers, saturating on overflow.
///
/// \param[in] lhs The first term.
/// \param[in] rhs The second term.
///
/// \return
/// The (potentially saturated) difference.
template <typename T, std::enable_if_t<detail::is_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto sub_sat(const T lhs, const T rhs) noexcept -> T
{
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  if (T diff {}; !sub(lhs, rhs, diff)) {
    return diff;
  }

  if constexpr (detail::is_unsigned_integer_v<T>) {
    return t_min;
  }
  else {
    return lhs < 0 ? t_min : t_max;
  }
}

}  // namespace safely

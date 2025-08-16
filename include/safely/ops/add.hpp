// Copyright (C) 2025 Albin Johansson

#pragma once

#include <limits>
#include <type_traits>

#include <safely/detail/msvc_overflow_intrinsics.hpp>
#include <safely/detail/traits.hpp>
#include <safely/error.hpp>
#include <safely/predef.hpp>
#include <safely/primitives.hpp>

#if SAFELY_HAS_STDCKDINT
  #include <stdbool.h>
  #include <stdckdint.h>
#endif

namespace safely {
namespace detail {

// Validate a signed integer addition.
// See SEI CERT C Coding Standard INT32-C.
template <typename T, std::enable_if_t<is_signed_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_validate_add(const T lhs,
                                                  const T rhs) noexcept -> errc
{
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  if (rhs > 0 && lhs > t_max - rhs) SAFELY_ATTR_UNLIKELY {
    return errc::overflow;
  }

  if (rhs < 0 && lhs < t_min - rhs) SAFELY_ATTR_UNLIKELY {
    return errc::overflow;
  }

  return errc::ok;
}

// Validate an unsigned integer addition.
// See SEI CERT C Coding Standard INT30-C.
template <typename T, std::enable_if_t<is_unsigned_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_validate_add(const T lhs,
                                                  const T rhs) noexcept -> errc
{
  constexpr auto t_max = std::numeric_limits<T>::max();

  if (lhs > t_max - rhs) SAFELY_ATTR_UNLIKELY {
    return errc::overflow;
  }

  return errc::ok;
}

// Perform a checked integer addition.
template <typename T, std::enable_if_t<is_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_add(const T lhs,
                                         const T rhs,
                                         T& sum) noexcept -> errc
{
  const auto error = generic_validate_add(lhs, rhs);

  if (error == errc::ok) SAFELY_ATTR_LIKELY {
    sum = static_cast<T>(lhs + rhs);
  }

  return error;
}

template <typename T, std::enable_if_t<is_signed_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_add_wrap(const T lhs, const T rhs) noexcept
    -> T
{
  using UT = std::make_unsigned_t<T>;

  // This assumes that signed integers use two's complement.
  const auto u_lhs = static_cast<UT>(lhs);
  const auto u_rhs = static_cast<UT>(rhs);

  // Note, this is implementation defined.
  return static_cast<T>(u_lhs + u_rhs);
}

template <typename T, std::enable_if_t<is_unsigned_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_add_wrap(const T lhs, const T rhs) noexcept
    -> T
{
  return static_cast<T>(lhs + rhs);
}

}  // namespace detail

/// Performs checked addition of two integers.
///
/// \param[in]  lhs The first term.
/// \param[in]  rhs The second term.
/// \param[out] sum The destination of the result. This variable is left in an
///                 unspecified state in the case of failure.
///
/// \return
/// `ok` if successful; another error code otherwise.
template <typename T, std::enable_if_t<detail::is_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto add(const T lhs, const T rhs, T& sum) noexcept
    -> errc
{
#if SAFELY_HAS_STDCKDINT
  return ckd_add(&sum, lhs, rhs) ? errc::overflow : errc::ok;
#elif SAFELY_HAS_BUILTIN_ADD_OVERFLOW
  return __builtin_add_overflow(lhs, rhs, &sum) ? errc::overflow : errc::ok;
#elif SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS
  return detail::msvc_add_overflow(lhs, rhs, sum) ? errc::overflow : errc::ok;
#else
  return detail::generic_add(lhs, rhs, sum);
#endif
}

/// Performs addition of two integers, wrapping on overflow.
///
/// \param[in] lhs The first term.
/// \param[in] rhs The second term.
///
/// \return
/// The (potentially wrapped) sum of the terms.
template <typename T, std::enable_if_t<detail::is_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto add_wrap(const T lhs, const T rhs) noexcept -> T
{
  T sum {};

#if SAFELY_HAS_STDCKDINT
  (void) ckd_add(&sum, lhs, rhs);
#elif SAFELY_HAS_BUILTIN_ADD_OVERFLOW
  (void) __builtin_add_overflow(lhs, rhs, &sum);
#elif SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS
  (void) detail::msvc_add_overflow(lhs, rhs, sum);
#else
  sum = detail::generic_add_wrap(lhs, rhs);
#endif

  return sum;
}

/// Performs addition of two integers, saturating on overflow.
///
/// \param[in] lhs The first term.
/// \param[in] rhs The second term.
///
/// \return
/// The (potentially saturated) sum of the terms.
template <typename T, std::enable_if_t<detail::is_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto add_sat(const T lhs, const T rhs) noexcept -> T
{
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  if (T sum {}; add(lhs, rhs, sum) == errc::ok) {
    return sum;
  }

  if constexpr (detail::is_unsigned_integer_v<T>) {
    return t_max;
  }
  else {
    return lhs < 0 ? t_min : t_max;
  }
}

}  // namespace safely

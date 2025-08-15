#pragma once

#include <limits>
#include <type_traits>

#if __has_include(<stdckdint.h>)
  #include <stdckdint.h>
#endif

#include <safely/detail/traits.hpp>
#include <safely/error.hpp>
#include <safely/predef.hpp>

namespace safely {
namespace detail {

// Validate a signed integer addition.
// See SEI CERT C Coding Standard INT32-C.
template <typename T, std::enable_if_t<is_signed_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto slow_validate_add(const T lhs,
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
[[nodiscard]] constexpr auto slow_validate_add(const T lhs,
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
[[nodiscard]] constexpr auto slow_add(const T lhs, const T rhs, T& sum) noexcept
    -> errc
{
  const auto error = slow_validate_add(lhs, rhs);

  if (error == errc::ok) SAFELY_ATTR_LIKELY {
    sum = static_cast<T>(lhs + rhs);
  }

  return error;
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
#ifndef SAFELY_NO_INTRINSICS
  #if __STDC_VERSION_STDCKDINT_H__ >= 202311L
  return ckd_add(&sum, lhs, rhs) ? errc::overflow : errc::ok;
  #elif defined(__has_builtin) && __has_builtin(__builtin_add_overflow)
  return __builtin_add_overflow(lhs, rhs, &sum) ? errc::overflow : errc::ok;
  #endif
#endif

  return detail::slow_add(lhs, rhs, sum);
}

}  // namespace safely

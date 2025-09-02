// Copyright (C) 2025 Albin Johansson

#pragma once

#include <limits>
#include <optional>

#include <safely/detail/msvc_overflow_intrinsics.hpp>
#include <safely/detail/traits.hpp>
#include <safely/detail/unchecked.hpp>
#include <safely/predef.hpp>

#if SAFELY_HAS_STDCKDINT
  #include <stdbool.h>  // NOLINT(*-deprecated-headers)
  #include <stdckdint.h>
#endif

namespace safely {
namespace detail {

template <typename T, integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto check_sub_overflow_sw(const T lhs,
                                                   const T rhs) noexcept -> bool
{
  if constexpr (is_signed_integer_v<T>) {
    constexpr auto t_min = std::numeric_limits<T>::min();
    constexpr auto t_max = std::numeric_limits<T>::max();

    return (rhs > 0 && lhs < add_unchecked(t_min, rhs)) ||
           (rhs < 0 && lhs > add_unchecked(t_max, rhs));
  }
  else {
    return rhs > lhs;
  }
}

template <typename T, integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto sub_sw(const T lhs, const T rhs) noexcept
    -> std::optional<T>
{
  if (check_sub_overflow_sw(lhs, rhs)) SAFELY_ATTR_UNLIKELY {
    return std::nullopt;
  }

  return sub_unchecked(lhs, rhs);
}

template <typename T, integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto sub_wrap_sw(const T lhs, const T rhs) noexcept -> T
{
  if constexpr (is_signed_integer_v<T>) {
    // Note, this static_cast is implementation defined.
    return static_cast<T>(sub_unchecked(to_unsigned(lhs), to_unsigned(rhs)));
  }
  else {
    return sub_unchecked(lhs, rhs);
  }
}

}  // namespace detail

/// Performs checked integer subtraction.
///
/// \tparam T An integer type.
///
/// \param[in] lhs The first term.
/// \param[in] rhs The second term.
///
/// \return
/// The difference if successful; an empty optional otherwise.
template <typename T, detail::integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto sub(const T lhs, const T rhs) noexcept
    -> std::optional<T>
{
  std::optional<T> result {};

#if SAFELY_HAS_STDCKDINT
  T diff {};
  if (!ckd_sub(&diff, lhs, rhs)) SAFELY_ATTR_LIKELY {
    result = diff;
  }
#elif SAFELY_HAS_BUILTIN_SUB_OVERFLOW
  T diff {};
  if (!__builtin_sub_overflow(lhs, rhs, &diff)) SAFELY_ATTR_LIKELY {
    result = diff;
  }
#elif SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS
  T diff {};
  if (!detail::msvc_sub_overflow(lhs, rhs, diff)) SAFELY_ATTR_LIKELY {
    result = diff;
  }
#else
  result = detail::sub_sw(lhs, rhs);
#endif

  return result;
}

/// Performs checked integer subtraction, wrapping on overflow.
///
/// \tparam T An integer type.
///
/// \param[in] lhs The first term.
/// \param[in] rhs The second term.
///
/// \return
/// The wrapped difference.
template <typename T, detail::integer_concept_t<T> = 0>
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
  diff = detail::sub_wrap_sw(lhs, rhs);
#endif

  return diff;
}

/// Performs checked integer subtraction, saturating on overflow.
///
/// \tparam T An integer type.
///
/// \param[in] lhs The first term.
/// \param[in] rhs The second term.
///
/// \return
/// The saturated difference.
template <typename T, detail::integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto sub_sat(const T lhs, const T rhs) noexcept -> T
{
  if (const auto diff = sub(lhs, rhs)) SAFELY_ATTR_LIKELY {
    return *diff;
  }

  if constexpr (detail::is_unsigned_integer_v<T>) {
    return std::numeric_limits<T>::min();
  }
  else {
    return lhs < 0 ? std::numeric_limits<T>::min()
                   : std::numeric_limits<T>::max();
  }
}

}  // namespace safely

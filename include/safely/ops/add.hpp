// Copyright (C) 2025 Albin Johansson

#pragma once

#include <limits>
#include <optional>

#include <safely/detail/msvc.hpp>
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
[[nodiscard]] constexpr auto check_add_overflow_sw(const T lhs,
                                                   const T rhs) noexcept -> bool
{
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  if constexpr (is_signed_integer_v<T>) {
    return (rhs > 0 && lhs > sub_unchecked(t_max, rhs)) ||
           (rhs < 0 && lhs < sub_unchecked(t_min, rhs));
  }
  else {
    return lhs > sub_unchecked(t_max, rhs);
  }
}

template <typename T, integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto add_sw(const T lhs, const T rhs) noexcept
    -> std::optional<T>
{
  if (check_add_overflow_sw(lhs, rhs)) SAFELY_ATTR_UNLIKELY {
    return std::nullopt;
  }

  return add_unchecked(lhs, rhs);
}

template <typename T, integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto add_wrap_sw(const T lhs, const T rhs) noexcept -> T
{
  if constexpr (is_signed_integer_v<T>) {
    // Note, this static_cast is implementation defined.
    return static_cast<T>(add_unchecked(to_unsigned(lhs), to_unsigned(rhs)));
  }
  else {
    return add_unchecked(lhs, rhs);
  }
}

}  // namespace detail

/// Performs checked integer addition.
///
/// \tparam T An integer type.
///
/// \param[in] lhs The first term.
/// \param[in] rhs The second term.
///
/// \return
/// The sum if successful; an empty optional otherwise.
template <typename T, detail::integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto add(const T lhs, const T rhs) noexcept
    -> std::optional<T>
{
  std::optional<T> result {};

#if SAFELY_HAS_STDCKDINT
  T sum {};
  if (!ckd_add(&sum, lhs, rhs)) {
    result = sum;
  }
#elif SAFELY_HAS_BUILTIN_ADD_OVERFLOW
  T sum {};
  if (!__builtin_add_overflow(lhs, rhs, &sum)) {
    result = sum;
  }
#elif SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS
  T sum {};
  if (!detail::msvc_add_overflow(lhs, rhs, sum)) {
    result = sum;
  }
#else
  result = detail::add_sw(lhs, rhs);
#endif

  return result;
}

/// Performs addition of two integers, wrapping on overflow.
///
/// \tparam T An integer type.
///
/// \param[in] lhs The first term.
/// \param[in] rhs The second term.
///
/// \return
/// The wrapped sum.
template <typename T, detail::integer_concept_t<T> = 0>
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
  sum = detail::add_wrap_sw(lhs, rhs);
#endif

  return sum;
}

/// Performs addition of two integers, saturating on overflow.
///
/// \tparam T An integer type.
///
/// \param[in] lhs The first term.
/// \param[in] rhs The second term.
///
/// \return
/// The saturated sum.
template <typename T, detail::integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto add_sat(const T lhs, const T rhs) noexcept -> T
{
  if (const auto sum = add(lhs, rhs)) SAFELY_ATTR_LIKELY {
    return *sum;
  }

  if constexpr (detail::is_unsigned_integer_v<T>) {
    return std::numeric_limits<T>::max();
  }
  else {
    return lhs < 0 ? std::numeric_limits<T>::min()
                   : std::numeric_limits<T>::max();
  }
}

}  // namespace safely

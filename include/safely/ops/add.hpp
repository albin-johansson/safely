// Copyright (C) 2025 Albin Johansson

#pragma once

#include <limits>
#include <type_traits>

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
[[nodiscard]] constexpr auto generic_add_check_overflow(const T lhs,
                                                        const T rhs) noexcept
    -> bool
{
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  if (rhs > 0 && lhs > sub_unchecked(t_max, rhs)) SAFELY_ATTR_UNLIKELY {
    return true;
  }

  if (rhs < 0 && lhs < sub_unchecked(t_min, rhs)) SAFELY_ATTR_UNLIKELY {
    return true;
  }

  return false;
}

// See SEI CERT C Coding Standard INT30-C.
template <typename T, unsigned_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto generic_add_check_overflow(const T lhs,
                                                        const T rhs) noexcept
    -> bool
{
  constexpr auto t_max = std::numeric_limits<T>::max();
  return lhs > sub_unchecked(t_max, rhs);
}

template <typename T, integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto generic_add(const T lhs,
                                         const T rhs,
                                         T& sum) noexcept -> bool
{
  const auto overflow = generic_add_check_overflow(lhs, rhs);

  if (!overflow) SAFELY_ATTR_LIKELY {
    sum = add_unchecked(lhs, rhs);
  }

  return overflow;
}

template <typename T, std::enable_if_t<is_signed_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_add_wrap(const T lhs, const T rhs) noexcept
    -> T
{
  // Note, this static_cast is implementation defined.
  return static_cast<T>(add_unchecked(to_unsigned(lhs), to_unsigned(rhs)));
}

template <typename T, unsigned_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto generic_add_wrap(const T lhs, const T rhs) noexcept
    -> T
{
  return add_unchecked(lhs, rhs);
}

}  // namespace detail

/// Performs checked addition of two integers.
///
/// \tparam T An integer type.
///
/// \param[in]  lhs The first term.
/// \param[in]  rhs The second term.
/// \param[out] sum The destination of the result. This variable is left in an
///                 unspecified state if the addition would overflow.
///
/// \return
/// `true` if the addition would overflow; `false` otherwise.
template <typename T, detail::integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto add(const T lhs, const T rhs, T& sum) noexcept
    -> bool
{
#if SAFELY_HAS_STDCKDINT
  return ckd_add(&sum, lhs, rhs);
#elif SAFELY_HAS_BUILTIN_ADD_OVERFLOW
  return __builtin_add_overflow(lhs, rhs, &sum);
#elif SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS
  return detail::msvc_add_overflow(lhs, rhs, sum);
#else
  return detail::generic_add(lhs, rhs, sum);
#endif
}

/// Performs addition of two integers, wrapping on overflow.
///
/// \tparam T An integer type.
///
/// \param[in] lhs The first term.
/// \param[in] rhs The second term.
///
/// \return
/// The (potentially wrapped) sum of the terms.
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
  sum = detail::generic_add_wrap(lhs, rhs);
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
/// The (potentially saturated) sum of the terms.
template <typename T, detail::integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto add_sat(const T lhs, const T rhs) noexcept -> T
{
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  if (T sum {}; !add(lhs, rhs, sum)) {
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

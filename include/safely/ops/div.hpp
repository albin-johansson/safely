// Copyright (C) 2025 Albin Johansson

#pragma once

#include <limits>
#include <optional>
#include <type_traits>

#include <safely/detail/traits.hpp>
#include <safely/detail/unchecked.hpp>
#include <safely/predef.hpp>

namespace safely {
namespace detail {

template <typename T, std::enable_if_t<is_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto div_check_overflow(const T lhs,
                                                const T rhs) noexcept -> bool
{
  if constexpr (is_signed_integer_v<T>) {
    // See SEI CERT C Coding Standard INT32-C.
    constexpr auto t_min = std::numeric_limits<T>::min();
    return lhs == t_min && rhs == -1;
  }
  else {
    return false;
  }
}

}  // namespace detail

/// Performs checked integer division.
///
/// \param[in] lhs The numerator.
/// \param[in] rhs The denominator.
///
/// \return
/// The quotient if successful; an empty optional otherwise.
template <typename T, std::enable_if_t<detail::is_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto div(const T lhs, const T rhs) noexcept
    -> std::optional<T>
{
  // See SEI CERT C Coding Standard INT33-C.
  if (rhs == 0 || detail::div_check_overflow(lhs, rhs)) SAFELY_ATTR_UNLIKELY {
    return std::nullopt;
  }

  return detail::div_unchecked(lhs, rhs);
}

}  // namespace safely

// Copyright (C) 2025 Albin Johansson

#pragma once

#include <limits>
#include <optional>

#include <safely/detail/traits.hpp>
#include <safely/predef.hpp>

namespace safely {
namespace detail {

template <typename T, integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto div_check_overflow(const T lhs,
                                                const T rhs) noexcept -> bool
{
  if constexpr (is_signed_integer_v<T>) {
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
/// \tparam T An integer type.
///
/// \param[in] lhs The numerator.
/// \param[in] rhs The denominator.
///
/// \return
/// The quotient if successful; an empty optional otherwise.
template <typename T, detail::integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto div(const T lhs, const T rhs) noexcept
    -> std::optional<T>
{
  if (rhs == 0 || detail::div_check_overflow(lhs, rhs)) SAFELY_ATTR_UNLIKELY {
    return {};
  }

  using tmp_t = detail::arithmetic_t<T>;
  return static_cast<T>(static_cast<tmp_t>(lhs) / static_cast<tmp_t>(rhs));
}

}  // namespace safely

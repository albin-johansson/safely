// Copyright (C) 2025 Albin Johansson

#pragma once

#include <limits>
#include <optional>

#include <safely/detail/traits.hpp>
#include <safely/detail/unchecked.hpp>
#include <safely/predef.hpp>

namespace safely {


/// Performs a checked bitwise left shift of an integer.
///
/// Note, this function permits unsigned integer overflow.
///
/// \tparam T An integer type.
///
/// \param[in] lhs The shift target.
/// \param[in] rhs The shift amount.
///
/// \return
/// The shifted value if successful; an empty optional otherwise.
template <typename T, detail::integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto shl(const T lhs, const T rhs) noexcept
    -> std::optional<T>
{
  constexpr T t_digits {std::numeric_limits<T>::digits};
  constexpr auto t_max = std::numeric_limits<T>::max();

  if constexpr (detail::is_signed_integer_v<T>) {
    if (lhs < 0 || rhs < 0 || rhs >= t_digits || lhs > (t_max >> rhs))
        SAFELY_ATTR_UNLIKELY {
      return std::nullopt;
    }
  }
  else {
    if (rhs >= t_digits) SAFELY_ATTR_UNLIKELY {
      return std::nullopt;
    }
  }

  return detail::shl_unchecked(lhs, rhs);
}

}  // namespace safely

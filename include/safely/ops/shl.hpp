// Copyright (C) 2025 Albin Johansson

#pragma once

#include <limits>
#include <optional>

#include <safely/detail/traits.hpp>
#include <safely/predef.hpp>

namespace safely {

/// Performs a checked bitwise left shift of an integer.
///
/// Note, this function permits unsigned integer overflow.
///
/// \tparam T An unsigned integer type.
///
/// \param[in] lhs The shift target.
/// \param[in] rhs The shift amount.
///
/// \return
/// The shifted value if successful; an empty optional otherwise.
template <typename T, detail::unsigned_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto shl(const T lhs, const T rhs) noexcept
    -> std::optional<T>
{
  constexpr T t_digits {std::numeric_limits<T>::digits};

  if (rhs >= t_digits) SAFELY_ATTR_UNLIKELY {
    return {};
  }

  return static_cast<T>(static_cast<detail::arithmetic_t<T>>(lhs)
                        << static_cast<detail::arithmetic_t<T>>(rhs));
}

}  // namespace safely

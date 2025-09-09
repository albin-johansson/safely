// Copyright (C) 2025 Albin Johansson

#pragma once

#include <limits>
#include <optional>
#include <type_traits>

#include <safely/detail/traits.hpp>
#include <safely/ops/cmp.hpp>
#include <safely/predef.hpp>

namespace safely {

/// Indicates whether an integer is in range of another integer type.
///
/// \tparam To   The target integer type.
/// \tparam From The source integer type.
///
/// \param[in] from The value to range check.
///
/// \return
/// True if the value is in the range of the target type; false otherwise.
template <typename To,
          typename From,
          detail::variadic_integer_concept_t<To, From> = 0>
[[nodiscard]] constexpr auto in_range(const From from) noexcept -> bool
{
  if constexpr (std::is_same_v<To, From>) {
    return true;
  }
  else {
    if constexpr (std::is_signed_v<From>) {
      if (cmp_lt(from, std::numeric_limits<To>::min())) SAFELY_ATTR_UNLIKELY {
        return false;
      }
    }

    if (cmp_gt(from, std::numeric_limits<To>::max())) SAFELY_ATTR_UNLIKELY {
      return false;
    }

    return true;
  }
}

/// Performs a lossless integral type conversion.
///
/// \tparam To   The target integer type.
/// \tparam From The source integer type.
///
/// \param[in] from The value to convert.
///
/// \return
/// The converted value if successful; an empty optional otherwise.
template <typename To,
          typename From,
          detail::variadic_integer_concept_t<To, From> = 0>
[[nodiscard]] constexpr auto cast(const From from) noexcept -> std::optional<To>
{
  if (!in_range<To>(from)) SAFELY_ATTR_UNLIKELY {
    return std::nullopt;
  }

  return static_cast<To>(from);
}

/// Performs a lossless signed-to-unsigned integral type conversion.
///
/// \tparam T A signed integer type.
///
/// \param[in] val The value to convert.
///
/// \return
/// An unsigned value if successful; an empty optional otherwise.
template <typename T, detail::signed_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto to_unsigned(const T val) noexcept
    -> std::optional<std::make_unsigned_t<T>>
{
  return cast<std::make_unsigned_t<T>>(val);
}

/// Performs a lossless unsigned-to-signed integral type conversion.
///
/// \tparam T An unsigned integer type.
///
/// \param[in] val The value to convert.
///
/// \return
/// A signed value if successful; an empty optional otherwise.
template <typename T, detail::unsigned_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto to_signed(const T val) noexcept
    -> std::optional<std::make_signed_t<T>>
{
  return cast<std::make_signed_t<T>>(val);
}

}  // namespace safely

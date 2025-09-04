// Copyright (C) 2025 Albin Johansson

#pragma once

#include <type_traits>

#include <safely/detail/traits.hpp>

namespace safely {

/// Indicates whether the values of two integers are equivalent.
///
/// \tparam T An integer type.
/// \tparam U An integer type.
///
/// \param[in] lhs The left-hand side operand.
/// \param[in] rhs The right-hand side operand.
///
/// \return
/// True if the integers values are equivalent; false otherwise.
template <typename T, typename U, detail::variadic_integer_concept_t<T, U> = 0>
[[nodiscard]] constexpr auto cmp_eq(const T lhs, const U rhs) noexcept -> bool
{
  if constexpr (std::is_signed_v<T> == std::is_signed_v<U>) {
    return lhs == rhs;
  }
  else if constexpr (std::is_signed_v<T>) {
    return lhs >= 0 && static_cast<std::make_unsigned_t<T>>(lhs) == rhs;
  }
  else {
    return rhs >= 0 && lhs == static_cast<std::make_unsigned_t<U>>(rhs);
  }
}

/// Indicates whether the values of two integers aren't equivalent.
///
/// \tparam T An integer type.
/// \tparam U An integer type.
///
/// \param[in] lhs The left-hand side operand.
/// \param[in] rhs The right-hand side operand.
///
/// \return
/// True if the integers values aren't equivalent; false otherwise.
template <typename T, typename U, detail::variadic_integer_concept_t<T, U> = 0>
[[nodiscard]] constexpr auto cmp_ne(const T lhs, const U rhs) noexcept -> bool
{
  return !cmp_eq(lhs, rhs);
}

/// Indicates whether an integer value is less than another integer value.
///
/// \tparam T An integer type.
/// \tparam U An integer type.
///
/// \param[in] lhs The left-hand side operand.
/// \param[in] rhs The right-hand side operand.
///
/// \return
/// True if `lhs` is less than `rhs`; false otherwise.
template <typename T, typename U, detail::variadic_integer_concept_t<T, U> = 0>
[[nodiscard]] constexpr auto cmp_lt(const T lhs, const U rhs) noexcept -> bool
{
  if constexpr (std::is_signed_v<T> == std::is_signed_v<U>) {
    return lhs < rhs;
  }
  else if constexpr (std::is_signed_v<T>) {
    return lhs < 0 || static_cast<std::make_unsigned_t<T>>(lhs) < rhs;
  }
  else /* if constexpr (std::is_signed_v<U>) */ {
    return rhs >= 0 && lhs < static_cast<std::make_unsigned_t<U>>(rhs);
  }
}

/// Indicates whether an integer value is greater than another integer value.
///
/// \tparam T An integer type.
/// \tparam U An integer type.
///
/// \param[in] lhs The left-hand side operand.
/// \param[in] rhs The right-hand side operand.
///
/// \return
/// True if `lhs` is greater than `rhs`; false otherwise.
template <typename T, typename U, detail::variadic_integer_concept_t<T, U> = 0>
[[nodiscard]] constexpr auto cmp_gt(const T lhs, const U rhs) noexcept -> bool
{
  return cmp_lt(rhs, lhs);
}

/// Indicates whether an integer is less than or equal to another integer.
///
/// \tparam T An integer type.
/// \tparam U An integer type.
///
/// \param[in] lhs The left-hand side operand.
/// \param[in] rhs The right-hand side operand.
///
/// \return
/// True if `lhs` is less than or equal to `rhs`; false otherwise.
template <typename T, typename U, detail::variadic_integer_concept_t<T, U> = 0>
[[nodiscard]] constexpr auto cmp_le(const T lhs, const U rhs) noexcept -> bool
{
  return !cmp_lt(rhs, lhs);
}

/// Indicates whether an integer is greater than or equal to another integer.
///
/// \tparam T An integer type.
/// \tparam U An integer type.
///
/// \param[in] lhs The left-hand side operand.
/// \param[in] rhs The right-hand side operand.
///
/// \return
/// True if `lhs` is greater than or equal to `rhs`; false otherwise.
template <typename T, typename U, detail::variadic_integer_concept_t<T, U> = 0>
[[nodiscard]] constexpr auto cmp_ge(const T lhs, const U rhs) noexcept -> bool
{
  return !cmp_lt(lhs, rhs);
}

}  // namespace safely

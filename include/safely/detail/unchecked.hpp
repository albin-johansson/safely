// Copyright (C) 2025 Albin Johansson

#pragma once

#include <type_traits>

#include <safely/detail/traits.hpp>

namespace safely::detail {

template <typename T, integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto add_unchecked(const T lhs, const T rhs) noexcept
    -> T
{
  return static_cast<T>(to_arithmetic(lhs) + to_arithmetic(rhs));
}

template <typename T, integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto sub_unchecked(const T lhs, const T rhs) noexcept
    -> T
{
  return static_cast<T>(to_arithmetic(lhs) - to_arithmetic(rhs));
}

template <typename T, integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto mul_unchecked(const T lhs, const T rhs) noexcept
    -> T
{
  return static_cast<T>(to_arithmetic(lhs) * to_arithmetic(rhs));
}

template <typename T, integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto div_unchecked(const T lhs, const T rhs) noexcept
    -> T
{
  return static_cast<T>(to_arithmetic(lhs) / to_arithmetic(rhs));
}

template <typename T, integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto rem_unchecked(const T lhs, const T rhs) noexcept
    -> T
{
  return static_cast<T>(to_arithmetic(lhs) % to_arithmetic(rhs));
}

}  // namespace safely::detail

// Copyright (C) 2025 Albin Johansson

#pragma once

#include <limits>
#include <type_traits>

#include <safely/detail/traits.hpp>
#include <safely/predef.hpp>

namespace safely {
namespace detail {

template <typename T, unsigned_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto rotl_sw(const T val, const T n) noexcept -> T
{
  if (n == 0) SAFELY_ATTR_UNLIKELY {
    return val;
  }

  constexpr T t_digits {std::numeric_limits<T>::digits};
  const auto n_rem = n % t_digits;

  return static_cast<T>(val << n_rem | val >> (t_digits - n_rem));
}

}  // namespace detail

/// Performs a bitwise left circular shift of an integer.
///
/// \tparam T An unsigned integer type.
///
/// \param[in] val The value to rotate.
/// \param[in] n   The number of rotation steps.
///
/// \return
/// The circularly shifted value.
template <typename T, detail::unsigned_integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto rotl(const T val, const T n) noexcept -> T
{
#if SAFELY_HAS_BUILTIN_ROTATELEFT
  if constexpr (std::is_same_v<T, u64>) {
    return __builtin_rotateleft64(val, n);
  }
  else if constexpr (std::is_same_v<T, u32>) {
    return __builtin_rotateleft32(val, n);
  }
  else if constexpr (std::is_same_v<T, u16>) {
    return __builtin_rotateleft16(val, n);
  }
  else /* if constexpr (std::is_same_v<T, u8>) */ {
    static_assert(std::is_same_v<T, u8>);
    return __builtin_rotateleft8(val, n);
  }
#else
  return detail::rotl_sw(val, n);
#endif
}

}  // namespace safely

// Copyright (C) 2025 Albin Johansson

#pragma once

#include <limits>
#include <optional>

#include <safely/detail/traits.hpp>
#include <safely/predef.hpp>

namespace safely {

/// Performs checked integral negation.
///
/// \tparam T An integer type.
///
/// \param[in] val The value to negate.
///
/// \return
/// The negated value if successful; an empty optional otherwise.
template <typename T, detail::integer_concept_t<T> = 0>
[[nodiscard]] constexpr auto neg(const T val) noexcept -> std::optional<T>
{
  if constexpr (detail::is_signed_integer_v<T>) {
    if (val == std::numeric_limits<T>::min()) SAFELY_ATTR_UNLIKELY {
      return {};
    }

    return static_cast<T>(-val);
  }
  else {
    if (val != 0) SAFELY_ATTR_LIKELY {
      return {};
    }

    return T {0};
  }
}

}  // namespace safely

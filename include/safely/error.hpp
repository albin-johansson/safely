// Copyright (C) 2025 Albin Johansson

#pragma once

#include <cstdint>

namespace safely {

/// Provides common error codes.
enum class errc : std::uint8_t
{
  /// Success.
  ok,

  /// Value not representable using the target type.
  overflow,

  /// Attempted division by zero.
  div_by_zero,

  /// Attempted to shift value by too many bit positions.
  overshift,

  /// Attempted negative shift.
  negative_shift
};

}  // namespace safely

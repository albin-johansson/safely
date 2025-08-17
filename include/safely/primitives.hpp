// Copyright (C) 2025 Albin Johansson

#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>

namespace safely {

using uint = unsigned int;

using usize = std::size_t;
using isize = std::ptrdiff_t;

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

static_assert(static_cast<unsigned>(-1) == std::numeric_limits<unsigned>::max(),
              "Signed integers must use two's complement");

}  // namespace safely

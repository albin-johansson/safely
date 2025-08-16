// Copyright (C) 2025 Albin Johansson

#pragma once

#include <gtest/gtest.h>
#include <safely/primitives.hpp>

namespace safely::tests {

using SignedIntegerTypes = testing::Types<i8, i16, i32, i64>;

using UnsignedIntegerTypes = testing::Types<u8, u16, u32, u64>;

using IntegerTypes = testing::Types<i8, i16, i32, i64, u8, u16, u32, u64>;

}  // namespace safely::tests

// Copyright (C) 2025 Albin Johansson

#pragma once

#include <cstdint>
#include <limits>

#include <gtest/gtest.h>

namespace safely::tests {

template <typename T>
using Limits = std::numeric_limits<T>;

using SignedIntegerTypes = testing::Types<std::int8_t,   //
                                          std::int16_t,  //
                                          std::int32_t,  //
                                          std::int64_t>;

using UnsignedIntegerTypes = testing::Types<std::uint8_t,   //
                                            std::uint16_t,  //
                                            std::uint32_t,  //
                                            std::uint64_t>;

using IntegerTypes = testing::Types<std::int8_t,    //
                                    std::int16_t,   //
                                    std::int32_t,   //
                                    std::int64_t,   //
                                    std::uint8_t,   //
                                    std::uint16_t,  //
                                    std::uint32_t,  //
                                    std::uint64_t>;

}  // namespace safely::tests

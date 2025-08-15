// Copyright (C) 2025 Albin Johansson

#pragma once

#include <limits>

#include <gtest/gtest.h>

namespace safely::tests {

template <typename T>
using Limits = std::numeric_limits<T>;

using SignedIntegerTypes = testing::Types<signed char,   //
                                          signed short,  //
                                          signed int,    //
                                          signed long,   //
                                          signed long long>;

using UnsignedIntegerTypes = testing::Types<unsigned char,   //
                                            unsigned short,  //
                                            unsigned int,    //
                                            unsigned long,   //
                                            unsigned long long>;

using IntegerTypes = testing::Types<signed char,
                                    signed short,
                                    signed int,
                                    signed long,
                                    signed long long,
                                    unsigned char,
                                    unsigned short,
                                    unsigned int,
                                    unsigned long,
                                    unsigned long long>;

}  // namespace safely::tests

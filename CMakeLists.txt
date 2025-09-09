# Copyright (c) 2025 Albin Johansson

cmake_minimum_required(VERSION 3.31)

option(SAFELY_ENABLE_TESTS "Enable tests" OFF)
option(SAFELY_ENABLE_INTRINSICS "Enable use of compiler intrinsics" ON)
option(SAFELY_ENABLE_UBSAN "Enable UB sanitizer" OFF)
option(SAFELY_ENABLE_MODULE "Enable C++20 module" OFF)

message(DEBUG "SAFELY_ENABLE_TESTS: ${SAFELY_ENABLE_TESTS}")
message(DEBUG "SAFELY_ENABLE_INTRINSICS: ${SAFELY_ENABLE_INTRINSICS}")
message(DEBUG "SAFELY_ENABLE_UBSAN: ${SAFELY_ENABLE_UBSAN}")
message(DEBUG "SAFELY_ENABLE_MODULE: ${SAFELY_ENABLE_MODULE}")

if (SAFELY_ENABLE_TESTS)
  list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif ()

project(safely CXX)

include("tools/cmake/common.cmake")
include("tools/cmake/targets/safely.cmake")

if (SAFELY_ENABLE_MODULE)
  include("tools/cmake/targets/safely_mod.cmake")
endif ()

if (SAFELY_ENABLE_TESTS)
  include("tools/cmake/targets/safely_tests.cmake")
endif ()

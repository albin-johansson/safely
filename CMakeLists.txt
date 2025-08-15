# Copyright (c) 2025 Albin Johansson

cmake_minimum_required(VERSION 3.31)

option(SAFELY_ENABLE_TESTS "Enable tests" OFF)

if (SAFELY_ENABLE_TESTS)
  list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif ()

project(safely CXX)

include("tools/cmake/targets/safely.cmake")

if (SAFELY_ENABLE_TESTS)
  include("tools/cmake/targets/safely_tests.cmake")
endif ()

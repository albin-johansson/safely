# Copyright (c) 2025 Albin Johansson

find_package(GTest CONFIG REQUIRED)

add_executable(safely_tests)

set_target_properties(safely_tests
                      PROPERTIES
                      PREFIX ""
                      POSITION_INDEPENDENT_CODE "ON"
                      )

target_sources(safely_tests
               PRIVATE FILE_SET HEADERS BASE_DIRS "${PROJECT_SOURCE_DIR}/tests"
               FILES
               "${PROJECT_SOURCE_DIR}/tests/common/types.hpp"

               PRIVATE
               "${PROJECT_SOURCE_DIR}/tests/detail/traits.test.cpp"
               "${PROJECT_SOURCE_DIR}/tests/ops/add.test.cpp"
               "${PROJECT_SOURCE_DIR}/tests/ops/add_sat.test.cpp"
               "${PROJECT_SOURCE_DIR}/tests/safely_tests.main.cpp"
               )

if (NOT DEFINED CMAKE_CXX_STANDARD)
  target_compile_features(safely_tests PRIVATE "cxx_std_20")
endif ()

target_link_libraries(safely_tests
                      PRIVATE
                      GTest::gtest
                      safely::headers
                      )

if (MSVC)
  target_compile_definitions(safely_tests
                             PRIVATE
                             "WIN32_LEAN_AND_MEAN"
                             "NOMINMAX"
                             )

  target_compile_options(safely_tests
                         PRIVATE
                         "/EHsc"
                         "/MP"
                         "/W4"
                         "/bigobj"
                         "/permissive-"
                         "/Zc:preprocessor"
                         "/Zc:__cplusplus"
                         )
else ()
  target_compile_options(safely_tests
                         PRIVATE
                         "-Wall"
                         "-Wextra"
                         "-Wpedantic"
                         "-Wconversion"
                         "-Wsign-conversion"
                         "-Wswitch-enum"
                         "-Wold-style-cast"
                         )
endif ()

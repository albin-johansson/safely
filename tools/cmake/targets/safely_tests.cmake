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
               "${PROJECT_SOURCE_DIR}/tests/ops/add_wrap.test.cpp"
               "${PROJECT_SOURCE_DIR}/tests/ops/div.test.cpp"
               "${PROJECT_SOURCE_DIR}/tests/ops/mul.test.cpp"
               "${PROJECT_SOURCE_DIR}/tests/ops/mul_sat.test.cpp"
               "${PROJECT_SOURCE_DIR}/tests/ops/mul_wrap.test.cpp"
               "${PROJECT_SOURCE_DIR}/tests/ops/rem.test.cpp"
               "${PROJECT_SOURCE_DIR}/tests/ops/sub.test.cpp"
               "${PROJECT_SOURCE_DIR}/tests/ops/sub_sat.test.cpp"
               "${PROJECT_SOURCE_DIR}/tests/ops/sub_wrap.test.cpp"
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

target_compile_definitions(safely_tests PRIVATE "${SAFELY_COMPILE_DEFINITIONS}")
target_compile_options(safely_tests PRIVATE "${SAFELY_COMPILE_OPTIONS}")
target_link_options(safely_tests PRIVATE "${SAFELY_LINK_OPTIONS}")

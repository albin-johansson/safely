# Copyright (c) 2025 Albin Johansson

add_library(safely INTERFACE)
add_library(safely::headers ALIAS safely)

set_target_properties(safely
                      PROPERTIES
                      PREFIX ""
                      POSITION_INDEPENDENT_CODE "ON"
                      )

target_sources(safely INTERFACE FILE_SET "HEADERS" BASE_DIRS "${PROJECT_SOURCE_DIR}/include"
               FILES
               "${PROJECT_SOURCE_DIR}/include/detail/msvc_overflow_intrinsics.hpp"
               "${PROJECT_SOURCE_DIR}/include/detail/traits.hpp"
               "${PROJECT_SOURCE_DIR}/include/ops/add.hpp"
               "${PROJECT_SOURCE_DIR}/include/ops/mul.hpp"
               "${PROJECT_SOURCE_DIR}/include/ops/sub.hpp"
               "${PROJECT_SOURCE_DIR}/include/error.hpp"
               "${PROJECT_SOURCE_DIR}/include/predef.hpp"
               "${PROJECT_SOURCE_DIR}/include/primitives.hpp"
               "${PROJECT_SOURCE_DIR}/include/safely.hpp"
               )

target_compile_features(safely INTERFACE "cxx_std_17")

if (NOT SAFELY_ENABLE_INTRINSICS)
  target_compile_definitions(safely INTERFACE "SAFELY_NO_INTRINSICS")
endif ()

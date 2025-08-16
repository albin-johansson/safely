# Copyright (c) 2025 Albin Johansson

add_library(safely_mod STATIC)
add_library(safely::module ALIAS safely_mod)

set_target_properties(safely_mod
                      PROPERTIES
                      PREFIX ""
                      POSITION_INDEPENDENT_CODE "ON"
                      )

target_sources(safely_mod PUBLIC FILE_SET "CXX_MODULES" BASE_DIRS "${PROJECT_SOURCE_DIR}/modules"
               FILES
               "${PROJECT_SOURCE_DIR}/modules/safely.cppm"
               )

target_compile_features(safely_mod
                        PUBLIC
                        "cxx_std_20"
                        )

target_link_libraries(safely_mod
                      PUBLIC
                      safely::headers
                      )

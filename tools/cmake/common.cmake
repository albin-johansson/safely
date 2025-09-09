# Copyright (c) 2025 Albin Johansson

if (MSVC)
  list(APPEND SAFELY_COMPILE_DEFINITIONS
       "WIN32_LEAN_AND_MEAN"
       "NOMINMAX"
       )

  list(APPEND SAFELY_COMPILE_OPTIONS
       "/EHsc"
       "/MP"
       "/W4"
       "/bigobj"
       "/permissive-"
       "/Zc:preprocessor"
       "/Zc:__cplusplus"
       )
else ()
  list(APPEND SAFELY_COMPILE_OPTIONS
       "-Wall"
       "-Wextra"
       "-Wpedantic"
       "-Wconversion"
       "-Wsign-conversion"
       "-Wswitch-enum"
       "-Wold-style-cast"
       "-Wno-c++20-attribute-extensions"
       )

  if (SAFELY_ENABLE_UBSAN)
    list(APPEND SAFELY_COMPILE_OPTIONS
         "-fsanitize=undefined"
         "-fno-sanitize-recover"
         "-fno-omit-frame-pointer"
         )

    list(APPEND SAFELY_LINK_OPTIONS
         "-fsanitize=undefined"
         "-fno-sanitize-recover"
         "-fno-omit-frame-pointer"
         )
  endif ()
endif ()

message(DEBUG "SAFELY_COMPILE_DEFINITIONS: [${SAFELY_COMPILE_DEFINITIONS}]")
message(DEBUG "SAFELY_COMPILE_OPTIONS: [${SAFELY_COMPILE_OPTIONS}]")
message(DEBUG "SAFELY_LINK_OPTIONS: [${SAFELY_LINK_OPTIONS}]")

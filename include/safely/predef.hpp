// Copyright (C) 2025 Albin Johansson

#pragma once

#if __has_include(<stdckdint.h>)
  #include <stdckdint.h>
#endif

#if (defined(__has_cpp_attribute) && __has_cpp_attribute(likely)) || \
    (defined(__has_attribute) && __has_attribute(likely))
  #define SAFELY_ATTR_LIKELY [[likely]]
#else
  #define SAFELY_ATTR_LIKELY
#endif

#if (defined(__has_cpp_attribute) && __has_cpp_attribute(unlikely)) || \
    (defined(__has_attribute) && __has_attribute(unlikely))
  #define SAFELY_ATTR_UNLIKELY [[unlikely]]
#else
  #define SAFELY_ATTR_UNLIKELY
#endif

#define SAFELY_HAS_STDCKDINT 0
#define SAFELY_HAS_BUILTIN_ADD_OVERFLOW 0
#define SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS 0

#ifndef SAFELY_NO_INTRINSICS
  #if __STDC_VERSION_STDCKDINT_H__ >= 202311L
    #undef SAFELY_HAS_STDCKDINT
    #define SAFELY_HAS_STDCKDINT 1
  #endif

  #ifdef __has_builtin
    #if __has_builtin(__builtin_add_overflow)
      #undef SAFELY_HAS_BUILTIN_ADD_OVERFLOW
      #define SAFELY_HAS_BUILTIN_ADD_OVERFLOW 1
    #endif
  #endif

  #if _MSC_VER >= 1937  // Visual Studio 2022 17.7
    #undef SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS
    #define SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS 1
  #endif
#endif

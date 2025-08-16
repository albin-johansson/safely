// Copyright (C) 2025 Albin Johansson

#pragma once

#ifdef __has_include
  #if __has_include(<stdckdint.h>)
    #include <stdckdint.h>
  #endif
#endif

// Default macro definitions
#define SAFELY_ATTR_LIKELY
#define SAFELY_ATTR_UNLIKELY
#define SAFELY_HAS_STDCKDINT 0
#define SAFELY_HAS_BUILTIN_ADD_OVERFLOW 0
#define SAFELY_HAS_BUILTIN_SUB_OVERFLOW 0
#define SAFELY_HAS_BUILTIN_MUL_OVERFLOW 0
#define SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS 0

#ifdef __has_cpp_attribute

  #if __has_cpp_attribute(likely)
    #undef SAFELY_ATTR_LIKELY
    #define SAFELY_ATTR_LIKELY [[likely]]
  #endif

  #if __has_cpp_attribute(unlikely)
    #undef SAFELY_ATTR_UNLIKELY
    #define SAFELY_ATTR_UNLIKELY [[unlikely]]
  #endif

#endif

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

    #if __has_builtin(__builtin_sub_overflow)
      #undef SAFELY_HAS_BUILTIN_SUB_OVERFLOW
      #define SAFELY_HAS_BUILTIN_SUB_OVERFLOW 1
    #endif

    #if __has_builtin(__builtin_mul_overflow)
      #undef SAFELY_HAS_BUILTIN_MUL_OVERFLOW
      #define SAFELY_HAS_BUILTIN_MUL_OVERFLOW 1
    #endif

  #endif

  // Visual Studio 2022 17.7 (x64/x86)
  #if _MSC_VER >= 1937 && (defined(_M_X64) || defined(_M_IX86))
    #undef SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS
    #define SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS 1
  #endif

#endif

// Copyright (C) 2025 Albin Johansson

#pragma once

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

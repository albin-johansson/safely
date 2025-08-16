// Copyright (C) 2025 Albin Johansson

#include <iostream>

#include <gtest/gtest.h>
#include <safely/predef.hpp>

auto main(int argc, char* argv[]) -> int
{
  std::cout << "__cplusplus: " << __cplusplus << '\n';

#ifdef SAFELY_NO_INTRINSICS
  std::cout << "SAFELY_NO_INTRINSICS is defined\n";
#endif

  std::cout << "SAFELY_HAS_STDCKDINT: " << SAFELY_HAS_STDCKDINT << '\n';

  std::cout << "SAFELY_HAS_BUILTIN_ADD_OVERFLOW: "
            << SAFELY_HAS_BUILTIN_ADD_OVERFLOW << '\n';

  std::cout << "SAFELY_HAS_BUILTIN_SUB_OVERFLOW: "
            << SAFELY_HAS_BUILTIN_SUB_OVERFLOW << '\n';

  std::cout << "SAFELY_HAS_BUILTIN_MUL_OVERFLOW: "
            << SAFELY_HAS_BUILTIN_MUL_OVERFLOW << '\n';

  std::cout << "SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS: "
            << SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS << '\n';

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

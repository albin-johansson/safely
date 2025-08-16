# Safely

[![CI](https://github.com/albin-johansson/safely/actions/workflows/ci.yml/badge.svg)](https://github.com/albin-johansson/safely/actions/workflows/ci.yml)

Safely is a C++ library that provides safe numeric APIs, free of undefined behavior.

## Requirements

* C++17 or later
* Signed integers must use two's complement (verified at compile-time)

## Configuration

* Use `SAFELY_ENABLE_INTRINSICS` to control whether intrinsics such as `__builtin_add_overflow` are used

## See also

* SEI CERT C Coding Standard
* [Clang intrinsics](https://clang.llvm.org/docs/LanguageExtensions.html#checked-arithmetic-builtins)
* [GCC intrinsics](https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html)
* [MSVC intrinsics](https://learn.microsoft.com/en-us/cpp/intrinsics/compiler-intrinsics)
* [boostorg/safe_numerics](https://github.com/boostorg/safe_numerics)

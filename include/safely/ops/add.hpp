#pragma once

#include <cstdint>
#include <limits>
#include <type_traits>

#include <safely/detail/traits.hpp>
#include <safely/error.hpp>
#include <safely/predef.hpp>

#if SAFELY_HAS_STDCKDINT
  #include <stdckdint.h>
#endif

#if SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS
  #include <intrin.h>
#endif

namespace safely {
namespace detail {

// Validate a signed integer addition.
// See SEI CERT C Coding Standard INT32-C.
template <typename T, std::enable_if_t<is_signed_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_validate_add(const T lhs,
                                                  const T rhs) noexcept -> errc
{
  constexpr auto t_min = std::numeric_limits<T>::min();
  constexpr auto t_max = std::numeric_limits<T>::max();

  if (rhs > 0 && lhs > t_max - rhs) SAFELY_ATTR_UNLIKELY {
    return errc::overflow;
  }

  if (rhs < 0 && lhs < t_min - rhs) SAFELY_ATTR_UNLIKELY {
    return errc::overflow;
  }

  return errc::ok;
}

// Validate an unsigned integer addition.
// See SEI CERT C Coding Standard INT30-C.
template <typename T, std::enable_if_t<is_unsigned_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_validate_add(const T lhs,
                                                  const T rhs) noexcept -> errc
{
  constexpr auto t_max = std::numeric_limits<T>::max();

  if (lhs > t_max - rhs) SAFELY_ATTR_UNLIKELY {
    return errc::overflow;
  }

  return errc::ok;
}

// Perform a checked integer addition.
template <typename T, std::enable_if_t<is_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto generic_add(const T lhs,
                                         const T rhs,
                                         T& sum) noexcept -> errc
{
  const auto error = generic_validate_add(lhs, rhs);

  if (error == errc::ok) SAFELY_ATTR_LIKELY {
    sum = static_cast<T>(lhs + rhs);
  }

  return error;
}

#if SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS

template <typename T, std::enable_if_t<is_signed_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto msvc_add_overflow(const T lhs,
                                               const T rhs,
                                               T& sum) noexcept -> errc
{
  static_assert(sizeof(T) <= sizeof(std::int64_t));

  if constexpr (sizeof(T) == sizeof(std::int8_t)) {
    return _add_overflow_i8(0, lhs, rhs, &sum) ? errc::overflow : errc::ok;
  }
  else if constexpr (sizeof(T) == sizeof(std::int16_t)) {
    return _add_overflow_i16(0, lhs, rhs, &sum) ? errc::overflow : errc::ok;
  }
  else if constexpr (sizeof(T) == sizeof(std::int32_t)) {
    return _add_overflow_i32(0, lhs, rhs, &sum) ? errc::overflow : errc::ok;
  }
  else /* if constexpr (sizeof(T) == sizeof(std::int64_t)) */ {
    return _add_overflow_i64(0, lhs, rhs, &sum) ? errc::overflow : errc::ok;
  }
}

template <typename T, std::enable_if_t<is_unsigned_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto msvc_add_overflow(const T lhs,
                                               const T rhs,
                                               T& sum) noexcept -> errc
{
  static_assert(sizeof(T) <= sizeof(std::uint64_t));

  if constexpr (sizeof(T) == sizeof(std::uint8_t)) {
    return _addcarry_u8(0, lhs, rhs, &sum) ? errc::overflow : errc::ok;
  }
  else if constexpr (sizeof(T) == sizeof(std::uint16_t)) {
    return _addcarry_u16(0, lhs, rhs, &sum) ? errc::overflow : errc::ok;
  }
  else if constexpr (sizeof(T) == sizeof(std::uint32_t)) {
    return _addcarry_u32(0, lhs, rhs, &sum) ? errc::overflow : errc::ok;
  }
  else /* if constexpr (sizeof(T) == sizeof(std::uint64_t)) */ {
    return _addcarry_u64(0, lhs, rhs, &sum) ? errc::overflow : errc::ok;
  }
}

#endif

}  // namespace detail

/// Performs checked addition of two integers.
///
/// \param[in]  lhs The first term.
/// \param[in]  rhs The second term.
/// \param[out] sum The destination of the result. This variable is left in an
///                 unspecified state in the case of failure.
///
/// \return
/// `ok` if successful; another error code otherwise.
template <typename T, std::enable_if_t<detail::is_integer_v<T>, int> = 0>
[[nodiscard]] constexpr auto add(const T lhs, const T rhs, T& sum) noexcept
    -> errc
{
#if SAFELY_HAS_STDCKDINT
  return ckd_add(&sum, lhs, rhs) ? errc::overflow : errc::ok;
#elif SAFELY_HAS_BUILTIN_ADD_OVERFLOW
  return __builtin_add_overflow(lhs, rhs, &sum) ? errc::overflow : errc::ok;
#elif SAFELY_HAS_MSVC_OVERFLOW_INTRINSICS
  return detail::msvc_add_overflow(lhs, rhs, sum);
#else
  return detail::generic_add(lhs, rhs, sum);
#endif
}

}  // namespace safely

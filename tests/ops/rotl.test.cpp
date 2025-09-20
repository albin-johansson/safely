// Copyright (C) 2025 Albin Johansson

#include <safely/ops/rotl.hpp>
#include <safely/primitives.hpp>

namespace safely::tests {
namespace {

static_assert(rotl(u8 {0b0000'0001u}, u8 {0u}) == u8 {0b0000'0001u});
static_assert(rotl(u8 {0b0000'0001u}, u8 {1u}) == u8 {0b0000'0010u});
static_assert(rotl(u8 {0b0000'0001u}, u8 {2u}) == u8 {0b0000'0100u});
static_assert(rotl(u8 {0b0000'0001u}, u8 {3u}) == u8 {0b0000'1000u});
static_assert(rotl(u8 {0b0000'0001u}, u8 {4u}) == u8 {0b0001'0000u});
static_assert(rotl(u8 {0b0000'0001u}, u8 {5u}) == u8 {0b0010'0000u});
static_assert(rotl(u8 {0b0000'0001u}, u8 {6u}) == u8 {0b0100'0000u});
static_assert(rotl(u8 {0b0000'0001u}, u8 {7u}) == u8 {0b1000'0000u});
static_assert(rotl(u8 {0b0000'0001u}, u8 {8u}) == u8 {0b0000'0001u});
static_assert(rotl(u8 {0b0000'0001u}, u8 {9u}) == u8 {0b0000'0010u});

}  // namespace
}  // namespace safely::tests

// Copyright (C) 2025 Albin Johansson

module;

#include <safely/safely.hpp>

export module safely;

export namespace safely {

// <safely/error.hpp>
using safely::errc;

// <safely/ops/add.hpp>
using safely::add_overflow;
using safely::add_wrap;
using safely::add_sat;

// <safely/ops/sub.hpp>
using safely::sub;
using safely::sub_wrap;
using safely::sub_sat;

}  // namespace safely

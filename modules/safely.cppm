// Copyright (C) 2025 Albin Johansson

module;

#include <safely/safely.hpp>

export module safely;

export namespace safely {

// <safely/error.hpp>
using safely::errc;

// <safely/ops/add.hpp>
using safely::add;
using safely::add_wrap;
using safely::add_sat;

}  // namespace safely

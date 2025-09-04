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

// <safely/ops/cast.hpp>
using safely::cast;
using safely::in_range;

// <safely/ops/cmp.hpp>
using safely::cmp_eq;
using safely::cmp_ne;
using safely::cmp_lt;
using safely::cmp_le;
using safely::cmp_gt;
using safely::cmp_ge;

// <safely/ops/div.hpp>
using safely::div;

// <safely/ops/mul.hpp>
using safely::mul;
using safely::mul_wrap;
using safely::mul_sat;

// <safely/ops/rem.hpp>
using safely::rem;

// <safely/ops/shl.hpp>
using safely::shl;

// <safely/ops/sub.hpp>
using safely::sub;
using safely::sub_wrap;
using safely::sub_sat;

}  // namespace safely

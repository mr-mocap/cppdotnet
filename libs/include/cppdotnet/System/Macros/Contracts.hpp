#pragma once

#include <cppdotnet/System/Macros/Assert.hpp>

#define PRECONDITION(expr) ASSERT(expr)

#define POSTCONDITION(expr) ASSERT(expr)

#define INVARIANT(expr) ASSERT(expr)

#define IMPLIES(a, b) (!(a) || (b))
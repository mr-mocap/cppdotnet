#pragma once

#include <cassert>

// For marking unused expressions (and keeping compilers quieter)
#define UNUSED(expr) do { (void)expr; } while (0)

#define PRECONDITION(expr) assert(expr)
#define POSTCONDITION(expr) assert(expr)
#define INVARIANT(expr) assert(expr)
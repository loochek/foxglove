#pragma once

#include <cassert>

#ifdef FXG_DEBUG
#define FXG_ASSERT(expr) assert(expr)
#else
#define FXG_ASSERT(expr)
#endif

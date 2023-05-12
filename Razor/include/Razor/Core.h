#pragma once

#ifdef RZR_DEBUG
    #define RZR_CORE_ASSERT(x, ...) { if ((x) == false) { RZR_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define RZR_ASSERT(x, ...) { if ((x) == false) { RZR_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define RZR_CORE_ASSERT(x, ...)
    #define RZR_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BIND_FN(Fn) std::bind(&Fn, this, std::placeholders::_1)
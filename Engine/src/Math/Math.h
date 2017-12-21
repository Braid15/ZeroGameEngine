#pragma once

#include <float.h>
#include <math.h>
#include <cstdint>

namespace ZeroEngine {
    
    // ---------------------------------------------
    // Provides static interface for math functions
    // ---------------------------------------------

    // @TODO: Implement for other data types.

    // @TODO: Compile errors with templates. Try and fix and implement

    namespace Math {

        extern const float_t pi;

        extern float_t clamp(const float_t& orig_val, const float_t& min, const float_t& max);

        extern float_t power_of(const float_t& orig_val, const int32_t& exponent);

        extern float_t absolute_value(const float_t& orig_val);

        extern float_t square(const float_t& orig_val);

        extern float_t cube(const float_t& orig_val);

        // static T root(const T& orig_val, const int32_t& root_of);

        extern float_t square_root(const float_t& orig_val);

        #ifdef _DEBUG
        extern void run_tests();
        #endif
    }
}
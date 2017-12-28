#pragma once

#include <math.h>
#include "../AtomicTypes.h"


namespace ZeroEngine {
    
    // ---------------------------------------------
    // Provides static interface for math functions
    // ---------------------------------------------

    // @TODO: Implement for other data types.

    // @TODO: Compile errors with templates. Try and fix and implement

    namespace Math {

        extern const float32 pi;

        extern float32 clamp(const float32& orig_val, const float32& min, const float32& max);
        extern float32 clamp_min(const float32& orig_val, const float32& min);
        extern float32 clamp_max(const float32& orig_val, const float32& max);



        extern float32 power_of(const float32& orig_val, const int32& exponent);

        extern float32 absolute_value(const float32& orig_val);

        extern float32 square(const float32& orig_val);

        extern float32 cube(const float32& orig_val);

        // static T root(const T& orig_val, const i32& root_of);

        extern float32 square_root(const float32& orig_val);

        #ifdef _DEBUG
        extern void run_tests();
        #endif
    }
}
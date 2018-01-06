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

        extern const Float32 pi;

        extern Float32 clamp(const Float32& orig_val, const Float32& min, const Float32& max);
        extern Float32 clamp_min(const Float32& orig_val, const Float32& min);
        extern Float32 clamp_max(const Float32& orig_val, const Float32& max);


        extern Float32 angle_to_radian(const Degree& angle);

        extern Float32 power_of(const Float32& orig_val, const Int32& exponent);

        extern Float32 absolute_value(const Float32& orig_val);

        extern Float32 square(const Float32& orig_val);

        extern Float32 cube(const Float32& orig_val);

        extern Float32 cosine(const Float32& radian);

        extern Float32 sine(const Float32& radian);

        // static T root(const T& orig_val, const i32& root_of);

        extern Float32 square_root(const Float32& orig_val);

        #ifdef _DEBUG
        extern void run_tests();
        #endif
    }
}
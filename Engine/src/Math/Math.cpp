#include "Math.h"
#include "../Logger/Logging.h"

namespace ZeroEngine {

    // @TODO: Check and test all of these agianst equivalent clib functions

    // See @TODO in header

    namespace Math {

        const float32 pi = 3.14159f;

        // -----
        // clamp
        // -----

        float32 clamp(const float32& orig_val, const float32& min, const float32& max) {
            if (orig_val < min) {
                return min;
            } else if (orig_val > max) {
                return max;
            }
            return orig_val;
        }

        // ---------
        // clamp_min
        // ---------

        float32 clamp_min(const float32& orig_val, const float32& min) {
            if (orig_val < min) return min;
            return orig_val;
        }

        // ---------
        // clamp_max
        // ---------

        float32 clamp_max(const float32& orig_val, const float32& max) {
            if (orig_val > max) return max;
            return orig_val;
        }

        // --------
        // power_of
        // --------

        float32 power_of(const float32& orig_val, const int32& exponent) {
            /*
            f32 ret_val = orig_val;
            for (i32 i = 1; i < exponent; ++i) {
                ret_val *= orig_val;
            }
            return ret_val;
            */
            return powf(orig_val, static_cast<float32>(exponent));
        }

        #ifdef _DEBUG
        // @TODO: Try to beat!
        //
        // Mine: 14324 ms
        // powf: 1557 ms

        static void power_of_test() {
            int32 base_max = 10000;
            int32 exponent_max = 1000;
            for (int32 base = 2; base < base_max; ++base) {
                for (int32 exponent = 2; exponent < exponent_max; ++exponent) {
                    Math::power_of(static_cast<float32>(base), exponent);
                }
            }
        }
        #endif

        // --------------
        // absolute_value
        // --------------

        float32 absolute_value(const float32& orig_val) {
            return (orig_val < 0) ? orig_val * -1 : orig_val;
        }

        // ------
        // square
        // ------

        float32 square(const float32& orig_val) {
            return orig_val * orig_val;
        }

        // ----
        // cube
        // ----

        float32 cube(const float32& orig_val) {
            return orig_val * orig_val * orig_val;
        }

        // -----------
        // square_root
        // -----------

        float32 square_root(const float32& orig_val) {
            return sqrtf(orig_val);
        }


        // ---------
        // run_tests
        // ---------

        #ifdef _DEBUG
        void run_tests() {
            power_of_test();
        }
        #endif
    }
}
#include "Math.h"
#include "../Logger/Logging.h"

namespace ZeroEngine {

    // @TODO: Check and test all of these agianst equivalent clib functions

    // See @TODO in header

    namespace Math {

        const float_t pi = 3.14159f;

        // -----
        // clamp
        // -----

        float_t clamp(const float_t& orig_val, const float_t& min, const float_t& max) {
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

        float_t clamp_min(const float_t& orig_val, const float_t& min) {
            if (orig_val < min) return min;
            return orig_val;
        }

        // ---------
        // clamp_max
        // ---------

        float_t clamp_max(const float_t& orig_val, const float_t& max) {
            if (orig_val > max) return max;
            return orig_val;
        }

        // --------
        // power_of
        // --------

        float_t power_of(const float_t& orig_val, const int32_t& exponent) {
            /*
            float_t ret_val = orig_val;
            for (int i = 1; i < exponent; ++i) {
                ret_val *= orig_val;
            }
            return ret_val;
            */
            return powf(orig_val, static_cast<float>(exponent));
        }

        #ifdef _DEBUG
        // @TODO: Try to beat!
        //
        // Mine: 14324 ms
        // powf: 1557 ms

        static void power_of_test() {
            int base_max = 10000;
            int exponent_max = 1000;
            for (int base = 2; base < base_max; ++base) {
                for (int exponent = 2; exponent < exponent_max; ++exponent) {
                    Math::power_of(static_cast<float_t>(base), exponent);
                }
            }
        }
        #endif

        // --------------
        // absolute_value
        // --------------

        float_t absolute_value(const float_t& orig_val) {
            return (orig_val < 0) ? orig_val * -1 : orig_val;
        }

        // ------
        // square
        // ------

        float_t square(const float_t& orig_val) {
            return orig_val * orig_val;
        }

        // ----
        // cube
        // ----

        float_t cube(const float_t& orig_val) {
            return orig_val * orig_val * orig_val;
        }

        // -----------
        // square_root
        // -----------

        float_t square_root(const float_t& orig_val) {
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
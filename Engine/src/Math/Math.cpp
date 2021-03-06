#include "Math.h"
#include "../Logger/Logging.h"

namespace ZeroEngine {

    // @TODO: Check and test all of these agianst equivalent clib functions

    // See @TODO in header

    namespace Math {

        // -----
        // clamp
        // -----

        Float32 clamp(const Float32& orig_val, const Float32& min, const Float32& max) {
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

        Float32 clamp_min(const Float32& orig_val, const Float32& min) {
            if (orig_val < min) return min;
            return orig_val;
        }

        // ---------
        // clamp_max
        // ---------

        Float32 clamp_max(const Float32& orig_val, const Float32& max) {
            if (orig_val > max) return max;
            return orig_val;
        }

        bool floats_equal(const Float32 a, const Float32 b, Float32 epsilon) {
            return fabs(a - b) < epsilon;
        }

        // ----
        // lerp
        // ----

        Float32 lerp(const Float32& v0, const Float32& v1, const Float32& t) {
            return ((1 - t) * v0) + (t * v1);
        }

        // ----------------
        // degree_to_radian
        // ----------------

        Radian degrees_to_radians(const Degree& degree) {
            return degree * Math::pi / 180.0f;
        }

        // ----------------
        // radian_to_degree
        // ----------------

        Degree radians_to_degrees(const Radian& radian) {
            return radian * 180.0f / Math::pi;
        }

        // ------
        // cosine
        // ------

        Float32 cosine(const Float32& radian) {
            return cosf(radian);
        }

        // ----
        // sine
        // ----

        Float32 sine(const Float32& radian) {
            return sinf(radian);
        }

        // --------
        // power_of
        // --------

        Float32 power_of(const Float32& orig_val, const Int32& exponent) {
            /*
            f32 ret_val = orig_val;
            for (i32 i = 1; i < exponent; ++i) {
                ret_val *= orig_val;
            }
            return ret_val;
            */
            return powf(orig_val, static_cast<Float32>(exponent));
        }

        #ifdef _DEBUG
        // @TODO: Try to beat!
        //
        // Mine: 14324 ms
        // powf: 1557 ms

        static void power_of_test() {
            Int32 base_max = 10000;
            Int32 exponent_max = 1000;
            for (Int32 base = 2; base < base_max; ++base) {
                for (Int32 exponent = 2; exponent < exponent_max; ++exponent) {
                    Math::power_of(static_cast<Float32>(base), exponent);
                }
            }
        }
        #endif

        // --------------
        // absolute_value
        // --------------

        Float32 absolute_value(const Float32& orig_val) {
            return (orig_val < 0) ? orig_val * -1 : orig_val;
        }

        // ------
        // square
        // ------

        Float32 square(const Float32& orig_val) {
            return orig_val * orig_val;
        }

        // ----
        // cube
        // ----

        Float32 cube(const Float32& orig_val) {
            return orig_val * orig_val * orig_val;
        }

        // -----------
        // square_root
        // -----------

        Float32 square_root(const Float32& orig_val) {
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
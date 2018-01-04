#pragma once

#include "../ZeroEngineStd.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace ZeroEngine {

    class Matrix3x3 : public virtual IZeroObject {
    private:
        Vector3 _matrix[3];
    public:
        Matrix3x3() {}
        ~Matrix3x3() {}

        StringRepr to_string() const override { return "Matrix3x3"; }
    };
}
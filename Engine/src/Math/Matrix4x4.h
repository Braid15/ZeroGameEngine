#pragma once

#include "../ZeroEngineStd.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace ZeroEngine {

    class Matrix4x4 : public virtual IZeroObject {
    private:
        Vector4 _matrix[4];
    public:
        Matrix4x4() {}
        ~Matrix4x4() {}

        StringRepr to_string() const override { return "Matrix4x4"; }
    };
}
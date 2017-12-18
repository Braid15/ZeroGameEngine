#pragma once 

#include "../ZeroEngineStd.h"
#include "Vector2.h"

namespace ZeroEngine {

    class Line : public IZeroObject {
    private:
        Vector2 _start;
        Vector2 _end;
    public:

        inline StringRepr to_string() const { return "Line"; }

    };
}
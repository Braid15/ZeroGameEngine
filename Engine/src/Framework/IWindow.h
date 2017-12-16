#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    class IWindow {
    public:
        virtual void shutdown() = 0;
        typedef std::shared_ptr<IWindow> ptr;
    };

    class NullWindow : public IWindow, public IZeroObject {
    public:
        inline void shutdown() override {}
        inline StringRepr to_string() const { return "NullWindow"; }
    };

}
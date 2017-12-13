#pragma once

#include "../ZeroEngineStd.h"
#include "AFramework.h"
#include "IRenderer.h"
#include "IWindow.h"
#include "SdlFramework\SdlFramework.h"
#include "../Time.h"

namespace ZeroEngine {

    // Provides a global interface to communicate with the framework.
    // Does not implement AFramework and does not necessarily expose AFRameworks complete
    // interface.

    // @TODO: May want to consolidate this into a different class like ZeroEngineApp or something
    class ZeroFramework final {
    private:
        static const AFramework* _framework;
    public:
        ~ZeroFramework() {}
        static Ticks get_ticks();
        static StringRepr to_string();
        static void set_framework(const AFramework*);
    private:
        inline ZeroFramework() {}
        inline ZeroFramework(const ZeroFramework&) {}
    };
}
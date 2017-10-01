#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    class ZeroEngineApp : public IType {

    /* Interface */
    public:
        ZeroEngineApp();
        virtual ~ZeroEngineApp();

    protected:

    private:
        // TODO: 10/1/17
        // This is windows specific. Need to change it out
        HINSTANCE _instance;
        bool _is_running;
        bool _quit_requested;
        bool _is_quitting;
        bool _is_editor_running;

    /* IType interface */
    public:
        virtual TypeName get_type() const override { return "ZeroEngineApp"; }
    };

}

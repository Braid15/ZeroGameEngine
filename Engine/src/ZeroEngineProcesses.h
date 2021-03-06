#pragma once 

#include "ZeroEngineStd.h"
#include "Process/Process.h"
#include "Time.h"

namespace ZeroEngine {

    //
    // TimedProcess
    //

    class TimedProcess : public Process {
    private:
        Uint32 _timeout;
        Uint32 _current;
    public:
        inline explicit TimedProcess(Tick timeout_ms) : 
            _timeout(static_cast<Uint32>(timeout_ms)), _current(0) {}
        inline virtual StringRepr to_string() const override { return "TimedProcess"; }
    protected:
        virtual void on_update(Tick delta_time) override;
    };
}
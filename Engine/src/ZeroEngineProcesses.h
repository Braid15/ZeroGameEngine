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
        uint32_t _timeout;
        uint32_t _current;
    public:
        inline explicit TimedProcess(Tick timeout_ms) : 
            _timeout(static_cast<uint32_t>(timeout_ms)), _current(0) {}
        inline virtual StringRepr to_string() const override { return "TimedProcess"; }
    protected:
        virtual void on_update(Tick delta_time) override;
    };
}
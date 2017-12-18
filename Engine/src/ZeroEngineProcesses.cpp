#include "ZeroEngineProcesses.h"

namespace ZeroEngine {

    //
    // TimedProcess
    //

    void TimedProcess::on_update(Tick delta_time) {
        _current += static_cast<uint32_t>(delta_time);
        if (_current >= _timeout) {
            succeed();
        }
    }
}
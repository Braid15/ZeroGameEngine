#ifdef _DEBUG

#include "TestApp.h"

namespace ZeroEngineAppTest {


    bool MockZeroEngineApp::on_msg_proc(const AppMsg* const msg) {
        return true;
    }

    void MockZeroEngineApp::on_update(Ticks time) {
    }
}

#endif
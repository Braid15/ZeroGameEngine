#include "ZeroEngineApp.h"

namespace ZeroEngine {

    // TODO: Unit test this entire file - 10/4/17

    ZeroEngineApp* ZeroEngineApp::_app = nullptr;

    ZeroEngineApp* const ZeroEngineApp::get_app() {
        return ZeroEngineApp::_app;
    }

    void ZeroEngineApp::set_app( ZeroEngineApp* app ) {
        if ( _app == nullptr ) {
            _app = app;
        }
    }

    // TODO - 10/4/17: Don't know if anything else should
    // be in dtor or if it should all be freed in on_close
    ZeroEngineApp::~ZeroEngineApp() {
        if ( ZeroEngineApp::_app ) {
            delete ZeroEngineApp::_app;
        }
    }




}
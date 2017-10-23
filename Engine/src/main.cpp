#include "ZeroEngine.h"

#include "../test/IFrameworkTesting.h"
#include "../test/TestApp.h"

using namespace ZeroEngine;

// SDL requires this main signature
int main ( int argc, char* args[] ) {

    #ifdef _DEBUG
    int debug_flag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
    debug_flag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag( debug_flag );
    #endif

    ZeroEngineApp::set_app( new ZeroEngineAppTest::MockZeroEngineApp() );
    ZeroEngineApp::instance()->initialize();


    AFramework* framework = new IFrameworkTesting::MockFramework();
    framework->initialize();
    framework->set_app_msg_callback( ZeroEngineApp::on_app_msg );
    framework->set_update_callback( ZeroEngineApp::on_update );
    framework->set_render_callback( ZeroEngineApp::on_render );

    framework->main_loop();
    framework->shutdown();

    ZeroEngineApp::instance()->shutdown();
    

    #ifdef _DEBUG
    _CrtDumpMemoryLeaks();
    #endif

    return 0;
}
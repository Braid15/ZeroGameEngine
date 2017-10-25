#define _SDL

#include "ZeroEngine.h"

#include "../test/IFrameworkTesting.h"
#include "../test/TestApp.h"

using namespace ZeroEngine;

int main( int argc, char* args[] ) {

    #ifdef _DEBUG
    int debug_flag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
    debug_flag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag( debug_flag );
    #endif

    GameOptions options;
    ZeroEngineApp::set_app( new ZeroEngineAppTest::MockZeroEngineApp( options ) );
    ZeroEngineApp* app = ZeroEngineApp::instance();
    app->initialize();

    AFramework* framework = nullptr; 
    #ifdef _SDL
    framework = new IFrameworkTesting::MockFramework();
    #else
    framework = IFrameworkTesting::MockFrameworkTwo::instance();
    #endif

    framework->initialize();
    framework->set_app_msg_callback( ZeroEngineApp::on_app_msg );
    framework->set_update_callback( ZeroEngineApp::on_update );
    framework->set_render_callback( ZeroEngineApp::on_render );
    framework->main_loop();


    ZeroEngineApp::instance()->shutdown();

    framework->shutdown();

    delete framework;
    framework = nullptr;


    #ifdef _DEBUG
    _CrtDumpMemoryLeaks();
    #endif

    return 0;
}




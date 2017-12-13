#include "ZeroEngine.h"

#include "../test/TestApp.h"

using namespace ZeroEngine;

int main( int argc, char* args[] ) {

    #ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif

    AFramework* framework = nullptr; 
    framework = zero_new SdlFramework();
    framework->initialize();
    ZeroFramework::set_framework(framework);

    // @@TODO: Load gameoptions from file
    GameOptions options;
    ZeroEngineApp* app = zero_new ZeroEngineAppTest::MockZeroEngineApp(options);
    app->initialize();
    ZeroEngineApp::set_app(app);


    framework->create_window(app->get_game_title(), app->get_screen_size() );
    framework->create_renderer();


    framework->set_app_msg_callback(ZeroEngineApp::app_msg_proc);
    framework->set_update_callback(ZeroEngineApp::update);
    framework->set_render_callback(ZeroEngineApp::render);
    framework->run_main_loop();

    app->shutdown();
    zero_delete(app);

    ZeroEventManager::shutdown();

    framework->shutdown();
    zero_delete(framework);

    #ifdef _DEBUG
    _CrtDumpMemoryLeaks();
    #endif

    system("PAUSE");

    return 0;
}

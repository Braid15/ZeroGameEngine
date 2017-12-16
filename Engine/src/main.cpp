#include "ZeroEngine.h"

#include "../test/TestApp.h"

using namespace ZeroEngine;

int main( int argc, char* args[] ) {

    #ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif


    // @@TODO: Load gameoptions from file
    GameOptions options;
    GameApp* app = zero_new ZeroEngineAppTest::MockZeroEngineApp(options);

    AFramework* framework = nullptr; 
    framework = zero_new SdlFramework();
    framework->initialize();
    framework->initialize_window_and_renderer(app->get_game_title(), app->get_screen_size());
    ZeroFramework::set_framework(framework);

    app->initialize();
    GameApp::set_app(app);

    GameApp::instance()->load_game();

    framework->set_app_msg_callback(GameApp::app_msg_proc);
    framework->set_update_callback(GameApp::update);
    framework->set_render_callback(GameApp::render);
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

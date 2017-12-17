#include "ZeroEngine.h"

#include "../test/TestApp.h"

using namespace ZeroEngine;

int main( int argc, char* args[] ) {

    #ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif

    Logger::intialize();
    // Logger::disable_tag("DEBUG");

    // @@TODO: Load gameoptions from file
    GameOptions options;
    GameApp* app = zero_new ZeroEngineAppTest::MockZeroEngineApp(options);
    Game::set(app);
    app->set_framework(zero_new SdlFramework());
    if (app->initialize()) {
        app->load_game();
        app->run();
    } else {
        LOG_DEBUG("main", "Error initializing app");
    }

    app->shutdown();
    zero_delete(app);

    Logger::shutdown();

    #ifdef _DEBUG
    _CrtDumpMemoryLeaks();
    #endif

    system("PAUSE");

    return 0;
}

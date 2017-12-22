#include "ZeroEngine.h"

#include "../test/TestApp.h"

using namespace ZeroEngine;

static void run_game();

int main( int argc, char* args[] ) {

    #ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif

    XmlWriter_TinyXmlImpl_UNIT_TEST();
    // run_game();

    #ifdef _DEBUG
    _CrtDumpMemoryLeaks();
    #endif

    system("PAUSE");

    return 0;
}

void run_game() {
    // @TODO: Load options from file.
    GameOptions options;

    // Launcher takes care of deleting these pointers
    GameApp* game = zero_new ZeroEngineAppTest::MockZeroEngineApp(options);
    AFramework* framework = zero_new SdlFramework();

    GameLauncher* launcher = zero_new GameLauncher(game, framework);
    launcher->launch();

    zero_delete(launcher);
}

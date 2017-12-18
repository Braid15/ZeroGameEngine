#include "ZeroEngine.h"

#include "../test/TestApp.h"

using namespace ZeroEngine;

static void run_game();

int main( int argc, char* args[] ) {

    #ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif



    // @TESTING
    /*
    uint32_t f = 0x00FF00;
    uint8_t* msb = (uint8_t*)&f;
    printf("f + 0x0: %p\n", msb);
    printf("f + 0x4: %p\n", msb + 0x4);
    printf("f + 0x8: %p\n", msb + 0x8);
    */


    run_game();





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
